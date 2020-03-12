#ifndef __SUM_ABS_DIFF_HPP
#define __SUM_ABS_DIFF_HPP
#include <cstdint>
#include "bsg_striped_array.hpp"

#define ABS(x) ((x) >= 0) ? (x) : (-(x))
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

INIT_TILE_GROUP_BARRIER(rr_barrier, cc_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);



/* 
 * Version 0 - Singler work per tile 
 * In this version, each tile only performs one unit of work, i.e. calculating one
 * element of the result matrix. Based on the size of the result matrix, and the 
 * tile group dimensions, enough tile groups will be launched to populate the 
 * entire result matrix.
 */
int  __attribute__ ((noinline)) sum_abs_diff_single_work_per_tile (int *REF, int *FRAME, int *RES,
                                                                   uint32_t ref_height, uint32_t ref_width,
                                                                   uint32_t frame_height, uint32_t frame_width,
                                                                   uint32_t res_height, uint32_t res_width) {

        int start_y = __bsg_tile_group_id_y * bsg_tiles_Y + bsg_y;
        int end_y   = MIN (start_y + frame_height, res_height);
        int start_x = __bsg_tile_group_id_x * bsg_tiles_X + bsg_x;
        int end_x   = MIN (start_x + frame_width, res_width);


        int sad = 0;
        for (int y = start_y; y < end_y; y ++) {
                for (int x = start_x; x < end_x; x ++) {
                        sad += ABS ( (REF[y * ref_width + x] - FRAME[(y - start_y) * frame_width + (x - start_x)]) );
                }
        }

        RES[start_y * res_width + start_x] = sad;
        return 0;
}



/*
 * Version 1 - Multiple work per tile
 * In this version, each tile performs multiple units of work. The workload share 
 * of each tile group is defined by block_size_x/y and passed to the kernel. Each 
 * tile then performs the kernel in a loop, with each iteration belonging to a 
 * unit of work (or vitual thread).
 */
int  __attribute__ ((noinline)) sum_abs_diff_multiple_work_per_tile (int *REF, int *FRAME, int *RES,
                                                                     uint32_t ref_height, uint32_t ref_width,
                                                                     uint32_t frame_height, uint32_t frame_width,
                                                                     uint32_t res_height, uint32_t res_width,
                                                                     uint32_t block_size_y, uint32_t block_size_x) {


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
                                        sad += ABS ( (REF [y * ref_width + x] - FRAME [(y - start_y) * frame_width + (x - start_x)]) );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}



/*
 * Version 2 - Frame dimensions fixed to 4x4
 * In this version frame dimensions are fixed to 4x4 and 
 * constant numbers are used instead of variables.
 */
int  __attribute__ ((noinline)) sum_abs_diff_fixed_frame_4x4 (int *REF, int *FRAME, int *RES,
                                                                     uint32_t ref_height, uint32_t ref_width,
                                                                     uint32_t res_height, uint32_t res_width,
                                                                     uint32_t block_size_y, uint32_t block_size_x) {


        int tile_group_start_y = __bsg_tile_group_id_y * block_size_y;
        int tile_group_end_y = MIN (tile_group_start_y + block_size_y, res_height);
        int tile_group_start_x = __bsg_tile_group_id_x * block_size_x;
        int tile_group_end_x = MIN (tile_group_start_x + block_size_x, res_width);
 

        for (int iter_y = tile_group_start_y + bsg_y; iter_y < tile_group_end_y; iter_y += bsg_tiles_Y) {
                for (int iter_x = tile_group_start_x + bsg_x; iter_x < tile_group_end_x; iter_x += bsg_tiles_X) {



                        int start_y = iter_y;
                        int end_y = iter_y + 4;
                        int start_x = iter_x;
                        int end_x = iter_x + 4;


                        int sad = 0;
                        for (int y = start_y; y < end_y; y ++) {
                                for (int x = start_x; x < end_x; x ++) {
                                        sad += ABS ( (REF [y * ref_width + x] - FRAME [(y - start_y) << 2 + (x - start_x)]) );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}



/*
 * Version 3 - Frame dimensions templatized
 * In this version, the frame dimensions are templatized in the kernel, instead 
 * of being passed in as an input argument to the kernel. This gives the compiler
 * the opportunity to optimize based on frame dimensions known at compiler time.
 */
template <int FRAME_HEIGHT, int FRAME_WIDTH>
int  __attribute__ ((noinline)) sum_abs_diff_fixed_frame (int *REF, int *FRAME, int *RES,
                                                          uint32_t ref_height, uint32_t ref_width,
                                                          uint32_t res_height, uint32_t res_width,
                                                          uint32_t block_size_y, uint32_t block_size_x) {


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
                                        sad += ABS ( (REF [y * ref_width + x] - FRAME [(y - start_y) * FRAME_WIDTH + (x - start_x)]) );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}





/*
 * Version 4 - Refernce dimensions templatized
 * In this version, the reference dimensions are templatized in the kernel, instead 
 * of being passed in as an input argument to the kernel. This gives the compiler
 * the opportunity to optimize based on reference dimensions known at compiler time.
 */
template <int REF_HEIGHT, int REF_WIDTH>
int  __attribute__ ((noinline)) sum_abs_diff_fixed_reference (int *REF, int *FRAME, int *RES,
                                                          uint32_t frame_height, uint32_t frame_width,
                                                          uint32_t res_height, uint32_t res_width,
                                                          uint32_t block_size_y, uint32_t block_size_x) {


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
                                        sad += ABS ( (REF [y * REF_WIDTH + x] - FRAME [(y - start_y) * frame_width + (x - start_x)]) );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}




/*
 * Version 5 - Refernce and frame dimensions templatized
 * In this version, both the reference and frame dimensions are templatized 
 * in the kernel, instead of being passed in as an input argument to the kernel.
 * This gives the compiler the opportunity to optimize based on reference 
 * dimensions known at compiler time.
 */
template <int REF_HEIGHT, int REF_WIDTH, int FRAME_HEIGHT, int FRAME_WIDTH>
int  __attribute__ ((noinline)) sum_abs_diff_fixed_reference_frame (int *REF, int *FRAME, int *RES,
                                                                    uint32_t block_size_y, uint32_t block_size_x) {


        const int res_height = REF_HEIGHT - FRAME_HEIGHT + 1;
        const int res_width = REF_WIDTH - FRAME_WIDTH + 1;

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
                                        sad += ABS ( (REF [y * REF_WIDTH + x] - FRAME [(y - start_y) * FRAME_WIDTH + (x - start_x)]) );
                                }
                        }


                        RES [iter_y * res_width + iter_x] = sad;

                }
        }

        return 0;
}





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
        bsg_tile_group_barrier (&rr_barrier, &cc_barrier);


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




/*
 * Version 7 - Using tile group shared memory macros for storing refernce & frame 
 * Due to redundant accesses to DRAM, performance can be improved 
 * by loading reference and frame matrxix into shared meomry and 
 * using that for compuation.
 */
int  __attribute__ ((noinline)) sum_abs_diff_reference_frame_sh_mem_macro (int *REF, int *FRAME, int *RES,
                                                                           uint32_t ref_height, uint32_t ref_width,
                                                                           uint32_t frame_height, uint32_t frame_width,
                                                                           uint32_t res_height, uint32_t res_width,
                                                                           uint32_t block_size_y, uint32_t block_size_x) {

        int tile_group_start_y = __bsg_tile_group_id_y * block_size_y;
        int tile_group_end_y = MIN (tile_group_start_y + block_size_y, res_height);
        int tile_group_start_x = __bsg_tile_group_id_x * block_size_x;
        int tile_group_end_x = MIN (tile_group_start_x + block_size_x, res_width);


        const int sh_ref_height = frame_height + block_size_y - 1;
        const int sh_ref_width = frame_width + block_size_x - 1;

        bsg_tile_group_shared_mem (int, sh_FRAME, (frame_height * frame_width));
        bsg_tile_group_shared_mem (int, sh_REF, (sh_ref_height * sh_ref_width));

        // Load frame into tile group shared memory
        for (int iter_y = bsg_y; iter_y < frame_height; iter_y += bsg_tiles_Y) {
                for (int iter_x = bsg_x; iter_x < frame_width; iter_x += bsg_tiles_X) {
                        bsg_tile_group_shared_store (int, sh_FRAME, (iter_y * frame_width + iter_x), FRAME[iter_y * frame_width + iter_x]);
                }
        }


        for (int iter_y = bsg_y; iter_y < sh_ref_height; iter_y += bsg_tiles_Y) {
                for (int iter_x = bsg_x; iter_x < sh_ref_width; iter_x += bsg_tiles_X) {
                        bsg_tile_group_shared_store (int, sh_REF, (iter_y * sh_ref_width + iter_x), REF [((tile_group_start_y + iter_y) * ref_width + (tile_group_start_x + iter_x))]);
                }
        }


        // Perform barrier to make sure frame is loaded into tile group shared memory
        bsg_tile_group_barrier (&rr_barrier, &cc_barrier);



        for (int iter_y = bsg_y; iter_y < sh_ref_height; iter_y += bsg_tiles_Y) {
                for (int iter_x = bsg_x; iter_x < sh_ref_width; iter_x += bsg_tiles_X) {



                        int start_y = iter_y;
                        int end_y = iter_y + frame_height;
                        int start_x = iter_x;
                        int end_x = iter_x + frame_width;


                        int sad = 0;
                        for (int y = start_y; y < end_y; y ++) {
                                for (int x = start_x; x < end_x; x ++) {
                                        // Load the frame element from tile group shared memory into lc_frame
                                        int lc_frame = bsg_tile_group_shared_load (int, sh_FRAME, ((y - start_y) * frame_width + (x - start_x)), lc_frame);
                                        int lc_ref = bsg_tile_group_shared_load (int, sh_REF, (y * sh_ref_width + x), lc_ref);
                                        sad += ABS ( (lc_ref - lc_frame) );
                                }
                        }

                        RES [(tile_group_start_y + iter_y) * res_width + (tile_group_start_x + iter_x)] = sad;
                }
        }


        return 0;
}





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


        bsg_manycore::TileGroupStripedArray<int, (FRAME_HEIGHT * FRAME_WIDTH), bsg_tiles_X, bsg_tiles_Y, 1> sh_FRAME;


        // Load frame into tile group shared memory
        for (int iter_y = bsg_y; iter_y < FRAME_HEIGHT; iter_y += bsg_tiles_Y) {
                for (int iter_x = bsg_x; iter_x < FRAME_WIDTH; iter_x += bsg_tiles_X) {
                        sh_FRAME[iter_y * FRAME_WIDTH + iter_x] = FRAME[iter_y * FRAME_WIDTH + iter_x];
                }
        }


        // Perform barrier to make sure frame is loaded into tile group shared memory
        bsg_tile_group_barrier (&rr_barrier, &cc_barrier);


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













#endif //__SUM_ABS_DIFF_HPP
