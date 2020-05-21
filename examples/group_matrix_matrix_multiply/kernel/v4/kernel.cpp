/*
 * Blocked matrix-matrix multiplication using tile group
 * shared memory.
 * Templatized BLOCK_SIZE_X/y, i.e. the workload of each tile group.
 * Innter multiplication loop unrolled by a factor of 2
 */


// Template parameters
// We use this parameters to call the templatized kernel
// from the C-level kernel. bsg_tiles_X/Y must also be defined
// for legacy reasons, but they are deprecated.
#define TEMPLATE_TG_DIM_X 4            // Tile group X dimension
#define TEMPLATE_TG_DIM_Y 4            // Tile group Y dimension
#define TEMPLATE_BLOCK_SIZE_X 32       // Tile group's block size (X)
#define TEMPLATE_BLOCK_SIZE_Y 64       // Tile group's block size (Y)
#define TEMPLATE_BLOCK_WIDTH  32       // Algorithm's blocking factor

#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y


#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <cstdint>
#include <matrix_multiply.hpp>


// I <3 Hacks! Since bsg_manycore_arch.h can't handle the awesomeness
// of C++ templates I wrote this temporary replacement.
#ifdef bsg_tile_group_remote_ptr
#undef bsg_tile_group_remote_ptr
#include <type_traits>
#define bsg_tile_group_remote_ptr(__type,x,y,local_addr) \
        ( (typename std::add_pointer<__type>::type)                     \
        (   (REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS)               \
            | ((y) << Y_CORD_SHIFTS )                                   \
            | ((x) << X_CORD_SHIFTS )                                   \
            | ((uint32_t) (local_addr)   )                              \
            )                                                           \
                                                           )
#endif



bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


template <int TG_DIM_X, int TG_DIM_Y, int BLOCK_SIZE_X, int BLOCK_SIZE_Y, typename T>
void __attribute__ ((noinline)) memcpy_block_to_shmem (T *A, T *dst, uint32_t M, uint32_t N, uint32_t sub_block_y, uint32_t sub_block_x) { 

	uint32_t start_y = sub_block_y * BLOCK_SIZE_Y;
	uint32_t start_x = sub_block_x * BLOCK_SIZE_X;
	
	for (uint32_t iter_y = __bsg_y; iter_y < BLOCK_SIZE_Y; iter_y += TG_DIM_Y) { 
		for (uint32_t iter_x = __bsg_x; iter_x < BLOCK_SIZE_X; iter_x += TG_DIM_X) { 
			// dst[iter_y][iter_x] <-- A[iter_y + start_y][iter_x + start_x]
			bsg_tile_group_shared_store (T, dst, (iter_y * BLOCK_SIZE_X + iter_x), A[((iter_y + start_y) * N + iter_x + start_x)]);
		}
	}
	return; 
}

template <int TG_DIM_X, int TG_DIM_Y, int BLOCK_SIZE_X, int BLOCK_SIZE_Y, typename T>
void __attribute__ ((noinline)) memcpy_block_to_shmem_transposed (T *A, T *dst, uint32_t M, uint32_t N, uint32_t sub_block_y, uint32_t sub_block_x) { 

	uint32_t start_y = sub_block_y * BLOCK_SIZE_Y;
	uint32_t start_x = sub_block_x * BLOCK_SIZE_X;
	
	for (uint32_t iter_y = __bsg_y; iter_y < BLOCK_SIZE_Y; iter_y += TG_DIM_Y) { 
		for (uint32_t iter_x = __bsg_x; iter_x < BLOCK_SIZE_X; iter_x += TG_DIM_X) { 
			// dst[iter_x][iter_y] <-- A[iter_y + start_y][iter_x + start_x]
			bsg_tile_group_shared_store (T, dst, (iter_x * BLOCK_SIZE_Y + iter_y), A[((iter_y + start_y) * N + iter_x + start_x)]);
		}
	}
	return; 
}

template <int TG_DIM_X, int TG_DIM_Y, int BLOCK_SIZE_X, int BLOCK_SIZE_Y, typename T>
void __attribute__ ((noinline)) memcpy_shmem_to_block (T *A, T *src, uint32_t M, uint32_t N, uint32_t sub_block_y, uint32_t sub_block_x) { 

	uint32_t start_y = sub_block_y * BLOCK_SIZE_Y;
	uint32_t start_x = sub_block_x * BLOCK_SIZE_X;
	
	for (uint32_t iter_y = __bsg_y; iter_y < BLOCK_SIZE_Y; iter_y += TG_DIM_Y) { 
		for (uint32_t iter_x = __bsg_x; iter_x < BLOCK_SIZE_X; iter_x += TG_DIM_X) { 
			// A[iter_y + start_y][iter_x + start_x] <-- src[iter_y][iter_x]
			bsg_tile_group_shared_load (T, src, (iter_y * BLOCK_SIZE_X + iter_x), A[((iter_y + start_y) * N + iter_x + start_x)]);
		}
	}
	return; 
}


template <int TG_DIM_X, int TG_DIM_Y, int BLOCK_SIZE_X, int BLOCK_SIZE_Y, int BLOCK_WIDTH, typename TA, typename TB, typename TC>
void __attribute__ ((noinline)) subblock_shmem_matrix_mul_transposed (TA *A, TB *B, TC *C, uint32_t M, uint32_t N, uint32_t P, uint32_t block_num) { 

	for (uint32_t iter_y = __bsg_y; iter_y < BLOCK_SIZE_Y; iter_y += TG_DIM_Y) { 
		for (uint32_t iter_x = __bsg_x; iter_x < BLOCK_SIZE_X; iter_x += TG_DIM_X) { 

			TC sum = static_cast<TC>(0); 
			TA lc_A;
                        TB lc_B;
                        TC lc_C;

                        #pragma GCC unroll 2
			for (uint32_t k = 0; k < BLOCK_WIDTH; k ++) { 
				// lc_A <-- A[iter_y][iter_x]
				bsg_tile_group_shared_load (TA, A, (iter_y * BLOCK_WIDTH + k), lc_A); 
				// lc_B <-- B[iter_y][iter_x] remember, B is transposed
				bsg_tile_group_shared_load (TB, B, (iter_x * BLOCK_WIDTH + k), lc_B);
				sum += lc_A * lc_B;
			}

			if (!block_num) { 
				// C[iter_y][iter_x] <-- sum
				bsg_tile_group_shared_store (TC, C, (iter_y * BLOCK_SIZE_X + iter_x), sum);
			}
			else { 
				// C[iter_y][iter_x] += sum
				bsg_tile_group_shared_load (TC, C, (iter_y * BLOCK_SIZE_X + iter_x), lc_C);
				bsg_tile_group_shared_store (TC, C, (iter_y * BLOCK_SIZE_X + iter_x), lc_C + sum);
			} 
		}
	}
	return;
}

template <int TG_DIM_X, int TG_DIM_Y, int BLOCK_SIZE_X, int BLOCK_SIZE_Y, int BLOCK_WIDTH, typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) matrix_multiply_group_shared_mem(TA *A, TB *B, TC *C, 
                                                                 uint32_t M, uint32_t N, uint32_t P) { 

	// declare tile-group shared memory
	bsg_tile_group_shared_mem (TA, sh_A, (BLOCK_SIZE_Y * BLOCK_WIDTH));
	bsg_tile_group_shared_mem (TA, sh_B, (BLOCK_WIDTH * BLOCK_SIZE_X));
	bsg_tile_group_shared_mem (TA, sh_C, (BLOCK_SIZE_Y * BLOCK_SIZE_X));

	uint32_t num_blocks = N / BLOCK_WIDTH;	// *** Must divide evenly ***

	for (uint32_t block_num = 0; block_num < num_blocks; block_num ++) { 

		memcpy_block_to_shmem<TG_DIM_X, TG_DIM_Y, BLOCK_WIDTH, BLOCK_SIZE_Y>
                                     (A, sh_A, M, N, __bsg_tile_group_id_y, block_num);
 
		memcpy_block_to_shmem_transposed<TG_DIM_X, TG_DIM_Y, BLOCK_SIZE_X, BLOCK_WIDTH>
                                                (B, sh_B, N, P, block_num, __bsg_tile_group_id_x);

                barrier.sync();
		
		subblock_shmem_matrix_mul_transposed<TG_DIM_X, TG_DIM_Y, BLOCK_SIZE_X, BLOCK_SIZE_Y, BLOCK_WIDTH>
                                                    (sh_A, sh_B, sh_C, M, N, P, block_num);
		
                barrier.sync();
	}

	memcpy_shmem_to_block<TG_DIM_X, TG_DIM_Y, BLOCK_SIZE_X, BLOCK_SIZE_Y>
                              (C, sh_C, M, P, __bsg_tile_group_id_y, __bsg_tile_group_id_x); 

	return 0;
}

extern "C" {
        int  __attribute__ ((noinline)) kernel_matrix_multiply(
                      float *A, float *B, float *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH, uint32_t B_WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x) {
                int rc;

                bsg_cuda_print_stat_kernel_start();
                rc = matrix_multiply_group_shared_mem<TEMPLATE_TG_DIM_X,     \
                                                      TEMPLATE_TG_DIM_Y,     \
                                                      TEMPLATE_BLOCK_SIZE_X, \
                                                      TEMPLATE_BLOCK_SIZE_Y, \
                                                      TEMPLATE_BLOCK_WIDTH > 
                                                         (A, B, C,
                                                          A_HEIGHT, A_WIDTH, B_WIDTH);

                barrier.sync();
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }
}
