/*
 * This kernel performs load and store to tile group shared memory.
 * Using StripedArray
 * 4x2 tile group
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define TEMPLATE_TG_DIM_X 4
#define TEMPLATE_TG_DIM_Y 2
#define TEMPLATE_WIDTH    64

#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <cstdint>
#include "bsg_striped_array.hpp"
#include <shared_mem_load.hpp>


bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;

using namespace bsg_manycore;



template <int TG_DIM_X, int TG_DIM_Y, int WIDTH>
int  __attribute__ ((noinline)) shared_mem_load() {

        TileGroupStripedArray<int, WIDTH, TG_DIM_X, TG_DIM_Y, 1> sh_A;
        int lc_A[WIDTH];


        for (int i = 0; i < WIDTH; i ++) {
            lc_A[i] = sh_A[i];
        }

        barrier.sync();

        return 0;
}




extern "C" {
        int  __attribute__ ((noinline)) kernel_shared_mem_load(uint32_t WIDTH) {
                int rc;
                bsg_cuda_print_stat_kernel_start();
                rc = shared_mem_load<TEMPLATE_TG_DIM_X, TEMPLATE_TG_DIM_Y, TEMPLATE_WIDTH> ();

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
