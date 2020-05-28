/*
 * This kernel performs load and store to tile group shared memory.
 * Templatized matrix dimensions.
 * Using striped array.
 * Stride = 4
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define TEMPLATE_TG_DIM_X 4
#define TEMPLATE_TG_DIM_Y 4
#define TEMPLATE_HEIGHT   32
#define TEMPLATE_WIDTH    32

#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <cstdint>
#include "bsg_striped_array.hpp"
#include <shared_mem.hpp>

using namespace bsg_manycore;

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


template <int TG_DIM_X, int TG_DIM_Y, int HEIGHT, int WIDTH, typename T>
int  __attribute__ ((noinline)) shared_mem_load_store(T *A, T *R) {


        TileGroupStripedArray<T, (HEIGHT * WIDTH), TG_DIM_X, TG_DIM_Y, 4> sh_A;


        for (int y = bsg_y; y < HEIGHT; y += TG_DIM_Y) {
            for (int x = bsg_x; x < WIDTH; x += TG_DIM_X) {
                sh_A[y * WIDTH + x] = A[y * WIDTH + x];
            }
        }

        barrier.sync();

        for (int y = bsg_y; y < HEIGHT; y += TG_DIM_Y) {
            for (int x = bsg_x; x < WIDTH; x += TG_DIM_X) {
                R[y * WIDTH + x] = sh_A[y * WIDTH + x];
            }
        }

        barrier.sync();

        return 0;
}




extern "C" {
        int  __attribute__ ((noinline)) kernel_shared_mem(
                      float *A, float *R,
                      uint32_t HEIGHT, uint32_t WIDTH) {
                int rc;
                bsg_cuda_print_stat_kernel_start();
                rc = shared_mem_load_store<TEMPLATE_TG_DIM_X,
                                           TEMPLATE_TG_DIM_Y,
                                           TEMPLATE_HEIGHT,
                                           TEMPLATE_WIDTH> (A, R);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
