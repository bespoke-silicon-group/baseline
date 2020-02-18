// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a simple for loop to copy data to rtemp, then write to DMEM
//   * rtemp now declared as float (Perhaps integer register pressure is causing issues??)
//   * Unrolled by a factor of FACTOR (gcc pragma says 16, but array size/FACTOR dictates limit)
//   * Asm looks like lw/*/sw* (16 loads in flight before stall),
//   * sw dependencies ARE in same order as the lw producers. See:

/*
        const float *psrc = reinterpret_cast<const float *>(&src[0]);
        float *pdest = reinterpret_cast<float *>(&dest[0]);
        register float rtemp[FACTOR];

        for(int j = 0; j < i_nelements; j+= FACTOR){
 428:	08058c63          	beqz	x11,4c0 <_Z11bsg_memcopyPKimPi+0x98>
 42c:	00000793          	li	x15,0
#pragma GCC unroll 16
                for (int f = 0 ; f < FACTOR; ++f){
                        rtemp[f] = *psrc++;
 430:	00052887          	flw	f17,0(x10)
 434:	00452807          	flw	f16,4(x10)
 438:	00852387          	flw	f7,8(x10)
 43c:	00c52307          	flw	f6,12(x10)
 440:	01052287          	flw	f5,16(x10)
 444:	01452207          	flw	f4,20(x10)
 448:	01852187          	flw	f3,24(x10)
 44c:	01c52107          	flw	f2,28(x10)
 450:	02052087          	flw	f1,32(x10)
 454:	02452007          	flw	f0,36(x10)
 458:	02852507          	flw	f10,40(x10)
 45c:	02c52587          	flw	f11,44(x10)
 460:	03052607          	flw	f12,48(x10)
 464:	03452687          	flw	f13,52(x10)
 468:	03852707          	flw	f14,56(x10)
 46c:	03c52787          	flw	f15,60(x10)
        for(int j = 0; j < i_nelements; j+= FACTOR){
 470:	01078793          	addi	x15,x15,16
                }

#pragma GCC unroll 16
                for (int f = 0 ; f < FACTOR; ++f){
                        *pdest++ = rtemp[f];
 474:	01162027          	fsw	f17,0(x12)
 478:	01062227          	fsw	f16,4(x12)
 47c:	00762427          	fsw	f7,8(x12)
 480:	00662627          	fsw	f6,12(x12)
 484:	00562827          	fsw	f5,16(x12)
 488:	00462a27          	fsw	f4,20(x12)
 48c:	00362c27          	fsw	f3,24(x12)
 490:	00262e27          	fsw	f2,28(x12)
 494:	02162027          	fsw	f1,32(x12)
 498:	02062227          	fsw	f0,36(x12)
 49c:	02a62427          	fsw	f10,40(x12)
 4a0:	02b62627          	fsw	f11,44(x12)
 4a4:	02c62827          	fsw	f12,48(x12)
 4a8:	02d62a27          	fsw	f13,52(x12)
 4ac:	02e62c27          	fsw	f14,56(x12)
 4b0:	02f62e27          	fsw	f15,60(x12)
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

        const float *psrc = reinterpret_cast<const float *>(&src[0]);
        float *pdest = reinterpret_cast<float *>(&dest[0]);
        register float rtemp[FACTOR];

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
