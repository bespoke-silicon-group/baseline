/*
 * This kernel performs matrix multiplication.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define bsg_tiles_X 4
#define bsg_tiles_Y 4
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <cstdint>
#include <matrix_multiply.hpp>

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


template <int TG_DIM_X, int TG_DIM_Y, typename TA, typename TB, typename TC>
int  __attribute__ ((noinline)) matrix_multiply_group(TA *A, TB *B, TC *C,
                                                      uint32_t A_HEIGHT, uint32_t A_WIDTH, uint32_t B_WIDTH,
                                                      uint32_t block_size_y, uint32_t block_size_x) {

        uint32_t start_y = __bsg_tile_group_id_y * block_size_y;
        uint32_t start_x = __bsg_tile_group_id_x * block_size_x;
        uint32_t end_y = start_y + block_size_y;
        uint32_t end_x = start_x + block_size_x;
        
        // Double check matrix output dimensions. Only write where
        // valid data is.
	end_y = A_HEIGHT < (start_y + block_size_y) ? A_HEIGHT : (start_y + block_size_y);
	end_x = B_WIDTH < (start_x + block_size_x) ? B_WIDTH : (start_x + block_size_x);

        for (uint32_t iter_y = start_y + __bsg_y; iter_y < end_y; iter_y += TG_DIM_Y) {
                for (uint32_t iter_x = start_x + __bsg_x; iter_x < end_x; iter_x += TG_DIM_X) {
                        TC sum = static_cast<TC>(0);
                        for (uint32_t k = 0; k < A_WIDTH; k ++) {
                                sum += A[iter_y * A_WIDTH + k] * B[k * B_WIDTH + iter_x];
                        }
                        C[iter_y * B_WIDTH + iter_x] = sum;
                }
        }

        return 0;
}




extern "C" {
        int  __attribute__ ((noinline)) kernel_matrix_multiply(
                      float *A, float *B, float *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH, uint32_t B_WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x) {
                int rc;
                bsg_cuda_print_stat_kernel_start();
                rc = matrix_multiply_group<bsg_tiles_X, bsg_tiles_Y> (A, B, C,
                                                                      A_HEIGHT, A_WIDTH, B_WIDTH,
                                                                      block_size_y, block_size_x);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
