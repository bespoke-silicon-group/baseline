/*
 * This Kernel runs the gaussian elimination on an input MxN matrix. 
 * Input matrix represents a set of coefficients for an N-dimension linear 
 * equation. The purpose of this kernel is to transform the input matrix into 
 * a matrix where the triangle portion of the matrix below the diameter is zero.
 * Result is an MxN matrix.                                                   
 * Because of the nature of the application and the need for synchronization
 * among threads, the entire operation has to be done within one tile group.
 * Therefore, a single tile group has to handle the entire matrix, and the block
 * size (a tile group's workload) is set to the matrix height.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <bsg_striped_array.hpp>
#include <cstdint>

#include <gaussian_elimination.hpp>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


using namespace bsg_manycore;

/* 
 * Version 2
 * In this version, tiles in the tile group first load the matrix
 * into tile group shared memory, perform the compuation on tile grou
 * shared memory to alleviate redundant access latencies to DRAM,
 * and then store results back into DRAM.
 */
template <int HEIGHT, int WIDTH, typename T>
int  __attribute__ ((noinline)) gaussian_elimination_sh_mem (T* A) {


        TileGroupStripedArray<T, HEIGHT * WIDTH, bsg_tiles_X, bsg_tiles_Y, 1> sh_A;

        const int num_tiles = bsg_tiles_X * bsg_tiles_Y;

        // Load matrix into tile group shared memory
        for (int y = __bsg_y; y < HEIGHT; y += bsg_tiles_Y) {
                for (int x = __bsg_x; x < WIDTH; x += bsg_tiles_X) {
                        sh_A[y * WIDTH + x] = A[y * WIDTH + x];
                }
        }


        // Synchronize to ensure entire matrix is loaded
        bsg_tile_group_barrier(&r_barrier, &c_barrier);


        for (int y_src = 0; y_src < HEIGHT; y_src ++) {
                // We break this loop, and divide it among tiles in tile group 
                for (int y_dst = __bsg_id; y_dst < HEIGHT; y_dst += num_tiles) {
                        // If the desnitation row, is less that the source row,
                        // there is nothing to be done
                        if (y_dst > y_src) {
                                // Calculate the coefficient
                                // Coefficient = A[y_dst][y_src] / A[y_src][y_src]
                                float c = sh_A[y_dst * WIDTH + y_src] / sh_A[y_src * WIDTH + y_src];

                                for (int x = 0; x < WIDTH; x ++) {
                                        // A[y_dst][x] -= c * A[y_src][x]       
                                        sh_A[y_dst * WIDTH + x] = sh_A[y_dst * WIDTH + x] - c * sh_A[y_src * WIDTH + x];
                                }
                        }
                }

                bsg_tile_group_barrier(&r_barrier, &c_barrier);
        }


        bsg_tile_group_barrier(&r_barrier, &c_barrier);
      

        // Store result matrix back to DRAM
        for (int y = __bsg_y; y < HEIGHT; y += bsg_tiles_Y) {
                for (int x = __bsg_x; x < WIDTH; x += bsg_tiles_X) {
                        A[y * WIDTH + x] = sh_A[y * WIDTH + x];
                }
        }



        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_gaussian_elimination (float* A,
                                                                     int HEIGHT,
                                                                     int WIDTH) {

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = gaussian_elimination_sh_mem<8,8> (A);

                bsg_cuda_print_stat_end(0);

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
