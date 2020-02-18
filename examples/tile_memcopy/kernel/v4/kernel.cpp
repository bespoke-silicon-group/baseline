// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a simple for loop to copy data to rtemp, then write to DMEM
//   * Unrolled by a factor of FACTOR (gcc pragma says 8, but array size dictates limit)
//   * Asm looks like lw/lw/lw/lw/sw/sw/sw/sw (4 loads in flight before stall)

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

#define FACTOR 4
void bsg_memcopy(const int *src,
                 const uint32_t i_nelements,
                 int *dest){

        const int *psrc = &src[0];
        int *pdest = &dest[0];
        register int rtemp[FACTOR];

        for(int j = 0; j < i_nelements; j+= FACTOR){
#pragma GCC unroll 8
                for (int f = 0 ; f < FACTOR; ++f){
                        rtemp[f] = *psrc++;
                }

#pragma GCC unroll 8
                for (int f = 0 ; f < FACTOR; ++f){
                        *pdest++ = rtemp[f];
                }
        }
        return;
}

extern "C" {
        __attribute__((noinline))
        int kernel_tile_memcopy(const int *INPUT,
                                const uint32_t i_nelements,
                                int *OUTPUT)
        {
                int rc;

                int temp[i_nelements];
                for(int i = 0; i < 4; i += 2){
                        bsg_cuda_print_stat_start(i);
                        bsg_memcopy(INPUT, i_nelements, temp);
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
