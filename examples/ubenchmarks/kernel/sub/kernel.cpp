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
    int  __attribute__ ((noinline)) kernel_sub(int arg) {
        asm volatile(
					"li t0, 0x82c5e484;"
					"li t1, 0x7e50c751;"
					"li t2, 0xf51c245a;"
					"li a0, 0xeebb1990;"
					"li a1, 0x24181de1;"
					"li a2, 0xc543c6da;"
					"li a3, 0xdb976d24;"
					"li a4, 0xb6cf86fe;"
					"li a5, 0x14328be3;"
					"li a3, 0xeeedcd85;"
					"li a7, 0xd5df6f27;"
					"li s2, 0xab08ce2f;"
					"li s3, 0x1dba1fc6;"
					"li s4, 0xabc4a4d7;"
					"li s5, 0x7e8219d3;"
					"li s6, 0x85797b72;"
					"li s7, 0xfe6ea025;"
					"li s8, 0x07a431cd;"
					"li s9, 0x824c23a9;"
					"li s10, 0x518f6155;"
					"li s11, 0xee69200c;"
					"li t3, 0xe1f08d83;"
					"li t4, 0x108d7348;"
					"li t5, 0xd5dddacf;"
					"li t6, 0xce2d28bd;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: sub t0, t1, t2;"
					"m1: sub t1, t2, a0;"
					"m2: sub t2, a0, a1;"
					"m3: sub a0, a1, a2;"
					"m4: sub a1, a2, a3;"
					"m5: sub a2, a3, a4;"
					"m6: sub a3, a4, a5;"
					"m7: sub a4, a5, a3;"
					"m8: sub a5, a3, a7;"
					"m9: sub a3, a7, s2;"
					"m10: sub a7, s2, s3;"
					"m11: sub s2, s3, s4;"
					"m12: sub s3, s4, s5;"
					"m13: sub s4, s5, s6;"
					"m14: sub s5, s6, s7;"
					"m15: sub s6, s7, s8;"
					"m16: sub s7, s8, s9;"
					"m17: sub s8, s9, s10;"
					"m18: sub s9, s10, s11;"
					"m19: sub s10, s11, t3;"
					"m20: sub s11, t3, t4;"
					"m21: sub t3, t4, t5;"
					"m22: sub t4, t5, t6;"
					"m23: sub t5, t6, t0;"
					"m24: sub t6, t0, t1;"
					"m25: sub t0, t1, t2;"
					"m26: sub t1, t2, a0;"
					"m27: sub t2, a0, a1;"
					"m28: sub a0, a1, a2;"
					"m29: sub a1, a2, a3;"
					"m30: sub a2, a3, a4;"
					"m31: sub a3, a4, a5;"
					"m32: sub a4, a5, a3;"
					"m33: sub a5, a3, a7;"
					"m34: sub a3, a7, s2;"
					"m35: sub a7, s2, s3;"
					"m36: sub s2, s3, s4;"
					"m37: sub s3, s4, s5;"
					"m38: sub s4, s5, s6;"
					"m39: sub s5, s6, s7;"
					"m40: sub s6, s7, s8;"
					"m41: sub s7, s8, s9;"
					"m42: sub s8, s9, s10;"
					"m43: sub s9, s10, s11;"
					"m44: sub s10, s11, t3;"
					"m45: sub s11, t3, t4;"
					"m46: sub t3, t4, t5;"
					"m47: sub t4, t5, t6;"
					"m48: sub t5, t6, t0;"
					"m49: sub t6, t0, t1;"
					"m50: sub t0, t1, t2;"
					"m51: sub t1, t2, a0;"
					"m52: sub t2, a0, a1;"
					"m53: sub a0, a1, a2;"
					"m54: sub a1, a2, a3;"
					"m55: sub a2, a3, a4;"
					"m56: sub a3, a4, a5;"
					"m57: sub a4, a5, a3;"
					"m58: sub a5, a3, a7;"
					"m59: sub a3, a7, s2;"
					"m60: sub a7, s2, s3;"
					"m61: sub s2, s3, s4;"
					"m62: sub s3, s4, s5;"
					"m63: sub s4, s5, s6;"
					"m64: sub s5, s6, s7;"
					"m65: sub s6, s7, s8;"
					"m66: sub s7, s8, s9;"
					"m67: sub s8, s9, s10;"
					"m68: sub s9, s10, s11;"
					"m69: sub s10, s11, t3;"
					"m70: sub s11, t3, t4;"
					"m71: sub t3, t4, t5;"
					"m72: sub t4, t5, t6;"
					"m73: sub t5, t6, t0;"
					"m74: sub t6, t0, t1;"
					"m75: sub t0, t1, t2;"
					"m76: sub t1, t2, a0;"
					"m77: sub t2, a0, a1;"
					"m78: sub a0, a1, a2;"
					"m79: sub a1, a2, a3;"
					"m80: sub a2, a3, a4;"
					"m81: sub a3, a4, a5;"
					"m82: sub a4, a5, a3;"
					"m83: sub a5, a3, a7;"
					"m84: sub a3, a7, s2;"
					"m85: sub a7, s2, s3;"
					"m86: sub s2, s3, s4;"
					"m87: sub s3, s4, s5;"
					"m88: sub s4, s5, s6;"
					"m89: sub s5, s6, s7;"
					"m90: sub s6, s7, s8;"
					"m91: sub s7, s8, s9;"
					"m92: sub s8, s9, s10;"
					"m93: sub s9, s10, s11;"
					"m94: sub s10, s11, t3;"
					"m95: sub s11, t3, t4;"
					"m96: sub t3, t4, t5;"
					"m97: sub t4, t5, t6;"
					"m98: sub t5, t6, t0;"
					"m99: sub t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
