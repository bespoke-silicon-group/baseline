#ifndef __MATRIX_MULTIPLY_HPP
#define __MATRIX_MULTIPLY_HPP
#include <cstdint>

/*
 * This is the most basic single tile version of vector addition
 * that adds two vectors A and B and stores the result in C.
 *
 * The code assumes a sinlge 1x1 grid of a single 1x1 tile group
 * Do NOT use this version with larger tile groups 
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_tile_vector_add(TA *A, TB *B, TC *C,
                      uint32_t WIDTH) {
        // A single tile performs the entire vector addition
	/*for (int iter_x = 0; iter_x < WIDTH; iter_x += 1) { 
                C[iter_x] = A[iter_x] + B[iter_x];
	}*/
        float a_[4],b_[4],c_[4];
        for (int iter_x = 0; iter_x < WIDTH; iter_x += 4) { 
                #pragma GCC unroll 4
                for (int i = 0; i < 4; i++)
                {
                        a_[i] = A[iter_x+i];
                }
                #pragma GCC unroll 4
                for (int i = 0; i < 4; i++)
                {
                        b_[i] = B[iter_x+i];
                }
                #pragma GCC unroll 4
                for (int i = 0; i < 4; i++)
                {
                        c_[i] = a_[i]+b_[i];
                }
                #pragma GCC unroll 4
                for (int i = 0; i < 4; i++)
                {
                        C[iter_x+i] = c_[i];
                }
        }

        return 0;
}

#endif
