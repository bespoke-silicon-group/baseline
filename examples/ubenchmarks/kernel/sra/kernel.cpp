/*
 * This kernel prints the Hello World message 
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

#include <ubenchmarks.hpp>

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
    int  __attribute__ ((noinline)) kernel_sra(int arg) {
        asm volatile(
					"li t0, 0xd9a81704;"
					"li t1, 0x25ba7df0;"
					"li t2, 0x0749a39b;"
					"li a0, 0xc6b3b640;"
					"li a1, 0x7b44068c;"
					"li a2, 0x2ae9cd96;"
					"li a3, 0x4efd7d16;"
					"li a4, 0xdd22c99e;"
					"li a5, 0x5249be46;"
					"li a3, 0x24fe64f0;"
					"li a7, 0x118175d0;"
					"li s2, 0xc81a31a8;"
					"li s3, 0x41a697da;"
					"li s4, 0x938364f2;"
					"li s5, 0x5656b31e;"
					"li s6, 0x4243e6dc;"
					"li s7, 0x9d77d8bf;"
					"li s8, 0x6b8d05e9;"
					"li s9, 0xbaf6cd6b;"
					"li s10, 0xdb13bfad;"
					"li s11, 0x7d4aaa2c;"
					"li t3, 0xd50b22ad;"
					"li t4, 0x95a79ffb;"
					"li t5, 0xe2d7351e;"
					"li t6, 0xd3068eec;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: sra t0, t1, t2;"
					"m1: sra t1, t2, a0;"
					"m2: sra t2, a0, a1;"
					"m3: sra a0, a1, a2;"
					"m4: sra a1, a2, a3;"
					"m5: sra a2, a3, a4;"
					"m6: sra a3, a4, a5;"
					"m7: sra a4, a5, a3;"
					"m8: sra a5, a3, a7;"
					"m9: sra a3, a7, s2;"
					"m10: sra a7, s2, s3;"
					"m11: sra s2, s3, s4;"
					"m12: sra s3, s4, s5;"
					"m13: sra s4, s5, s6;"
					"m14: sra s5, s6, s7;"
					"m15: sra s6, s7, s8;"
					"m16: sra s7, s8, s9;"
					"m17: sra s8, s9, s10;"
					"m18: sra s9, s10, s11;"
					"m19: sra s10, s11, t3;"
					"m20: sra s11, t3, t4;"
					"m21: sra t3, t4, t5;"
					"m22: sra t4, t5, t6;"
					"m23: sra t5, t6, t0;"
					"m24: sra t6, t0, t1;"
					"m25: sra t0, t1, t2;"
					"m26: sra t1, t2, a0;"
					"m27: sra t2, a0, a1;"
					"m28: sra a0, a1, a2;"
					"m29: sra a1, a2, a3;"
					"m30: sra a2, a3, a4;"
					"m31: sra a3, a4, a5;"
					"m32: sra a4, a5, a3;"
					"m33: sra a5, a3, a7;"
					"m34: sra a3, a7, s2;"
					"m35: sra a7, s2, s3;"
					"m36: sra s2, s3, s4;"
					"m37: sra s3, s4, s5;"
					"m38: sra s4, s5, s6;"
					"m39: sra s5, s6, s7;"
					"m40: sra s6, s7, s8;"
					"m41: sra s7, s8, s9;"
					"m42: sra s8, s9, s10;"
					"m43: sra s9, s10, s11;"
					"m44: sra s10, s11, t3;"
					"m45: sra s11, t3, t4;"
					"m46: sra t3, t4, t5;"
					"m47: sra t4, t5, t6;"
					"m48: sra t5, t6, t0;"
					"m49: sra t6, t0, t1;"
					"m50: sra t0, t1, t2;"
					"m51: sra t1, t2, a0;"
					"m52: sra t2, a0, a1;"
					"m53: sra a0, a1, a2;"
					"m54: sra a1, a2, a3;"
					"m55: sra a2, a3, a4;"
					"m56: sra a3, a4, a5;"
					"m57: sra a4, a5, a3;"
					"m58: sra a5, a3, a7;"
					"m59: sra a3, a7, s2;"
					"m60: sra a7, s2, s3;"
					"m61: sra s2, s3, s4;"
					"m62: sra s3, s4, s5;"
					"m63: sra s4, s5, s6;"
					"m64: sra s5, s6, s7;"
					"m65: sra s6, s7, s8;"
					"m66: sra s7, s8, s9;"
					"m67: sra s8, s9, s10;"
					"m68: sra s9, s10, s11;"
					"m69: sra s10, s11, t3;"
					"m70: sra s11, t3, t4;"
					"m71: sra t3, t4, t5;"
					"m72: sra t4, t5, t6;"
					"m73: sra t5, t6, t0;"
					"m74: sra t6, t0, t1;"
					"m75: sra t0, t1, t2;"
					"m76: sra t1, t2, a0;"
					"m77: sra t2, a0, a1;"
					"m78: sra a0, a1, a2;"
					"m79: sra a1, a2, a3;"
					"m80: sra a2, a3, a4;"
					"m81: sra a3, a4, a5;"
					"m82: sra a4, a5, a3;"
					"m83: sra a5, a3, a7;"
					"m84: sra a3, a7, s2;"
					"m85: sra a7, s2, s3;"
					"m86: sra s2, s3, s4;"
					"m87: sra s3, s4, s5;"
					"m88: sra s4, s5, s6;"
					"m89: sra s5, s6, s7;"
					"m90: sra s6, s7, s8;"
					"m91: sra s7, s8, s9;"
					"m92: sra s8, s9, s10;"
					"m93: sra s9, s10, s11;"
					"m94: sra s10, s11, t3;"
					"m95: sra s11, t3, t4;"
					"m96: sra t3, t4, t5;"
					"m97: sra t4, t5, t6;"
					"m98: sra t5, t6, t0;"
					"m99: sra t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
