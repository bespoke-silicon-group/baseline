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
#define TEMPLATE_FRAME_HEIGHT 4
#define TEMPLATE_FRAME_WIDTH  4
#define TEMPLATE_STRIPE_SIZE  1
#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y

#include <bsg_manycore.h>
#include <sum_abs_diff.hpp>
#include <bsg_tile_group_barrier.hpp>
#include <bsg_shared_mem.hpp>

using namespace bsg_manycore;

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


// Version 3 - Using tile group shared memory macros for storing frame 
// Due to redundant accesses to DRAM, performance can be improved 
// by loading frame matrxix into shared meomry and using that for compuation.
// Using the hardware tile group shared memory in conjunction with 
// it's library bsg_shared_mem.hpp
// This version converts tile group shared memory and 
// input vector pointers into two dimensional matrix 
// references for better understanding of the code and
// easier programming.

template <int TG_DIM_X,
          int TG_DIM_Y,
          int FRAME_HEIGHT,
          int FRAME_WIDTH,
          int STRIPE_SIZE,
          typename T>
    int  __attribute__ ((noinline)) sum_abs_diff (T *ref, T *frame, T *res,
                                                  uint32_t REF_HEIGHT,
                                                  uint32_t REF_WIDTH,
                                                  uint32_t RES_HEIGHT,
                                                  uint32_t RES_WIDTH,
                                                  uint32_t block_size_y,
                                                  uint32_t block_size_x) {

        // Declare tile-group shared array
        TileGroupSharedMem<T, (FRAME_HEIGHT * FRAME_WIDTH), TG_DIM_X, TG_DIM_Y, STRIPE_SIZE> sh_frame;

        // Cast to a 2D reference to the tile group shared array
        T (&sh_frame_2d)[FRAME_HEIGHT][FRAME_WIDTH] = *reinterpret_cast<T (*)[FRAME_HEIGHT][FRAME_WIDTH]> (sh_frame.addr());

        // Create a 2D reference to the input matrices from 1D input pointers
        T (&ref_2d)[REF_HEIGHT][REF_WIDTH] = *reinterpret_cast<T (*)[REF_HEIGHT][REF_WIDTH]> (ref);
        T (&frame_2d)[FRAME_HEIGHT][FRAME_WIDTH] = *reinterpret_cast<T (*)[FRAME_HEIGHT][FRAME_WIDTH]> (frame);
        T (&res_2d)[RES_HEIGHT][RES_WIDTH] = *reinterpret_cast<T (*)[RES_HEIGHT][RES_WIDTH]> (res);


        // Load frame into tile group shared memory
        for (int iter_y = bsg_y; iter_y < FRAME_HEIGHT; iter_y += bsg_tiles_Y) {
            for (int iter_x = bsg_x; iter_x < FRAME_WIDTH; iter_x += bsg_tiles_X) {
                sh_frame_2d[iter_y][iter_x] = frame_2d[iter_y][iter_x];
            }
        }

        // Perform barrier to make sure frame is loaded into tile group shared memory
        barrier.sync();

        int tg_start_y = __bsg_tile_group_id_y * block_size_y;
        int tg_end_y = MIN (tg_start_y + block_size_y, RES_HEIGHT);
        int tg_start_x = __bsg_tile_group_id_x * block_size_x;
        int tg_end_x = MIN (tg_start_x + block_size_x, RES_WIDTH);

        for (int iter_y = tg_start_y + bsg_y; iter_y < tg_end_y; iter_y += bsg_tiles_Y) {
            for (int iter_x = tg_start_x + bsg_x; iter_x < tg_end_x; iter_x += bsg_tiles_X) {

                // Offset the 2D pointer to the reference to start from 
                // the beginning of the sub-matrix to be accesses [iter_y][iter_x]
                T (&ref_2d_offset)[REF_HEIGHT][REF_WIDTH] = *reinterpret_cast<T (*)[REF_HEIGHT][REF_WIDTH]> (&(ref_2d[iter_y][iter_x]));

                T sad = 0;
                for (int y = 0; y < FRAME_HEIGHT; y ++) {
                    for (int x = 0; x < FRAME_WIDTH; x ++) {
                        sad += ABS ( (ref_2d_offset[y][x] - sh_frame_2d[y][x]) );
                    }
                }

                res_2d[iter_y][iter_x] = sad;
            }
        }

        return 0;
    }


extern "C" {
    int  __attribute__ ((noinline)) kernel_sum_abs_diff(float *ref,
                                                        float *frame,
                                                        float *res,
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
                          TEMPLATE_TG_DIM_Y,
                          TEMPLATE_FRAME_HEIGHT,
                          TEMPLATE_FRAME_WIDTH,
                          TEMPLATE_STRIPE_SIZE> (ref, frame, res,
                                                 REF_HEIGHT,
                                                 REF_WIDTH,
                                                 RES_HEIGHT,
                                                 RES_WIDTH,
                                                 block_size_y,
                                                 block_size_x);

        barrier.sync();

        bsg_cuda_print_stat_kernel_end();

        return rc;
    }
}
