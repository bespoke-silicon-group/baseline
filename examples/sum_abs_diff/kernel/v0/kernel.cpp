// This kernel performs sum of absolute differences (SAD) between a 
// Reference matrix and a frame matrix. 
// The kernel searches over the reference matrix, and calculates 
// sum of absolute differnces for every sub-matrix that matches 
// the sizes of the frame matrix, and stores the result for that 
// location into result matrix. 

// TEMPLATE_TG_DIM_X/Y must be defined before bsg_manycore.h is
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.

#define TEMPLATE_TG_DIM_X 4
#define TEMPLATE_TG_DIM_Y 4
#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y

#include <bsg_manycore.h>
#include <sum_abs_diff.hpp>
#include <bsg_tile_group_barrier.hpp>


bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


// Version 0 - Multiple work per tile
// In this version, each tile performs multiple units of work. The workload share 
// of each tile group is defined by block_size_x/y and passed to the kernel. Each 
// tile then performs the kernel in a loop, with each iteration belonging to a 
// unit of work (or vitual thread).
template <int TG_DIM_X, int TG_DIM_Y, typename T>
    int  __attribute__ ((noinline)) sum_abs_diff (T *REF, T *FRAME, T *RES,
                                                  uint32_t REF_HEIGHT,
                                                  uint32_t REF_WIDTH,
                                                  uint32_t FRAME_HEIGHT,
                                                  uint32_t FRAME_WIDTH,
                                                  uint32_t RES_HEIGHT,
                                                  uint32_t RES_WIDTH,
                                                  uint32_t block_size_y,
                                                  uint32_t block_size_x) {
    
        int tg_start_y = __bsg_tile_group_id_y * block_size_y;
        int tg_end_y   = MIN (tg_start_y + block_size_y, RES_HEIGHT);
        int tg_start_x = __bsg_tile_group_id_x * block_size_x;
        int tg_end_x   = MIN (tg_start_x + block_size_x, RES_WIDTH);
    
        for (int iter_y = tg_start_y + bsg_y; iter_y < tg_end_y; iter_y += TG_DIM_Y) {
            for (int iter_x = tg_start_x + bsg_x; iter_x < tg_end_x; iter_x += TG_DIM_X) {
    
                int start_y = iter_y;
                int end_y = iter_y + FRAME_HEIGHT;
                int start_x = iter_x;
                int end_x = iter_x + FRAME_WIDTH;
    
                T sad = 0;
                for (int y = start_y; y < end_y; y ++) {
                    for (int x = start_x; x < end_x; x ++) {
                        sad += ABS ( (REF [y * REF_WIDTH + x] - FRAME [(y - start_y) * FRAME_WIDTH + (x - start_x)]) );
                    }
                }
    
                RES [iter_y * RES_WIDTH + iter_x] = sad;
            }
        }
    
        return 0;
    }


extern "C" {
    int  __attribute__ ((noinline)) kernel_sum_abs_diff(float *REF,
                                                        float *FRAME,
                                                        float *RES,
                                                        uint32_t REF_HEIGHT,
                                                        uint32_t REF_WIDTH,
                                                        uint32_t FRAME_HEIGHT,
                                                        uint32_t FRAME_WIDTH,
                                                        uint32_t RES_HEIGHT,
                                                        uint32_t RES_WIDTH,
                                                        uint32_t block_size_y,
                                                        uint32_t block_size_x) {

        int rc;
        bsg_cuda_print_stat_kernel_start();

        rc = sum_abs_diff<TEMPLATE_TG_DIM_X,
                          TEMPLATE_TG_DIM_Y> (REF, FRAME, RES,
                                              REF_HEIGHT,
                                              REF_WIDTH,
                                              FRAME_HEIGHT,
                                              FRAME_WIDTH,
                                              RES_HEIGHT,
                                              RES_WIDTH,
                                              block_size_y,
                                              block_size_x);

        barrier.sync();

        bsg_cuda_print_stat_kernel_end();

        return rc;
    }
}
