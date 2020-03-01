#ifndef __SUM_ABS_DIFF_HPP
#define __SUM_ABS_DIFF_HPP
#include <cstdint>



#define ABS_DIFF(x,y) (x>y) ? (x-y) : (y-x)




int  __attribute__ ((noinline)) single_sum_abs_diff (int *REF, int *FRAME, int *RES,
                                                     uint32_t ref_height, uint32_t ref_width,
                                                     uint32_t frame_height, uint32_t frame_width,
                                                     uint32_t res_height, uint32_t res_width) {

        int start_y = bsg_y;
        int end_y   = start_y + frame_height;
        int start_x = bsg_x;
        int end_x   = start_x + frame_width;


        int sad = 0;
        for (int y = start_y; y < end_y; y ++) {
                for (int x = start_x; x < end_x; x ++) {
                        sad += ABS_DIFF (REF[y * ref_width + x] , FRAME[(y - start_y) * frame_width + (x - start_x)]);
                }
        }

        RES[bsg_y * res_width + bsg_x] = sad;
        return 0;
}



int  __attribute__ ((noinline)) multi_sum_abs_diff (int *REF, int *FRAME, int *RES,
                                                    uint32_t ref_height, uint32_t ref_width,
                                                    uint32_t frame_height, uint32_t frame_width,
                                                    uint32_t res_height, uint32_t res_width,
                                                    uint32_t block_size_y, uint32_t block_size_x) {


        int tile_group_start_y = __bsg_tile_group_id_y * block_size_y;
        int tile_group_end_y = tile_group_start_y + block_size_y;
        int tile_group_start_x = __bsg_tile_group_id_x * block_size_x;
        int tile_group_end_x = tile_group_start_x + block_size_x;
 

        for (int iter_y = tile_group_start_y + bsg_y; iter_y < tile_group_end_y; iter_y += bsg_tiles_Y) {
                for (int iter_x = tile_group_start_x + bsg_x; iter_x < tile_group_end_x; iter_x += bsg_tiles_X) {



                        int start_y = iter_y;
                        int end_y = iter_y + frame_height;
                        int start_x = iter_x;
                        int end_x = iter_x + frame_width;


                        int sad = 0;
                        for (int y = start_y; y < end_y; y ++) {
                                for (int x = start_x; x < end_x; x ++) {
                                        sad += ABS_DIFF ( REF [y * ref_width + x] , FRAME [(y - start_y) * frame_width + (x - start_x)] );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}



#endif //__SUM_ABS_DIFF_HPP
