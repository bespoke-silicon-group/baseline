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
    int  __attribute__ ((noinline)) kernel_and(int arg) {
        asm volatile(
					"li t0, 0x0ff9e3d1;"
					"li t1, 0x7805ba21;"
					"li t2, 0x538ef62b;"
					"li a0, 0x8732489b;"
					"li a1, 0xd8d9f09a;"
					"li a2, 0xfdbf5cb2;"
					"li a3, 0xb4738f7f;"
					"li a4, 0xae0067ab;"
					"li a5, 0xfb4d7e34;"
					"li a3, 0x760a8df3;"
					"li a7, 0xe258a084;"
					"li s2, 0x8849e0d2;"
					"li s3, 0xd4bda243;"
					"li s4, 0xb89057dc;"
					"li s5, 0x582c4338;"
					"li s6, 0xbaf4d36e;"
					"li s7, 0xe8281f2a;"
					"li s8, 0x7ca37de7;"
					"li s9, 0xfa0414c2;"
					"li s10, 0xb1334c04;"
					"li s11, 0xa943e459;"
					"li t3, 0x9a89ad06;"
					"li t4, 0x7bc3156d;"
					"li t5, 0xbbf2d757;"
					"li t6, 0xb0a01967;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: and t0, t1, t2;"
					"m1: and t1, t2, a0;"
					"m2: and t2, a0, a1;"
					"m3: and a0, a1, a2;"
					"m4: and a1, a2, a3;"
					"m5: and a2, a3, a4;"
					"m6: and a3, a4, a5;"
					"m7: and a4, a5, a3;"
					"m8: and a5, a3, a7;"
					"m9: and a3, a7, s2;"
					"m10: and a7, s2, s3;"
					"m11: and s2, s3, s4;"
					"m12: and s3, s4, s5;"
					"m13: and s4, s5, s6;"
					"m14: and s5, s6, s7;"
					"m15: and s6, s7, s8;"
					"m16: and s7, s8, s9;"
					"m17: and s8, s9, s10;"
					"m18: and s9, s10, s11;"
					"m19: and s10, s11, t3;"
					"m20: and s11, t3, t4;"
					"m21: and t3, t4, t5;"
					"m22: and t4, t5, t6;"
					"m23: and t5, t6, t0;"
					"m24: and t6, t0, t1;"
					"m25: and t0, t1, t2;"
					"m26: and t1, t2, a0;"
					"m27: and t2, a0, a1;"
					"m28: and a0, a1, a2;"
					"m29: and a1, a2, a3;"
					"m30: and a2, a3, a4;"
					"m31: and a3, a4, a5;"
					"m32: and a4, a5, a3;"
					"m33: and a5, a3, a7;"
					"m34: and a3, a7, s2;"
					"m35: and a7, s2, s3;"
					"m36: and s2, s3, s4;"
					"m37: and s3, s4, s5;"
					"m38: and s4, s5, s6;"
					"m39: and s5, s6, s7;"
					"m40: and s6, s7, s8;"
					"m41: and s7, s8, s9;"
					"m42: and s8, s9, s10;"
					"m43: and s9, s10, s11;"
					"m44: and s10, s11, t3;"
					"m45: and s11, t3, t4;"
					"m46: and t3, t4, t5;"
					"m47: and t4, t5, t6;"
					"m48: and t5, t6, t0;"
					"m49: and t6, t0, t1;"
					"m50: and t0, t1, t2;"
					"m51: and t1, t2, a0;"
					"m52: and t2, a0, a1;"
					"m53: and a0, a1, a2;"
					"m54: and a1, a2, a3;"
					"m55: and a2, a3, a4;"
					"m56: and a3, a4, a5;"
					"m57: and a4, a5, a3;"
					"m58: and a5, a3, a7;"
					"m59: and a3, a7, s2;"
					"m60: and a7, s2, s3;"
					"m61: and s2, s3, s4;"
					"m62: and s3, s4, s5;"
					"m63: and s4, s5, s6;"
					"m64: and s5, s6, s7;"
					"m65: and s6, s7, s8;"
					"m66: and s7, s8, s9;"
					"m67: and s8, s9, s10;"
					"m68: and s9, s10, s11;"
					"m69: and s10, s11, t3;"
					"m70: and s11, t3, t4;"
					"m71: and t3, t4, t5;"
					"m72: and t4, t5, t6;"
					"m73: and t5, t6, t0;"
					"m74: and t6, t0, t1;"
					"m75: and t0, t1, t2;"
					"m76: and t1, t2, a0;"
					"m77: and t2, a0, a1;"
					"m78: and a0, a1, a2;"
					"m79: and a1, a2, a3;"
					"m80: and a2, a3, a4;"
					"m81: and a3, a4, a5;"
					"m82: and a4, a5, a3;"
					"m83: and a5, a3, a7;"
					"m84: and a3, a7, s2;"
					"m85: and a7, s2, s3;"
					"m86: and s2, s3, s4;"
					"m87: and s3, s4, s5;"
					"m88: and s4, s5, s6;"
					"m89: and s5, s6, s7;"
					"m90: and s6, s7, s8;"
					"m91: and s7, s8, s9;"
					"m92: and s8, s9, s10;"
					"m93: and s9, s10, s11;"
					"m94: and s10, s11, t3;"
					"m95: and s11, t3, t4;"
					"m96: and t3, t4, t5;"
					"m97: and t4, t5, t6;"
					"m98: and t5, t6, t0;"
					"m99: and t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
