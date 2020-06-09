#ifndef __MATRIX_MULTIPLY_HPP
#define __MATRIX_MULTIPLY_HPP
//#include <cstdint>
#include <stdint.h>

#define __remote __attribute__((address_space(1)))
/*
 * This is the most basic single tile version of vector addition
 * that adds two vectors A and B and stores the result in C.
 *
 * The code assumes a sinlge 1x1 grid of a single 1x1 tile group
 * Do NOT use this version with larger tile groups 
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_vector_add_single_tile(__remote TA __restrict__ *A, __remote TB __restrict__ *B, __remote TC __restrict__ *C,
                      uint32_t WIDTH) {
        // A single tile performs the entire vector addition
  #pragma unroll 8
	for (int iter_x = 0; iter_x < WIDTH; iter_x += 1) { 
                C[iter_x] = A[iter_x] + B[iter_x];
	}

	bsg_tile_group_barrier(&r_barrier, &c_barrier); 

        return 0;
}


/*
 * This is the single 1 dimensional tile group version of vector addition
 * that adds two vectors A and B and stores the result in C.
 *
 * The code assumes a sinlge 1x1 grid of 1-dimensional tile group
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_vector_add_single_1D_tile_group(__remote TA __restrict__ *A, __remote TB __restrict__ *B, __remote TC __restrict__ *C,
                      uint32_t WIDTH) {

        // Vector is divided among tiles in the tile group
        // As tile group is one dimensional, each tile performs
        // (WIDTH / bsg_tiles_X) additions
  #pragma unroll 8
	for (int iter_x = __bsg_x; iter_x < WIDTH; iter_x += bsg_tiles_X) { 
                C[iter_x] = A[iter_x] + B[iter_x];
	}

	bsg_tile_group_barrier(&r_barrier, &c_barrier); 

        return 0;
}


/*
 * This is the single 2 dimensional tile group version of vector addition
 * that adds two vectors A and B and stores the result in C.
 *
 * The code assumes a sinlge 1x1 grid of tile group
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_vector_add_single_2D_tile_group(__remote TA __restrict__ *A, __remote TB __restrict__ *B, __remote TC __restrict__ *C,
                      uint32_t WIDTH) {

        // Vector is divided among tiles in the tile group
        // As the tile group is two diemsnional, each tile performs
        // (WIDTH / (bsg_tiles_X * bsg_tiles_Y)) additions
  #pragma unroll 8
	for (int iter_x = __bsg_id; iter_x < WIDTH; iter_x += bsg_tiles_X * bsg_tiles_Y) { 
                C[iter_x] = A[iter_x] + B[iter_x];
	}

	bsg_tile_group_barrier(&r_barrier, &c_barrier); 

        return 0;
}


/*
 * This is the 1 dimensional grid of 2 dimensional tile groups version of vector addition
 * that adds two vectors A and B and stores the result in C.
 *
 * The code assumes a 1-dimensional grid of 2-dimensional tile groups are called.
 * Due to the nature of the compuation (1 dimensional vector addition), there
 * is no need to launch a 2-dimensional grid. Look at matrix multiplication examples
 * for a sample of launching 2-dimensional grids.
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_vector_add_1D_grid_2D_tile_groups(__remote TA __restrict__ *A, __remote TB __restrict__ *B, __remote TC __restrict__ *C,
                      uint32_t WIDTH, uint32_t block_size_x) {

        // Each tile group is responsbile for calculating block_size_x elements
        // As there are multiple tile groups that shared the work,
        // first we calculate the porition of each specific tile group
        uint32_t start = __bsg_tile_group_id_x * block_size_x;
        uint32_t end = start + block_size_x;
        

        // A tile group's share (block_size_x) is divided among tiles in the tile group
        // As the tile group is two diemsnional, each tile performs
        // (block_size_x / (bsg_tiles_X * bsg_tiles_Y)) additions
  #pragma unroll 8
	for (int iter_x = start + __bsg_id; iter_x < end; iter_x += bsg_tiles_X * bsg_tiles_Y) { 
                C[iter_x] = A[iter_x] + B[iter_x];
	}

	bsg_tile_group_barrier(&r_barrier, &c_barrier); 

        return 0;
}




#endif
