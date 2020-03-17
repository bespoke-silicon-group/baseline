/*
 * This kernel performs matrix multiplication. 
 * 
 * This is the most basic version of single-tile Matrix-Matrix (MM)
 * Multiplication. Unlike later versions, the statistics of first
 * iteration of the MM computation is not discarded (i.e. the same tag
 * is used for every iteration). See v1 for comparison.
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

#include <matrix_multiply.hpp>
#include <cstring>

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
        int  __attribute__ ((noinline)) kernel_matrix_multiply_int(
                      int *A, int *B, int *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc;
                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_int16(
                      int16_t *A, int16_t *B, int16_t *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_int8(
                      int8_t *A, int8_t *B, int8_t *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }

                return rc;
        }


        int  __attribute__ ((noinline)) kernel_matrix_multiply_float(
                      float *A, float *B, float *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(tag);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(tag);
                }

                return rc;
        }
}
