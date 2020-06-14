// This kernel performs blocked matrix multiplication using 
// tile group shared memory. Subblocks of input matrices are
// loaded into tile group shared memory by all tiles, and 
// accesses for matrix multiplication are done to the 
// lower-latency tile group shared meomry instead of the long-
// latency DRAM.
// This code uses old C version of software tile group shared memory.

// TEMPLATE_TG_DIM_X/Y must be defined before bsg_manycore.h is
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.

#define TEMPLATE_TG_DIM_X 4
#define TEMPLATE_TG_DIM_Y 4
#define TEMPLATE_BLOCK_SIZE_X  64
#define TEMPLATE_BLOCK_SIZE_Y  64
#define TEMPLATE_SUBBLOCK_SIZE 32
#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y

#include <bsg_manycore.h>
#include <group_matrix_matrix_multiply.hpp>
#include <bsg_tile_group_barrier.hpp>


bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


// Load a BLOCK_SIZE_X x BLOCK_SIZE_Y submatrix 
// from DRAM into tile group shared memory
template <int TG_DIM_X, int TG_DIM_Y,
          int BLOCK_SIZE_X, int BLOCK_SIZE_Y, typename T>
    void __attribute__ ((noinline)) memcpy_block_to_shmem (T *A, T *dst,
                                                           uint32_t M,
                                                           uint32_t N,
                                                           uint32_t sub_block_y,
                                                           uint32_t sub_block_x) { 
    
        uint32_t start_y = sub_block_y * BLOCK_SIZE_Y;
        uint32_t start_x = sub_block_x * BLOCK_SIZE_X;
        
        for (uint32_t iter_y = __bsg_y; iter_y < BLOCK_SIZE_Y; iter_y += TG_DIM_Y) { 
            for (uint32_t iter_x = __bsg_x; iter_x < BLOCK_SIZE_X; iter_x += TG_DIM_X) { 
                // dst[iter_y][iter_x] <-- A[iter_y + start_y][iter_x + start_x]
                bsg_tile_group_shared_store (T, dst, (iter_y * BLOCK_SIZE_X + iter_x), 
                                             A[((iter_y + start_y) * N + iter_x + start_x)]);
            }
        }
        return; 
    }


// Load a BLOCK_SIZE_X x BLOCK_SIZE_Y submatrix 
// from DRAM into tile group shared memory and transpose it
template <int TG_DIM_X, int TG_DIM_Y,
          int BLOCK_SIZE_X, int BLOCK_SIZE_Y, typename T>
    void __attribute__ ((noinline)) memcpy_block_to_shmem_transposed (T *A, T *dst,
                                                                      uint32_t M,
                                                                      uint32_t N,
                                                                      uint32_t sub_block_y,
                                                                      uint32_t sub_block_x) { 
    
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


// Store a BLOCK_SIZE_X x BLOCK_SIZE_Y submatrix 
// from tile group shared memory to DRAM 
template <int TG_DIM_X, int TG_DIM_Y,
          int BLOCK_SIZE_X, int BLOCK_SIZE_Y, typename T>
    void __attribute__ ((noinline)) memcpy_shmem_to_block (T *A, T *src,
                                                           uint32_t M,
                                                           uint32_t N,
                                                           uint32_t sub_block_y,
                                                           uint32_t sub_block_x) { 
    
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


// Perform a submatrix multiplication among two 
// matrices stored in tile group shared memory
// and store into tile group shared memory
template <int TG_DIM_X, int TG_DIM_Y,
          int BLOCK_SIZE_X, int BLOCK_SIZE_Y, int SUBBLOCK_SIZE,
          typename TA, typename TB, typename TC>
    void __attribute__ ((noinline)) subblock_shmem_matrix_mul_transposed (TA *A, TB *B, TC *C,
                                                                          uint32_t M,
                                                                          uint32_t N,
                                                                          uint32_t P,
                                                                          uint32_t block_num,
                                                                          uint32_t unroll_factor) { 
    
        for (uint32_t iter_y = __bsg_y; iter_y < BLOCK_SIZE_Y; iter_y += TG_DIM_Y) { 
            for (uint32_t iter_x = __bsg_x; iter_x < BLOCK_SIZE_X; iter_x += TG_DIM_X) { 
                TC sum = static_cast<TC>(0); 
                TA lc_A;
                TB lc_B;
                TC lc_C;


                // lc_A <-- A[iter_y][iter_x]
                // lc_B <-- B[iter_y][iter_x] remember, B is transposed
                // sum += lc_A * lc_B
                switch(unroll_factor) {
                    case 2:
                        #pragma GCC unroll 2
                        for (uint32_t k = 0; k < SUBBLOCK_SIZE; k ++) { 
                            bsg_tile_group_shared_load (TA, A, (iter_y * SUBBLOCK_SIZE + k), lc_A); 
                            bsg_tile_group_shared_load (TB, B, (iter_x * SUBBLOCK_SIZE + k), lc_B);
                            sum += lc_A * lc_B;
                        }
                        break;
                    case 4:
                        #pragma GCC unroll 4
                        for (uint32_t k = 0; k < SUBBLOCK_SIZE; k ++) { 
                            bsg_tile_group_shared_load (TA, A, (iter_y * SUBBLOCK_SIZE + k), lc_A); 
                            bsg_tile_group_shared_load (TB, B, (iter_x * SUBBLOCK_SIZE + k), lc_B);
                            sum += lc_A * lc_B;
                        }
                        break;
                    case 8:
                        #pragma GCC unroll 8
                        for (uint32_t k = 0; k < SUBBLOCK_SIZE; k ++) { 
                            bsg_tile_group_shared_load (TA, A, (iter_y * SUBBLOCK_SIZE + k), lc_A); 
                            bsg_tile_group_shared_load (TB, B, (iter_x * SUBBLOCK_SIZE + k), lc_B);
                            sum += lc_A * lc_B;
                        }
                        break;
                    case 16:
                        #pragma GCC unroll 16
                        for (uint32_t k = 0; k < SUBBLOCK_SIZE; k ++) { 
                            bsg_tile_group_shared_load (TA, A, (iter_y * SUBBLOCK_SIZE + k), lc_A); 
                            bsg_tile_group_shared_load (TB, B, (iter_x * SUBBLOCK_SIZE + k), lc_B);
                            sum += lc_A * lc_B;
                        }
                        break;
                    case 32:
                        #pragma GCC unroll 32
                        for (uint32_t k = 0; k < SUBBLOCK_SIZE; k ++) { 
                            bsg_tile_group_shared_load (TA, A, (iter_y * SUBBLOCK_SIZE + k), lc_A); 
                            bsg_tile_group_shared_load (TB, B, (iter_x * SUBBLOCK_SIZE + k), lc_B);
                            sum += lc_A * lc_B;
                        }
                        break;
                    default:
                        #pragma GCC unroll 1
                        for (uint32_t k = 0; k < SUBBLOCK_SIZE; k ++) { 
                            bsg_tile_group_shared_load (TA, A, (iter_y * SUBBLOCK_SIZE + k), lc_A); 
                            bsg_tile_group_shared_load (TB, B, (iter_x * SUBBLOCK_SIZE + k), lc_B);
                            sum += lc_A * lc_B;
                        }
                        break;
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


template <int TG_DIM_X, int TG_DIM_Y,
          int BLOCK_SIZE_X, int BLOCK_SIZE_Y, int SUBBLOCK_SIZE,
          typename TA, typename TB, typename TC>
    int __attribute__ ((noinline)) group_matrix_multiply(TA *A, TB *B, TC *C, 
                                                         uint32_t M,
                                                         uint32_t N,
                                                         uint32_t P,
                                                         uint32_t unroll_factor) { 
    
        // declare tile-group shared memory
        bsg_tile_group_shared_mem (TA, sh_A, (BLOCK_SIZE_Y * SUBBLOCK_SIZE));
        bsg_tile_group_shared_mem (TA, sh_B, (SUBBLOCK_SIZE * BLOCK_SIZE_X));
        bsg_tile_group_shared_mem (TA, sh_C, (BLOCK_SIZE_Y * BLOCK_SIZE_X));
        
        uint32_t num_blocks = N / SUBBLOCK_SIZE;	// *** Must divide evenly ***
        
        for (uint32_t block_num = 0; block_num < num_blocks; block_num ++) { 

            // Load a MxN submatrix from A in DRAM into 
            // tile group shared memory and transpose it
            memcpy_block_to_shmem<TG_DIM_X, TG_DIM_Y,
                                  SUBBLOCK_SIZE, BLOCK_SIZE_Y>
                                  (A, sh_A, M, N,
                                   __bsg_tile_group_id_y, block_num);
            
            // Load a NxP submatrix from B in DRAM into 
            // tile group shared memory and transpose it
            memcpy_block_to_shmem_transposed<TG_DIM_X, TG_DIM_Y,
                                             BLOCK_SIZE_X, SUBBLOCK_SIZE>
                                             (B, sh_B, N, P,
                                              block_num, __bsg_tile_group_id_x);
            
            barrier.sync();
            
            // Perform submatrix multiplication in 
            // tile group shared memory            
            subblock_shmem_matrix_mul_transposed<TG_DIM_X, TG_DIM_Y,
                                                 BLOCK_SIZE_X, BLOCK_SIZE_Y,
                                                 SUBBLOCK_SIZE>
                                                 (sh_A, sh_B, sh_C,
                                                  M, N, P, block_num,
                                                  unroll_factor);
            
            barrier.sync();
        }

        // Store the MxP submatrix multiplication result
        // from tile group shared memory into C in DRAM
        memcpy_shmem_to_block<TG_DIM_X, TG_DIM_Y,
                              BLOCK_SIZE_X, BLOCK_SIZE_Y>
                              (C, sh_C, M, P,
                               __bsg_tile_group_id_y,
                               __bsg_tile_group_id_x); 
        
        return 0;
    }


extern "C" {
    int  __attribute__ ((noinline)) kernel_matrix_multiply(float *A, float *B, float *C,
                                                           uint32_t A_HEIGHT,
                                                           uint32_t A_WIDTH,
                                                           uint32_t B_WIDTH,
                                                           uint32_t block_size_y,
                                                           uint32_t block_size_x) {
        int rc;
        bsg_cuda_print_stat_kernel_start();

        for (int i = 0; i < 6; i++) {
            bsg_cuda_print_stat_start(i+1);

            rc = group_matrix_multiply <TEMPLATE_TG_DIM_X,
                                        TEMPLATE_TG_DIM_Y,
                                        TEMPLATE_BLOCK_SIZE_X,
                                        TEMPLATE_BLOCK_SIZE_Y,
                                        TEMPLATE_SUBBLOCK_SIZE> (A, B, C,
                                                                 A_HEIGHT,
                                                                 A_WIDTH,
                                                                 B_WIDTH,
                                                                 (1 << i));

            bsg_cuda_print_stat_end(i+1);
        }

        barrier.sync();

        bsg_cuda_print_stat_kernel_end();
        return rc;
    }
}
