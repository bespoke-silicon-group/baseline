/*
 * This kernel performs vector addition. 
 * 
 * This is the single 2-dimensional tile-group Vector-Vector Addition.
 * This version assumes only a single tile group is called.
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
#include <cstring>

extern int bsg_printf(const char*, ...);

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
        int  __attribute__ ((noinline)) kernel_vector_add_int(
                      int *A, int *B, int *C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_single_2D_tile_group(A, B, C, WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_vector_add_int16(
                      int16_t *A, int16_t *B, int16_t *C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_single_2D_tile_group(A, B, C, WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_vector_add_int8(
                      int8_t *A, int8_t *B, int8_t *C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_single_2D_tile_group(A, B, C, WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_vector_add_float(
                      float *A, float *B, float *C,
                      uint32_t WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag, uint32_t iter) {
                bsg_cuda_print_stat_kernel_start();
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_vector_add_single_2D_tile_group(A, B, C, WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }
}
