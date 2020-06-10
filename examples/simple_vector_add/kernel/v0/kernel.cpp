/*
 * This kernel performs vector addition. 
 * 
 * This is the most basic version of single-tile Vector-Vector Addition.
 * This version assumes only a single 1x1 tile group is called.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 1
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, bsg_tiles_X-1, 0, bsg_tiles_Y-1);

#include <vector_add.hpp>
#include <cstring>

extern int bsg_printf(const char*, ...);

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
        int  __attribute__ ((noinline)) kernel_vector_add_int(
                      int * __restrict__ A, int *__restrict__ B, int * __restrict__ C,
                      uint32_t WIDTH) {
                bsg_cuda_print_stat_start(0);
#pragma GCC unroll 8
                for(int iter_x = __bsg_x; iter_x < WIDTH; iter_x += bsg_tiles_X) {
                    C[iter_x] = A[iter_x] + B[iter_x];
                }
                bsg_tile_group_barrier(&r_barrier, &c_barrier);
                bsg_cuda_print_stat_end(0);

                return 0;
        }

}
