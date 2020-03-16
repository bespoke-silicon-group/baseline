/*
 * This kernel performs sum of absolute differences (SAD) between a 
 * Reference matrix and a frame matrix. 
 * The kernel searches over the reference matrix, and calculates 
 * sum of absolute differnces for every sub-matrix that matches 
 * the sizes of the frame matrix, and stores the result for that 
 * location into result matrix. 
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
#include "bsg_striped_array.hpp"
#include <cstdint>

#include <sum_abs_diff.hpp>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


using namespace bsg_manycore;


/*
 * Version 8 - Using striped tile group shared memory library for storing frame 
 * Due to redundant accesses to DRAM, performance can be improved 
 * by loading frame matrxix into shared meomry and using that for compuation.
 */
template <int FRAME_HEIGHT, int FRAME_WIDTH>
int  __attribute__ ((noinline)) sum_abs_diff_frame_sh_mem_striped (int *REF, int *FRAME, int *RES,
                                                                   uint32_t ref_height, uint32_t ref_width,
                                                                   uint32_t res_height, uint32_t res_width,
                                                                   uint32_t block_size_y, uint32_t block_size_x) {


        TileGroupStripedArray<int, (FRAME_HEIGHT * FRAME_WIDTH), bsg_tiles_X, bsg_tiles_Y, 1> sh_FRAME;


        // Load frame into tile group shared memory
        for (int iter_y = bsg_y; iter_y < FRAME_HEIGHT; iter_y += bsg_tiles_Y) {
                for (int iter_x = bsg_x; iter_x < FRAME_WIDTH; iter_x += bsg_tiles_X) {
                        sh_FRAME[iter_y * FRAME_WIDTH + iter_x] = FRAME[iter_y * FRAME_WIDTH + iter_x];
                }
        }


        // Perform barrier to make sure frame is loaded into tile group shared memory
        bsg_tile_group_barrier (&r_barrier, &c_barrier);


        int tile_group_start_y = __bsg_tile_group_id_y * block_size_y;
        int tile_group_end_y = MIN (tile_group_start_y + block_size_y, res_height);
        int tile_group_start_x = __bsg_tile_group_id_x * block_size_x;
        int tile_group_end_x = MIN (tile_group_start_x + block_size_x, res_width);
 

        for (int iter_y = tile_group_start_y + bsg_y; iter_y < tile_group_end_y; iter_y += bsg_tiles_Y) {
                for (int iter_x = tile_group_start_x + bsg_x; iter_x < tile_group_end_x; iter_x += bsg_tiles_X) {



                        int start_y = iter_y;
                        int end_y = iter_y + FRAME_HEIGHT;
                        int start_x = iter_x;
                        int end_x = iter_x + FRAME_WIDTH;


                        int sad = 0;
                        for (int y = start_y; y < end_y; y ++) {
                                for (int x = start_x; x < end_x; x ++) {
                                        // Load the frame element from tile group shared memory into lc_frame
                                        int lc_frame = sh_FRAME[(y - start_y) * FRAME_WIDTH + (x - start_x)];
                                        sad += ABS ( (REF [y * ref_width + x] - lc_frame) );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}


extern "C" {
        int  __attribute__ ((noinline)) kernel_sum_abs_diff(
                      int *REF, int *FRAME, int *RES,
                      uint32_t REF_HEIGHT, uint32_t REF_WIDTH,
                      uint32_t FRAME_HEIGHT, uint32_t FRAME_WIDTH,
                      uint32_t RES_HEIGHT, uint32_t RES_WIDTH,
                      uint32_t block_size_y, uint32_t block_size_x) {
                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);
                rc = sum_abs_diff_frame_sh_mem_striped<4,4>   (REF, FRAME, RES,
                                                               REF_HEIGHT, REF_WIDTH,
                                                               RES_HEIGHT, RES_WIDTH,
                                                               block_size_y, block_size_x);
                bsg_cuda_print_stat_end(0);

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
