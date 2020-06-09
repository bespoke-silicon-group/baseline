/*
 * This kernel performs vector addition. 
 * 
 * This is the 1 dimensional grid of 2 dimensional tile groups version of vector addition
 * This version assumes a 1-dimensional grid of 2-dimensional tile groups are called.
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
#include <bsg_tile_group_barrier.h>
INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, bsg_tiles_X-1, 0, bsg_tiles_Y-1);

#include <vector_add.hpp>
//#include <cstring>

extern int bsg_printf(const char*, ...);

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
        int  __attribute__ ((noinline)) kernel_vector_add_int(
                      __remote int * __restrict__ A, __remote int * __restrict__ B, __remote int * __restrict__ C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_1D_grid_2D_tile_groups(A, B, C, WIDTH,
                                                                      block_size_x);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_vector_add_int16(
                      __remote int16_t * __restrict__ A, __remote int16_t * __restrict__ B, __remote int16_t * __restrict__ C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_1D_grid_2D_tile_groups(A, B, C, WIDTH,
                                                                      block_size_x);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_vector_add_int8(
                      __remote int8_t * __restrict__ A, __remote int8_t * __restrict__ B, __remote int8_t * __restrict__ C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_1D_grid_2D_tile_groups(A, B, C, WIDTH,
                                                                      block_size_x);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_vector_add_float(
                      __remote float * __restrict__ A, __remote float * __restrict__ B, __remote float * __restrict__ C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_1D_grid_2D_tile_groups(A, B, C, WIDTH,
                                                                      block_size_x);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }
}
