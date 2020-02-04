/*
 * This kernel performs matrix multiplication
 */

#include "bsg_manycore.h"
#include "bsg_set_tile_x_y.h"

#define BSG_TILE_GROUP_X_DIM bsg_tiles_X
#define BSG_TILE_GROUP_Y_DIM bsg_tiles_Y
#define IGNORE_TAG 0
#include "bsg_tile_group_barrier.h"
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
                int rc, temp = IGNORE_TAG;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_int16(
                      int16_t *A, int16_t *B, int16_t *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc, temp = IGNORE_TAG;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_int8(
                      int8_t *A, int8_t *B, int8_t *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc, temp = IGNORE_TAG;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                return rc;
        }


        int  __attribute__ ((noinline)) kernel_matrix_multiply_float(
                      float *A, float *B, float *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc, temp = IGNORE_TAG;

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply(A, B, C, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                return rc;
        }
}
