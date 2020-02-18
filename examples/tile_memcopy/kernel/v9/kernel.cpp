// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a for loop to copy data to rtemp, then write to DMEM
//   * For loops use assembly
//   * rtemp now declared as float
//   * Unrolled by a factor of FACTOR (gcc pragma says 16, but array size/FACTOR dictates limit)
//   * Asm looks like lw/*/sw* (32 loads in flight before stall),
//   * sw dependencies ARE in same order as the lw producers. See:

/*
                        asm volatile ("flw %0,%1" : "=f" (rtemp[f]) : "m" (psrc[f]));
 7c0:	00052d87          	flw	f27,0(x10)
 7c4:	00452d07          	flw	f26,4(x10)
 7c8:	00852c87          	flw	f25,8(x10)
 7cc:	00c52c07          	flw	f24,12(x10)
 7d0:	01052b87          	flw	f23,16(x10)
 7d4:	01452b07          	flw	f22,20(x10)
 7d8:	01852a87          	flw	f21,24(x10)
 7dc:	01c52a07          	flw	f20,28(x10)
 7e0:	02052987          	flw	f19,32(x10)
 7e4:	02452907          	flw	f18,36(x10)
 7e8:	02852487          	flw	f9,40(x10)
 7ec:	02c52407          	flw	f8,44(x10)
 7f0:	03052f87          	flw	f31,48(x10)
 7f4:	03452f07          	flw	f30,52(x10)
 7f8:	03852e87          	flw	f29,56(x10)
 7fc:	03c52e07          	flw	f28,60(x10)
 800:	04052887          	flw	f17,64(x10)
 804:	04452807          	flw	f16,68(x10)
 808:	04852387          	flw	f7,72(x10)
 80c:	04c52307          	flw	f6,76(x10)
 810:	05052287          	flw	f5,80(x10)
 814:	05452207          	flw	f4,84(x10)
 818:	05852187          	flw	f3,88(x10)
 81c:	05c52107          	flw	f2,92(x10)
 820:	06052087          	flw	f1,96(x10)
 824:	06452007          	flw	f0,100(x10)
 828:	06852507          	flw	f10,104(x10)
 82c:	06c52587          	flw	f11,108(x10)
 830:	07052607          	flw	f12,112(x10)
 834:	07452687          	flw	f13,116(x10)
 838:	07852707          	flw	f14,120(x10)
 83c:	07c52787          	flw	f15,124(x10)
                        asm volatile ("fsw %1,%0" : "=m" (pdest[f]) : "f" (rtemp[f]));
 840:	01b62027          	fsw	f27,0(x12)
 844:	01a62227          	fsw	f26,4(x12)
 848:	01962427          	fsw	f25,8(x12)
 84c:	01862627          	fsw	f24,12(x12)
 850:	01762827          	fsw	f23,16(x12)
 854:	01662a27          	fsw	f22,20(x12)
 858:	01562c27          	fsw	f21,24(x12)
 85c:	01462e27          	fsw	f20,28(x12)
 860:	03362027          	fsw	f19,32(x12)
 864:	03262227          	fsw	f18,36(x12)
 868:	02962427          	fsw	f9,40(x12)
 86c:	02862627          	fsw	f8,44(x12)
 870:	03f62827          	fsw	f31,48(x12)
 874:	03e62a27          	fsw	f30,52(x12)
 878:	03d62c27          	fsw	f29,56(x12)
 87c:	03c62e27          	fsw	f28,60(x12)
 880:	05162027          	fsw	f17,64(x12)
 884:	05062227          	fsw	f16,68(x12)
 888:	04762427          	fsw	f7,72(x12)
 88c:	04662627          	fsw	f6,76(x12)
 890:	04562827          	fsw	f5,80(x12)
 894:	04462a27          	fsw	f4,84(x12)
 898:	04362c27          	fsw	f3,88(x12)
 89c:	04262e27          	fsw	f2,92(x12)
 8a0:	06162027          	fsw	f1,96(x12)
 8a4:	06062227          	fsw	f0,100(x12)
 8a8:	06a62427          	fsw	f10,104(x12)
 8ac:	06b62627          	fsw	f11,108(x12)
 8b0:	06c62827          	fsw	f12,112(x12)
 8b4:	06d62a27          	fsw	f13,116(x12)
 8b8:	06e62c27          	fsw	f14,120(x12)
 8bc:	06f62e27          	fsw	f15,124(x12)
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

template <unsigned int FACTOR>
__attribute__((noinline))
void bsg_memcopy(const int *src,
                 const uint32_t i_nelements,
                 int *dest){

        const float *psrc  asm ("x10") = reinterpret_cast<const float *>(&src[0]);
        float *pdest asm ("x12") = reinterpret_cast<float *>(&dest[0]);

        for(int j = 0; j < i_nelements; j+= FACTOR){
                float rtemp[FACTOR];
#pragma GCC unroll 32
                for(int f = 0; f < FACTOR; f++){
                        asm volatile ("flw %0,%1" : "=f" (rtemp[f]) : "m" (psrc[f]));
                }

                // Write
#pragma GCC unroll 32
                for(int f = 0; f < FACTOR; f++){
                        asm volatile ("fsw %1,%0" : "=m" (pdest[f]) : "f" (rtemp[f]));
                }
                psrc += FACTOR;
                pdest += FACTOR;
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
                        bsg_memcopy<32>(INPUT, i_nelements, temp);
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
