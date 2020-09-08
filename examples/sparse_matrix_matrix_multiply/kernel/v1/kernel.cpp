/*
 * This kernel performs matrix multiplication.
 *
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#define SHD_MEM_SIZE (BSG_TILE_GROUP_X_DIM *BSG_TILE_GROUP_X_DIM*8)
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
void __attribute__ ((noinline)) memcpy_1d_block_to_shmem (bsg_attr_remote T* bsg_attr_noalias vals, uint32_t row_offset, uint32_t nnz, T* bsg_attr_noalias dst, uint32_t phase_num) {

    uint32_t index = ((phase_num * BSG_TILE_GROUP_X_DIM * BSG_TILE_GROUP_Y_DIM ) + __bsg_id) * 8;
    if(index < nnz){
        bsg_unroll(8)
        for(uint32_t i =0; i < 8; i++) {
            bsg_tile_group_shared_store (T, dst, __bsg_id+i, vals[index+row_offset+i]);
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
void __attribute__ ((noinline)) memcpy_shmem_to_1d_block (bsg_attr_remote T* bsg_attr_noalias A, T* bsg_attr_noalias src, uint32_t N) { 

    uint32_t numSubPhases = ((N-1) / SHD_MEM_SIZE) + 1;
    for(uint32_t sub_phase = 0; sub_phase < numSubPhases;sub_phase++) {
        uint32_t index = ((sub_phase * BSG_TILE_GROUP_X_DIM * BSG_TILE_GROUP_Y_DIM) + __bsg_id) * 8;
        if (index < N)
        {
            bsg_unroll(8)
            for(uint32_t i =0; i < 8; i++) {
	            bsg_tile_group_shared_load (T, src,index+i, A[(__bsg_tile_group_id_y * N) + index+i]);
            }
        }
    }
    return; 
}


template <typename TA, typename TB, typename TC>
void __attribute__ ((noinline)) subblock_shmem_matrix_mul (TA* bsg_attr_noalias A_vals, uint32_t* bsg_attr_noalias A_cols, uint32_t nnz,
                                                           bsg_attr_remote TB* bsg_attr_noalias B, TC* bsg_attr_noalias C,
                                                           uint32_t P, uint32_t phase_num) { 

    TA lc_A_val;
    uint32_t lc_A_col;
    TB lc_B;
    TC lc_C[8];
    uint32_t numSubPhases = ((P-1) / SHD_MEM_SIZE) + 1;
    for (uint32_t k = 0; k < SHD_MEM_SIZE && k+(phase_num * BSG_TILE_GROUP_X_DIM * BSG_TILE_GROUP_Y_DIM*8) < nnz; k++) {
        bsg_tile_group_shared_load (TA, A_vals, (k), lc_A_val);
        bsg_tile_group_shared_load (uint32_t, A_cols, (k), lc_A_col); 

        for(uint32_t sub_phase = 0; sub_phase < numSubPhases;sub_phase++) {
            uint32_t B_index = ((sub_phase * BSG_TILE_GROUP_X_DIM * BSG_TILE_GROUP_Y_DIM) + __bsg_id) * 8;
            if (B_index < P) {
                TC sum[8] = {{static_cast<TC>(0)}};

                bsg_unroll(8)
                for (uint32_t f = 0; f < 8;f++) {
                    sum[f] += lc_A_val * B[(lc_A_col * P) + B_index + f];
                }
                if (!phase_num) { 
                    bsg_unroll(8)
                    for (uint32_t f = 0; f < 8;f++) {
                        bsg_tile_group_shared_store (TC, C, (B_index+f), sum[f]);
                    }
                }
                else { 
                    bsg_unroll(8)
                    for (uint32_t f = 0; f < 8;f++) {
                        bsg_tile_group_shared_load (TC, C, (B_index+f), lc_C[f]);
                        bsg_tile_group_shared_store (TC, C, (B_index+f), lc_C[f] + sum[f]);
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
    bsg_tile_group_shared_mem (TA, sh_A_vals, SHD_MEM_SIZE);
    bsg_tile_group_shared_mem (uint32_t, sh_A_cols, SHD_MEM_SIZE);
    bsg_tile_group_shared_mem (TA, sh_C, P);

    for (uint32_t row_index = __bsg_tile_group_id; row_index < M;row_index+=__bsg_grid_dim_x*__bsg_grid_dim_y) {
        //one block for each row of A
        uint32_t row_offset = rows[row_index];
        uint32_t nnz = rows[row_index + 1] - row_offset;

        uint32_t num_phases = ((nnz-1) / SHD_MEM_SIZE) + 1;
        for(uint32_t phase_num = 0; phase_num < num_phases ; phase_num++) {

            memcpy_1d_block_to_shmem (vals,row_offset, nnz, sh_A_vals, phase_num);
            memcpy_1d_block_to_shmem (cols,row_offset, nnz, sh_A_cols, phase_num);

            bsg_tile_group_barrier (&r_barrier, &c_barrier);
            
            subblock_shmem_matrix_mul (sh_A_vals, sh_A_cols, nnz, B, sh_C, P, phase_num);  
            
            bsg_tile_group_barrier (&r_barrier, &c_barrier); 
        }
        
            memcpy_shmem_to_1d_block (C, sh_C, P);
    }

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
