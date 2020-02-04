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

                // These arrays are resident in DMEM
                int A_local[A_HEIGHT * A_WIDTH];
                int B_local[A_WIDTH * B_WIDTH];
                int C_local[A_HEIGHT * B_WIDTH];

                memcpy (A_local, A, sizeof(A[0])*A_HEIGHT*A_WIDTH);
                memcpy (B_local, B, sizeof(B[0])*A_WIDTH*B_WIDTH);

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply_transpose(A_local, B_local, C_local, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                memcpy (C, C_local, sizeof(C[0])*A_HEIGHT*B_WIDTH);

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_int16(
                      int16_t*A, int16_t*B, int16_t*C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc, temp = IGNORE_TAG;

                // These arrays are resident in DMEM
                int16_t A_local[A_HEIGHT * A_WIDTH];
                int16_t B_local[A_WIDTH * B_WIDTH];
                int16_t C_local[A_HEIGHT * B_WIDTH];

                memcpy (A_local, A, sizeof(A[0])*A_HEIGHT*A_WIDTH);
                memcpy (B_local, B, sizeof(B[0])*A_WIDTH*B_WIDTH);

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply_transpose(A_local, B_local, C_local, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                memcpy (C, C_local, sizeof(C[0])*A_HEIGHT*B_WIDTH);

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_int8(
                      int8_t *A, int8_t *B, int8_t *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc, temp = IGNORE_TAG;

                // These arrays are resident in DMEM
                int8_t A_local[A_HEIGHT * A_WIDTH];
                int8_t B_local[A_WIDTH * B_WIDTH];
                int8_t C_local[A_HEIGHT * B_WIDTH];

                memcpy (A_local, A, sizeof(A[0])*A_HEIGHT*A_WIDTH);
                memcpy (B_local, B, sizeof(B[0])*A_WIDTH*B_WIDTH);

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply_transpose(A_local, B_local, C_local, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                memcpy (C, C_local, sizeof(C[0])*A_HEIGHT*B_WIDTH);

                return rc;
        }

        int  __attribute__ ((noinline)) kernel_matrix_multiply_float(
                      float *A, float *B, float *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH, uint32_t tag, uint32_t iter) {
                int rc, temp = IGNORE_TAG;

                // These arrays are resident in DMEM
                float A_local[A_HEIGHT * A_WIDTH];
                float B_local[A_WIDTH * B_WIDTH];
                float C_local[A_HEIGHT * B_WIDTH];

                memcpy (A_local, A, sizeof(A[0])*A_HEIGHT*A_WIDTH);
                memcpy (B_local, B, sizeof(B[0])*A_WIDTH*B_WIDTH);

                for(int i = 0; i <= iter; ++i){
                        bsg_cuda_print_stat_start(temp);
                        rc = kernel_matrix_multiply_transpose(A_local, B_local, C_local, A_HEIGHT, A_WIDTH, B_WIDTH);
                        bsg_cuda_print_stat_end(temp);
                        temp = tag;
                }

                memcpy (C, C_local, sizeof(C[0])*A_HEIGHT*B_WIDTH);

                return rc;
        }
}
