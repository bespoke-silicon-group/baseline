/*
 * This kernel performs sum of absolute differences (SAD) between a 
 * Reference matrix and a frame matrix. 
 * The kernel searches over the reference matrix, and calculates 
 * sum of absolute differnces for every sub-matrix that matches 
 * the sizes of the frame matrix, and stores the result for that 
 * location into result matrix. 
 * TODO: more explanation 
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
                rc = sum_abs_diff_single_work_per_tile  (REF, FRAME, RES,
                                                         REF_HEIGHT, REF_WIDTH,
                                                         FRAME_HEIGHT, FRAME_WIDTH,
                                                         RES_HEIGHT, RES_WIDTH);
                bsg_cuda_print_stat_end(0);

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
