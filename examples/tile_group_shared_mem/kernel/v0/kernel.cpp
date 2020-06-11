// This kernel uses software tile group shared memory
// using  the bsg_striped_array.hpp library.
// It loads an input array into tile group shared memory
// and stores the array back into a destination in DRAM.
// Results are then compared against the original memory.

// TEMPLATE_TG_DIM_X/Y must be defined before bsg_manycore.h is
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.

#define TEMPLATE_TG_DIM_X 4
#define TEMPLATE_TG_DIM_Y 4
#define TEMPLATE_WIDTH    1024
#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y

#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <tile_group_shared_mem.hpp>
#include <bsg_striped_array.hpp>


using namespace bsg_manycore;

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


template <int TG_DIM_X, int TG_DIM_Y, int WIDTH, typename T>
int  __attribute__ ((noinline)) tile_group_shared_mem_load_store(T *A, T *R) {

    TileGroupStripedArray<T, WIDTH, TG_DIM_X, TG_DIM_Y, 8> sh_A;

    constexpr int block_size = WIDTH / (TG_DIM_X * TG_DIM_Y);
    int start = __bsg_id * block_size;
    int end = start + block_size;

    for (int i = start; i < end; i ++) {
        sh_A[i] = A[i];
    }

    barrier.sync();

    for (int i = start; i < end; i ++) {
        R[i] = sh_A[i];
    }

    barrier.sync();

    return 0;
}


extern "C" {
        int  __attribute__ ((noinline)) kernel_tile_group_shared_mem(
                      float *A, float *R) {
                int rc;
                bsg_cuda_print_stat_kernel_start();

                rc = tile_group_shared_mem_load_store<TEMPLATE_TG_DIM_X,
                                                TEMPLATE_TG_DIM_Y,
                                                TEMPLATE_WIDTH>
                                                (A, R);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
