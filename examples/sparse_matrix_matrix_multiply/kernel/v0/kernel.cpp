/*
 * This kernel performs matrix multiplication.
 *
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 16
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
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

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


template <typename T>
void __attribute__ ((noinline)) memcpy_1d_block_to_shmem (bsg_attr_remote T* bsg_attr_noalias vals, uint32_t row_offset, uint32_t nnz, T* bsg_attr_noalias dst,
                                                          uint32_t block_size_y, uint32_t block_size_x, uint32_t phase_num) { 

    for(uint32_t iter_y = __bsg_y; iter_y < block_size_y; iter_y += BSG_TILE_GROUP_Y_DIM) { 
        for(uint32_t iter_x = __bsg_x; iter_x < block_size_x; iter_x += BSG_TILE_GROUP_X_DIM) {
            uint32_t index = row_offset + (phase_num * block_size_y * block_size_x) + ((iter_y * block_size_x) + iter_x);
            // dst[iter_y][iter_x] <-- A[iter_y + start_y][iter_x + start_x]
            if(index < (nnz+row_offset)){
                bsg_tile_group_shared_store (T, dst, (iter_y * block_size_x + iter_x), vals[index]);
            }
        }
    }
    return; 
}

template <typename T>
void __attribute__ ((noinline)) memcpy_block_to_shmem_transposed (T *A, T *dst, uint32_t M, uint32_t N, uint32_t block_size_y, uint32_t block_size_x, uint32_t sub_block_y, uint32_t sub_block_x) { 

	uint32_t start_y = sub_block_y * block_size_y;
	uint32_t start_x = sub_block_x * block_size_x;
	
	for (uint32_t iter_y = __bsg_y; iter_y < block_size_y; iter_y += BSG_TILE_GROUP_Y_DIM) { 
		for (uint32_t iter_x = __bsg_x; iter_x < block_size_x; iter_x += BSG_TILE_GROUP_X_DIM) { 
			// dst[iter_x][iter_y] <-- A[iter_y + start_y][iter_x + start_x]
			bsg_tile_group_shared_store (T, dst, (iter_x * block_size_y + iter_y), A[((iter_y + start_y) * N + iter_x + start_x)]);
		}
	}
	return; 
}

template <typename T>
void __attribute__ ((noinline)) memcpy_shmem_to_1d_block (bsg_attr_remote T* bsg_attr_noalias A, T* bsg_attr_noalias src, uint32_t N, uint32_t block_size_y, uint32_t block_size_x) { 

    for (uint32_t iter_y = __bsg_y; iter_y < block_size_y; iter_y += BSG_TILE_GROUP_Y_DIM) { 
        for (uint32_t iter_x = __bsg_x; iter_x < block_size_x; iter_x += BSG_TILE_GROUP_X_DIM) {
            uint32_t numThreads = block_size_y * block_size_x;
            uint32_t numSubPhases = (N / numThreads) + 1;
            for(uint32_t sub_phase = 0; sub_phase < numSubPhases;sub_phase++) {
                uint32_t index = (sub_phase * block_size_y * block_size_x) + ((iter_y * block_size_x) + iter_x);
                if (index < N)
                {
                    // A[iter_y + start_y][iter_x + start_x] <-- src[iter_y][iter_x]
	            bsg_tile_group_shared_load (T, src,index, A[(__bsg_tile_group_id_y * N) + index]);
                }
            }
	}
    }
    return; 
}


template <typename TA, typename TB, typename TC>
void __attribute__ ((noinline)) subblock_shmem_matrix_mul (TA* bsg_attr_noalias A_vals, uint32_t* bsg_attr_noalias A_cols, uint32_t nnz,
                                                           bsg_attr_remote TB* bsg_attr_noalias B, TC* bsg_attr_noalias C, uint32_t P,
                                                           uint32_t block_size_y, uint32_t block_size_x, uint32_t phase_num) { 

    for (uint32_t iter_y = __bsg_y; iter_y < block_size_y; iter_y += BSG_TILE_GROUP_Y_DIM) { 
        for (uint32_t iter_x = __bsg_x; iter_x < block_size_x; iter_x += BSG_TILE_GROUP_X_DIM) { 
            uint32_t numThreads = block_size_y * block_size_x;
            TA lc_A_val;
            uint32_t lc_A_col;
            TB lc_B;
            TC lc_C;
            uint32_t numSubPhases = ((P-1) / numThreads) + 1;
            for(uint32_t sub_phase = 0; sub_phase < numSubPhases;sub_phase++) {
                uint32_t B_index = (sub_phase * block_size_y * block_size_x) + ((iter_y * block_size_x) + iter_x);
                TC sum = static_cast<TC>(0); 
                if (B_index < P) {
                    for (uint32_t k = 0; k < numThreads && k+(phase_num * block_size_y * block_size_x) < nnz; k++) {
                        // lc_A <-- A[iter_y][iter_x]
                        bsg_tile_group_shared_load (TA, A_vals, (k), lc_A_val);
                        bsg_tile_group_shared_load (uint32_t, A_cols, (k), lc_A_col); 

                        lc_B = B[(lc_A_col * P) + B_index];
                        sum += lc_A_val * lc_B;
                    }
                    if (!phase_num) { 
                        // C[iter_y][iter_x] <-- sum
                        bsg_tile_group_shared_store (TC, C, (B_index), sum);
                    }
                    else { 
                        // C[iter_y][iter_x] += su
    		        bsg_tile_group_shared_load (TC, C, (B_index), lc_C);
                        bsg_tile_group_shared_store (TC, C, (B_index), lc_C + sum);
                    }
                }
	    }
        }
    }
    return;
}

template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) sparse_matrix_multiply_shared_mem(bsg_attr_remote TA* bsg_attr_noalias vals, bsg_attr_remote uint32_t* bsg_attr_noalias rows, bsg_attr_remote uint32_t* bsg_attr_noalias cols,
                                                                 bsg_attr_remote TB* bsg_attr_noalias B, bsg_attr_remote TC* bsg_attr_noalias C, 
                                                                 uint32_t M, uint32_t N, uint32_t P, 
                                                                 uint32_t block_size_y, uint32_t block_size_x) {

    // declare tile-group shared memory
    bsg_tile_group_shared_mem (TA, sh_A_vals, (block_size_y * block_size_x));
    bsg_tile_group_shared_mem (uint32_t, sh_A_cols, (block_size_y * block_size_x));
    bsg_tile_group_shared_mem (TA, sh_C, P);

    //one block for each row of A
    uint32_t row_offset = rows[__bsg_tile_group_id_y];
    uint32_t nnz = rows[__bsg_tile_group_id_y + 1] - row_offset;

    uint32_t num_phases = ((nnz-1) / (block_size_y * block_size_x)) + 1;
    for(uint32_t phase_num = 0; phase_num < num_phases ; phase_num++) {

        memcpy_1d_block_to_shmem (vals,row_offset, nnz, sh_A_vals, block_size_y, block_size_x, phase_num);
        memcpy_1d_block_to_shmem (cols,row_offset, nnz, sh_A_cols, block_size_y, block_size_x, phase_num);

	bsg_tile_group_barrier (&r_barrier, &c_barrier);
        
        subblock_shmem_matrix_mul (sh_A_vals, sh_A_cols, nnz, B, sh_C, P, block_size_y, block_size_x, phase_num);  
		
	bsg_tile_group_barrier (&r_barrier, &c_barrier); 
    }
    
    memcpy_shmem_to_1d_block (C, sh_C, P, block_size_y, block_size_x); 

    return 0;
}

extern "C" {
        int  __attribute__ ((noinline)) kernel_sparse_matrix_multiply(
                      float *vals, uint32_t *rows, uint32_t *cols,
                      float *B, float *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH, uint32_t B_WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x) {
                int rc;

                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);
                rc = sparse_matrix_multiply_shared_mem(vals, rows, cols,
                                                      B, C,
                                                      A_HEIGHT, A_WIDTH, B_WIDTH,
                                                      block_size_y, block_size_x);
                bsg_cuda_print_stat_end(0);

                bsg_tile_group_barrier(&r_barrier, &c_barrier);
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }
}
