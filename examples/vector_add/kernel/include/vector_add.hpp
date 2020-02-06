#ifndef __MATRIX_MULTIPLY_HPP
#define __MATRIX_MULTIPLY_HPP
#include <cstdint>

/*
 * This is a naive implementation of vector addition that
 * multiplies the adds two vectors A and B and stores the result in C.
 *
 * The code assumes a sinlge grid of 1-dimensional tile group
 * Do NOT use this version with multiple or 2-dimensional tile groups 
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_vector_add_single_1D_tile_group(TA *A, TB *B, TC *C,
                      uint32_t WIDTH) {

	for (int iter_x = __bsg_id; iter_x < WIDTH; iter_x += bsg_tiles_X * bsg_tiles_Y) { 
                C[iter_x] = A[iter_x] + B[iter_x];
	}

	bsg_tile_group_barrier(&r_barrier, &c_barrier); 

        return 0;
}


#endif
