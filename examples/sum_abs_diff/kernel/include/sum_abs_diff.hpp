#ifndef __SUM_ABS_DIFF_HPP
#define __SUM_ABS_DIFF_HPP
#include <cstdint>



#define ABS_DIFF(x,y) (x>y) ? (x-y) : (y-x)




int  __attribute__ ((noinline)) single_sum_abs_diff (int *REF, int *FRAME, int *RES,
                                              uint32_t REF_HEIGHT, uint32_t REF_WIDTH,
                                              uint32_t FRAME_HEIGHT, uint32_t FRAME_WIDTH,
                                              uint32_t RES_HEIGHT, uint32_t RES_WIDTH) {

        int start_y = bsg_y;
        int end_y   = start_y + FRAME_HEIGHT;
        int start_x = bsg_x;
        int end_x   = start_x + FRAME_WIDTH;


        int sad = 0;
        for (int iter_y = start_y; iter_y < end_y; iter_y ++) {
                for (int iter_x = start_x; iter_x < end_x; iter_x ++) {
                        sad += ABS_DIFF (REF[iter_y * REF_WIDTH + iter_x] , FRAME[(iter_y - start_y) * FRAME_WIDTH + (iter_x - start_x)]);
                }
        }

        RES[bsg_y * RES_WIDTH + bsg_x] = sad;
        return 0;
}

#endif //__SUM_ABS_DIFF_HPP
