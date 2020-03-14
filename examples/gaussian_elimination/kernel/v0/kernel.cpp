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
#include <cstdint>

#include <gaussian_elimination.hpp>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


/* 
 * Version 0 
 * Each thread is responsible for calculating a row in each step
 * of the computation. Each tile in the tile group can be responsible 
 * for multple threads (i.e. calculating multiple rows).
 * The second loop of the sequential compuation, which loops over all
 * rows to calculate the new values in each step, is broken and divided 
 * among tiles. Each step of the outter loop needs a barrier to sync 
 * the new values of all rows.
 */
template <typename T>
int  __attribute__ ((noinline)) gaussian_elimination (T* A,
                                                      uint32_t HEIGHT,
                                                      uint32_t WIDTH) {


        //bsg_barrier<bsg_tiles_Y, bsg_tiles_X> barrier;

        const int num_tiles = bsg_tiles_X * bsg_tiles_Y;

        for (int y_src = 0; y_src < HEIGHT; y_src ++) {
                // We break this loop, and divide it among tiles in tile group 
                for (int y_dst = __bsg_id; y_dst < HEIGHT; y_dst += num_tiles) {
                        // If the desnitation row, is less that the source row,
                        // there is nothing to be done
                        if (y_dst > y_src) {
                                // Calculate the coefficient
                                // Coefficient = A[y_dst][y_src] / A[y_src][y_src]
                                float c = A[y_dst * WIDTH + y_src] / A[y_src * WIDTH + y_src];

                                for (int x = 0; x < WIDTH; x ++) {
                                        // A[y_dst][x] -= c * A[y_src][x]       
                                        A[y_dst * WIDTH + x] = A[y_dst * WIDTH + x] - c * A[y_src * WIDTH + x];
                                }
                        }
                }

                //barrier.sync();
                bsg_tile_group_barrier(&r_barrier, &c_barrier);
        }


        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_gaussian_elimination (float* A,
                                                                     uint32_t HEIGHT,
                                                                     uint32_t WIDTH) {
                //bsg_barrier <bsg_tiles_Y, bsg_tiles_X> barrier;

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = gaussian_elimination (A,
                                           HEIGHT,
                                           WIDTH);

                bsg_cuda_print_stat_end(0);

                //barrier.sync();
                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
