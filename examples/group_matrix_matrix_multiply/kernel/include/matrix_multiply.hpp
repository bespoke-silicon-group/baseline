#ifndef __MATRIX_MULTIPLY_HPP
#define __MATRIX_MULTIPLY_HPP
#include <cstdint>

template <typename TA, typename TB, typename TC>
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

        for (uint32_t iter_y = start_y + __bsg_y; iter_y < end_y; iter_y += BSG_TILE_GROUP_Y_DIM) {
                for (uint32_t iter_x = start_x + __bsg_x; iter_x < end_x; iter_x += BSG_TILE_GROUP_X_DIM) {
                        uint32_t sum = static_cast<TC>(0);
                        for (uint32_t k = 0; k < A_WIDTH; k ++) {
                                sum += A[iter_y * A_WIDTH + k] * B[k * B_WIDTH + iter_x];
                        }
                        C[iter_y * B_WIDTH + iter_x] = sum;
                }
        }

        return 0;
}

#endif //__MATRIX_MULTIPLY_HPP
