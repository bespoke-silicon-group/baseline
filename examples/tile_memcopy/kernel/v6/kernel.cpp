// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a simple for loop to copy data to rtemp, then write to DMEM
//   * Unrolled by a factor of FACTOR (gcc pragma says 16, but array size/FACTOR dictates limit)
//   * Asm looks like lw/*/sw* (16 loads in flight before stall),
//   * HOWEVER sw dependencies are not the same order as the lw producers. See:


/*
#pragma GCC unroll 16
                for (int f = 0 ; f < FACTOR; ++f){
                        rtemp[f] = *psrc++;
 44c:	00452903          	lw	x18,4(x10)
 450:	00852483          	lw	x9,8(x10)
 454:	00c52403          	lw	x8,12(x10)
 458:	01052583          	lw	x11,16(x10)
 45c:	01452383          	lw	x7,20(x10)
 460:	01852283          	lw	x5,24(x10)
 464:	01c52f83          	lw	x31,28(x10)
 468:	02052f03          	lw	x30,32(x10)
 46c:	02452e83          	lw	x29,36(x10)
 470:	02852e03          	lw	x28,40(x10)
 474:	02c52303          	lw	x6,44(x10)
 478:	03052883          	lw	x17,48(x10)
 47c:	03452803          	lw	x16,52(x10)
 480:	03852683          	lw	x13,56(x10)
 484:	03c52703          	lw	x14,60(x10)
                }

#pragma GCC unroll 16
                for (int f = 0 ; f < FACTOR; ++f){
                        *pdest++ = rtemp[f];
 488:	00052a03          	lw	x20,0(x10)
        for(int j = 0; j < i_nelements; j+= FACTOR){
 48c:	01078793          	addi	x15,x15,16
                        *pdest++ = rtemp[f];
 490:	01262223          	sw	x18,4(x12) // First lw
 494:	01462023          	sw	x20,0(x12) // Last lw !?
 498:	00962423          	sw	x9,8(x12)
 49c:	00862623          	sw	x8,12(x12)
 4a0:	00b62823          	sw	x11,16(x12)
 4a4:	00762a23          	sw	x7,20(x12)
 4a8:	00562c23          	sw	x5,24(x12)
 4ac:	01f62e23          	sw	x31,28(x12)
 4b0:	03e62023          	sw	x30,32(x12)
 4b4:	03d62223          	sw	x29,36(x12)
 4b8:	03c62423          	sw	x28,40(x12)
 4bc:	02662623          	sw	x6,44(x12)
 4c0:	03162823          	sw	x17,48(x12)
 4c4:	03062a23          	sw	x16,52(x12)
 4c8:	02d62c23          	sw	x13,56(x12)
 4cc:	02e62e23          	sw	x14,60(x12)
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
#include <cstdint>

#define FACTOR 16
void bsg_memcopy(const int *src,
                 const uint32_t i_nelements,
                 int *dest){

        const int *psrc = &src[0];
        int *pdest = &dest[0];
        register int rtemp[FACTOR];

        for(int j = 0; j < i_nelements; j+= FACTOR){
#pragma GCC unroll 16
                for (int f = 0 ; f < FACTOR; ++f){
                        rtemp[f] = *psrc++;
                }

#pragma GCC unroll 16
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
