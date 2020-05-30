/*
 * This kernel performs load and store to tile group shared memory.
 * 2x2 tile group.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define TEMPLATE_TG_DIM_X 2
#define TEMPLATE_TG_DIM_Y 2

#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <cstdint>
#include <shared_mem_load.hpp>

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


template <int TG_DIM_X, int TG_DIM_Y>
int  __attribute__ ((noinline)) shared_mem_load(uint32_t WIDTH) {

	bsg_tile_group_shared_mem (int, sh_A, WIDTH);
        int lc_A[WIDTH];


        for (int i = 0; i < WIDTH; i ++) {
            bsg_tile_group_shared_load (int, sh_A, i, lc_A[i]);
        }

        barrier.sync();

        return 0;
}




extern "C" {
        int  __attribute__ ((noinline)) kernel_shared_mem_load(uint32_t WIDTH) {
                int rc;
                bsg_cuda_print_stat_kernel_start();
                rc = shared_mem_load<TEMPLATE_TG_DIM_X, TEMPLATE_TG_DIM_Y> (WIDTH);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
