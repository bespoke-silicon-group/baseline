/*
 * This kernel runt the dense vector vector dot product kernel.
 * Each input vector is represented by two arrays, the array of index 
 * of non-zero valeus, and the array with the corresponding values.
 * The output is a single number replresenting the dot product.
 * block_size determines the amount of work each tile group handles,
 * i.e. the number of element-wise multiplications.
 * Work is divided among tiles in a tile group evenly.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 1
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier_template.hpp>
#include <cstdint>

#include <dense_vector_dot.hpp>


/* 
 * Version 0 
 * In this version, a single tile performs the entire dot product.
 */
template <typename TA, typename TB, typename TR>
int  __attribute__ ((noinline)) dense_vector_dot_single_tile (int* dense_A_index,
                                                              TA*  dense_A_data,
                                                              uint32_t A_width,
                                                              int* dense_B_index,
                                                              TB*  dense_B_data,
                                                              uint32_t B_width,
                                                              TR* result) {

        int A_ptr = 0;
        int B_ptr = 0;

        TR sum = 0;

        while (A_ptr < A_width && B_ptr < B_width) {
                int A_idx = dense_A_index[A_ptr];
                int B_idx = dense_B_index[B_ptr];

                if (A_idx == B_idx) {
                        sum += dense_A_data[A_idx] * dense_B_data[B_idx];
                        A_idx += 1;
                        B_idx += 1;
                }
                else if (A_idx < B_idx) {
                    A_ptr += 1;
                }
                else {
                    B_ptr += 1;
                }
        }

        *result = sum;

        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_dense_vector_dot (int* dense_A_index,
                                                                 int*  dense_A_data,
                                                                 uint32_t A_width,
                                                                 int* dense_B_index,
                                                                 int*  dense_B_data,
                                                                 uint32_t B_width,
                                                                 int* result) {
                bsg_barrier <bsg_tiles_Y, bsg_tiles_X> barrier;

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = dense_vector_dot_single_tile (dense_A_index,
                                                   dense_A_data,
                                                   A_width,
                                                   dense_B_index,
                                                   dense_B_data,
                                                   B_width,
                                                   result);

                bsg_cuda_print_stat_end(0);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
