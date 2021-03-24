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
    int  __attribute__ ((noinline)) kernel_mv(int arg) {
        asm volatile(
					"li t0, 0xbc3d9b9f;"
					"li t1, 0xa89ad265;"
					"li t2, 0x47b3c153;"
					"li a0, 0xc540e9a9;"
					"li a1, 0xba438f89;"
					"li a2, 0xfc85ebc0;"
					"li a3, 0x1389e06c;"
					"li a4, 0xf39beb21;"
					"li a5, 0x4de655b6;"
					"li a3, 0x66f85e5b;"
					"li a7, 0xfb838c95;"
					"li s2, 0xb54af11a;"
					"li s3, 0x47bc2ade;"
					"li s4, 0xae66a87b;"
					"li s5, 0xac404ecf;"
					"li s6, 0xacfdc65f;"
					"li s7, 0xca526eec;"
					"li s8, 0x1ea70b10;"
					"li s9, 0x4a18d175;"
					"li s10, 0x82cec68a;"
					"li s11, 0xdc3e64ad;"
					"li t3, 0xce3b63a0;"
					"li t4, 0x3215f2ce;"
					"li t5, 0xa4fb1e4e;"
					"li t6, 0xac026762;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: mv t0, t1;"
					"m1: mv t1, t2;"
					"m2: mv t2, a0;"
					"m3: mv a0, a1;"
					"m4: mv a1, a2;"
					"m5: mv a2, a3;"
					"m6: mv a3, a4;"
					"m7: mv a4, a5;"
					"m8: mv a5, a3;"
					"m9: mv a3, a7;"
					"m10: mv a7, s2;"
					"m11: mv s2, s3;"
					"m12: mv s3, s4;"
					"m13: mv s4, s5;"
					"m14: mv s5, s6;"
					"m15: mv s6, s7;"
					"m16: mv s7, s8;"
					"m17: mv s8, s9;"
					"m18: mv s9, s10;"
					"m19: mv s10, s11;"
					"m20: mv s11, t3;"
					"m21: mv t3, t4;"
					"m22: mv t4, t5;"
					"m23: mv t5, t6;"
					"m24: mv t6, t0;"
					"m25: mv t0, t1;"
					"m26: mv t1, t2;"
					"m27: mv t2, a0;"
					"m28: mv a0, a1;"
					"m29: mv a1, a2;"
					"m30: mv a2, a3;"
					"m31: mv a3, a4;"
					"m32: mv a4, a5;"
					"m33: mv a5, a3;"
					"m34: mv a3, a7;"
					"m35: mv a7, s2;"
					"m36: mv s2, s3;"
					"m37: mv s3, s4;"
					"m38: mv s4, s5;"
					"m39: mv s5, s6;"
					"m40: mv s6, s7;"
					"m41: mv s7, s8;"
					"m42: mv s8, s9;"
					"m43: mv s9, s10;"
					"m44: mv s10, s11;"
					"m45: mv s11, t3;"
					"m46: mv t3, t4;"
					"m47: mv t4, t5;"
					"m48: mv t5, t6;"
					"m49: mv t6, t0;"
					"m50: mv t0, t1;"
					"m51: mv t1, t2;"
					"m52: mv t2, a0;"
					"m53: mv a0, a1;"
					"m54: mv a1, a2;"
					"m55: mv a2, a3;"
					"m56: mv a3, a4;"
					"m57: mv a4, a5;"
					"m58: mv a5, a3;"
					"m59: mv a3, a7;"
					"m60: mv a7, s2;"
					"m61: mv s2, s3;"
					"m62: mv s3, s4;"
					"m63: mv s4, s5;"
					"m64: mv s5, s6;"
					"m65: mv s6, s7;"
					"m66: mv s7, s8;"
					"m67: mv s8, s9;"
					"m68: mv s9, s10;"
					"m69: mv s10, s11;"
					"m70: mv s11, t3;"
					"m71: mv t3, t4;"
					"m72: mv t4, t5;"
					"m73: mv t5, t6;"
					"m74: mv t6, t0;"
					"m75: mv t0, t1;"
					"m76: mv t1, t2;"
					"m77: mv t2, a0;"
					"m78: mv a0, a1;"
					"m79: mv a1, a2;"
					"m80: mv a2, a3;"
					"m81: mv a3, a4;"
					"m82: mv a4, a5;"
					"m83: mv a5, a3;"
					"m84: mv a3, a7;"
					"m85: mv a7, s2;"
					"m86: mv s2, s3;"
					"m87: mv s3, s4;"
					"m88: mv s4, s5;"
					"m89: mv s5, s6;"
					"m90: mv s6, s7;"
					"m91: mv s7, s8;"
					"m92: mv s8, s9;"
					"m93: mv s9, s10;"
					"m94: mv s10, s11;"
					"m95: mv s11, t3;"
					"m96: mv t3, t4;"
					"m97: mv t4, t5;"
					"m98: mv t5, t6;"
					"m99: mv t6, t0;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
