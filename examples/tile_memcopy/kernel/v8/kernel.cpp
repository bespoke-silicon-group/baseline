// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a simple for loop to copy data to rtemp, then write to DMEM
//   * rtemp now declared as float
//   * Unrolled by a factor of FACTOR (gcc pragma says 16, but array size/FACTOR dictates limit)
//   * Asm looks like lw/*/sw* (32 loads in flight before stall),
//   * sw dependencies ARE NOT in same order as the lw producers. See:

// * Not optimal, since first fsw depends on last flw.

/*
#pragma GCC unroll 32
                for (int f = 0 ; f < FACTOR; ++f){
                        rtemp[f] = *psrc++;
 464:	00452d07          	flw	f26,4(x10)
 468:	00852c87          	flw	f25,8(x10)
 46c:	00c52c07          	flw	f24,12(x10)
 470:	01052b87          	flw	f23,16(x10)
 474:	01452b07          	flw	f22,20(x10)
 478:	01852a87          	flw	f21,24(x10)
 47c:	01c52a07          	flw	f20,28(x10)
 480:	02052987          	flw	f19,32(x10)
 484:	02452907          	flw	f18,36(x10)
 488:	02852487          	flw	f9,40(x10)
 48c:	02c52407          	flw	f8,44(x10)
 490:	03052f87          	flw	f31,48(x10)
 494:	03452f07          	flw	f30,52(x10)
 498:	03852e87          	flw	f29,56(x10)
 49c:	03c52e07          	flw	f28,60(x10)
 4a0:	04052887          	flw	f17,64(x10)
 4a4:	04452807          	flw	f16,68(x10)
 4a8:	04852387          	flw	f7,72(x10)
 4ac:	04c52307          	flw	f6,76(x10)
 4b0:	05052287          	flw	f5,80(x10)
 4b4:	05452207          	flw	f4,84(x10)
 4b8:	05852187          	flw	f3,88(x10)
 4bc:	05c52107          	flw	f2,92(x10)
 4c0:	06052087          	flw	f1,96(x10)
 4c4:	06452007          	flw	f0,100(x10)
 4c8:	06852507          	flw	f10,104(x10)
 4cc:	06c52587          	flw	f11,108(x10)
 4d0:	07052607          	flw	f12,112(x10)
 4d4:	07452687          	flw	f13,116(x10)
 4d8:	07852707          	flw	f14,120(x10)
 4dc:	07c52787          	flw	f15,124(x10)
                }

#pragma GCC unroll 32
                for (int f = 0 ; f < FACTOR; ++f){
                        *pdest++ = rtemp[f];
 4e0:	00052d87          	flw	f27,0(x10)    // Last flw
        for(int j = 0; j < i_nelements; j+= FACTOR){
 4e4:	02078793          	addi	x15,x15,32
 4e8:	08060613          	addi	x12,x12,128
                        *pdest++ = rtemp[f];
 4ec:	f9b62027          	fsw	f27,-128(x12) // First fsw depends on f27!
 4f0:	f9a62227          	fsw	f26,-124(x12)
 4f4:	f9962427          	fsw	f25,-120(x12)
 4f8:	f9862627          	fsw	f24,-116(x12)
 4fc:	f9762827          	fsw	f23,-112(x12)
 500:	f9662a27          	fsw	f22,-108(x12)
 504:	f9562c27          	fsw	f21,-104(x12)
 508:	f9462e27          	fsw	f20,-100(x12)
 50c:	fb362027          	fsw	f19,-96(x12)
 510:	fb262227          	fsw	f18,-92(x12)
 514:	fa962427          	fsw	f9,-88(x12)
 518:	fa862627          	fsw	f8,-84(x12)
 51c:	fbf62827          	fsw	f31,-80(x12)
 520:	fbe62a27          	fsw	f30,-76(x12)
 524:	fbd62c27          	fsw	f29,-72(x12)
 528:	fbc62e27          	fsw	f28,-68(x12)
 52c:	fd162027          	fsw	f17,-64(x12)
 530:	fd062227          	fsw	f16,-60(x12)
 534:	fc762427          	fsw	f7,-56(x12)
 538:	fc662627          	fsw	f6,-52(x12)
 53c:	fc562827          	fsw	f5,-48(x12)
 540:	fc462a27          	fsw	f4,-44(x12)
 544:	fc362c27          	fsw	f3,-40(x12)
 548:	fc262e27          	fsw	f2,-36(x12)
 54c:	fe162027          	fsw	f1,-32(x12)
 550:	fe062227          	fsw	f0,-28(x12)
 554:	fea62427          	fsw	f10,-24(x12)
 558:	feb62627          	fsw	f11,-20(x12)
 55c:	fec62827          	fsw	f12,-16(x12)
 560:	fed62a27          	fsw	f13,-12(x12)
 564:	fee62c27          	fsw	f14,-8(x12)
 568:	fef62e27          	fsw	f15,-4(x12)
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

#define FACTOR 32
void bsg_memcopy(const int *src,
                 const uint32_t i_nelements,
                 int *dest){

        const float *psrc = reinterpret_cast<const float *>(&src[0]);
        float *pdest = reinterpret_cast<float *>(&dest[0]);
        register float rtemp[FACTOR];

        for(int j = 0; j < i_nelements; j+= FACTOR){
#pragma GCC unroll 32
                for (int f = 0 ; f < FACTOR; ++f){
                        rtemp[f] = *psrc++;
                }

#pragma GCC unroll 32
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
