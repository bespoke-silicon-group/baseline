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
#include <cstdint>

#include <sum_abs_diff.hpp>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


/*
 * Version 6 - Using tile group shared memory macros for storing frame 
 * Due to redundant accesses to DRAM, performance can be improved 
 * by loading frame matrxix into shared meomry and using that for compuation.
 */
int  __attribute__ ((noinline)) sum_abs_diff_frame_sh_mem_macro (int *REF, int *FRAME, int *RES,
                                                                 uint32_t ref_height, uint32_t ref_width,
                                                                 uint32_t frame_height, uint32_t frame_width,
                                                                 uint32_t res_height, uint32_t res_width,
                                                                 uint32_t block_size_y, uint32_t block_size_x) {


        bsg_tile_group_shared_mem (int, sh_FRAME, (frame_height * frame_width));


        // Load frame into tile group shared memory
        for (int iter_y = bsg_y; iter_y < frame_height; iter_y += bsg_tiles_Y) {
                for (int iter_x = bsg_x; iter_x < frame_width; iter_x += bsg_tiles_X) {
                        bsg_tile_group_shared_store (int, sh_FRAME, (iter_y * frame_width + iter_x), FRAME[iter_y * frame_width + iter_x]);
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
                        int end_y = iter_y + frame_height;
                        int start_x = iter_x;
                        int end_x = iter_x + frame_width;


                        int sad = 0;
                        for (int y = start_y; y < end_y; y ++) {
                                for (int x = start_x; x < end_x; x ++) {
                                        // Load the frame element from tile group shared memory into lc_frame
                                        int lc_frame = bsg_tile_group_shared_load (int, sh_FRAME, ((y - start_y) * frame_width + (x - start_x)), lc_frame);
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
                rc = sum_abs_diff_frame_sh_mem_macro   (REF, FRAME, RES,
                                                        REF_HEIGHT, REF_WIDTH,
                                                        FRAME_HEIGHT, FRAME_WIDTH,
                                                        RES_HEIGHT, RES_WIDTH,
                                                        block_size_y, block_size_x);
                bsg_cuda_print_stat_end(0);

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
