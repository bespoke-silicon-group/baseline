/*
 * This Kernel runs the gaussian elimination on an input MxN matrix. 
 * Input matrix represents a set of coefficients for an N-dimension linear 
 * equation. The purpose of this kernel is to transform the input matrix into 
 * a matrix where the triangle portion of the matrix below the diameter is zero.
 * Result is an MxN matrix.                                                   
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier_template.hpp>
#include <cstdint>

#include <gaussian_elimination.hpp>


/* 
 * Version 0 
 * 
 */
template <typename T>
int  __attribute__ ((noinline)) gaussian_elimination (T* A,
                                                      T* B,
                                                      uint32_t HEIGHT,
                                                      uint32_t WIDTH) {

        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_gaussian_elimination (float* A,
                                                                     float* B,
                                                                     uint32_t HEIGHT,
                                                                     uint32_t WIDTH) {
                bsg_barrier <bsg_tiles_Y, bsg_tiles_X> barrier;

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = gaussian_elimination (A,
                                           B,
                                           HEIGHT,
                                           WIDTH);

                bsg_cuda_print_stat_end(0);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
