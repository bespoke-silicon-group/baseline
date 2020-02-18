// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a simple for loop to copy data.
//   * Unrolled by a factor of 2
//   * Asm looks like lw/sw/lw/sw (instead of lw/lw/sw/sw goal)
//     * lw/sw raw dependendencies cause a round-Trip latency on every element

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
#include <cstdint>
#include <cstring>

extern "C" {
        __attribute__((noinline))
        int kernel_tile_memcopy(const int *INPUT,
                               const uint32_t i_nelements,
                               int *OUTPUT)
        {
                int rc;

                int temp[i_nelements];

                for(int i = 0; i < 4; i+=2){
                        bsg_cuda_print_stat_start(i);
                        // This fails miserably, since gcc does lw/sw/lw/sw instead of lw/lw/sw/sw
#pragma GCC unroll 2
                        for(int j = 0; j < i_nelements; ++j){
                                temp[j] = INPUT[j];
                        }
                        bsg_cuda_print_stat_end(i);

                        for(int j = 0; j < i_nelements; ++j){
                                temp[j] += 1;
                        }
                                
                        bsg_cuda_print_stat_start(i + 1);
                        for(int j = 0; j < i_nelements; ++j){
                                OUTPUT[j] = temp[j];
                        }
                        bsg_cuda_print_stat_end(i + 1);
                }

                return rc;
        }
}
