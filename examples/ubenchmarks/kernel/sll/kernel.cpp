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
    int  __attribute__ ((noinline)) kernel_sll(int arg) {
        asm volatile(
					"li t0, 0xec4ce3be;"
					"li t1, 0x62942048;"
					"li t2, 0x4ea34d2d;"
					"li a0, 0x61674ad4;"
					"li a1, 0xaf269f32;"
					"li a2, 0xed39cd88;"
					"li a3, 0x67d1b64e;"
					"li a4, 0xfaaed796;"
					"li a5, 0xd57e9599;"
					"li a3, 0xfd6fcd99;"
					"li a7, 0x375853db;"
					"li s2, 0xad0a997f;"
					"li s3, 0xfef3f81d;"
					"li s4, 0x4e1326e2;"
					"li s5, 0x1fce2a2b;"
					"li s6, 0x27920b57;"
					"li s7, 0x0da5dcc3;"
					"li s8, 0x5a293bc7;"
					"li s9, 0x200e9df3;"
					"li s10, 0xb9c714a9;"
					"li s11, 0xd3d619c7;"
					"li t3, 0x3d2ad908;"
					"li t4, 0x764d9d69;"
					"li t5, 0x241ae0e8;"
					"li t6, 0x483169f3;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: sll t0, t1, t2;"
					"m1: sll t1, t2, a0;"
					"m2: sll t2, a0, a1;"
					"m3: sll a0, a1, a2;"
					"m4: sll a1, a2, a3;"
					"m5: sll a2, a3, a4;"
					"m6: sll a3, a4, a5;"
					"m7: sll a4, a5, a3;"
					"m8: sll a5, a3, a7;"
					"m9: sll a3, a7, s2;"
					"m10: sll a7, s2, s3;"
					"m11: sll s2, s3, s4;"
					"m12: sll s3, s4, s5;"
					"m13: sll s4, s5, s6;"
					"m14: sll s5, s6, s7;"
					"m15: sll s6, s7, s8;"
					"m16: sll s7, s8, s9;"
					"m17: sll s8, s9, s10;"
					"m18: sll s9, s10, s11;"
					"m19: sll s10, s11, t3;"
					"m20: sll s11, t3, t4;"
					"m21: sll t3, t4, t5;"
					"m22: sll t4, t5, t6;"
					"m23: sll t5, t6, t0;"
					"m24: sll t6, t0, t1;"
					"m25: sll t0, t1, t2;"
					"m26: sll t1, t2, a0;"
					"m27: sll t2, a0, a1;"
					"m28: sll a0, a1, a2;"
					"m29: sll a1, a2, a3;"
					"m30: sll a2, a3, a4;"
					"m31: sll a3, a4, a5;"
					"m32: sll a4, a5, a3;"
					"m33: sll a5, a3, a7;"
					"m34: sll a3, a7, s2;"
					"m35: sll a7, s2, s3;"
					"m36: sll s2, s3, s4;"
					"m37: sll s3, s4, s5;"
					"m38: sll s4, s5, s6;"
					"m39: sll s5, s6, s7;"
					"m40: sll s6, s7, s8;"
					"m41: sll s7, s8, s9;"
					"m42: sll s8, s9, s10;"
					"m43: sll s9, s10, s11;"
					"m44: sll s10, s11, t3;"
					"m45: sll s11, t3, t4;"
					"m46: sll t3, t4, t5;"
					"m47: sll t4, t5, t6;"
					"m48: sll t5, t6, t0;"
					"m49: sll t6, t0, t1;"
					"m50: sll t0, t1, t2;"
					"m51: sll t1, t2, a0;"
					"m52: sll t2, a0, a1;"
					"m53: sll a0, a1, a2;"
					"m54: sll a1, a2, a3;"
					"m55: sll a2, a3, a4;"
					"m56: sll a3, a4, a5;"
					"m57: sll a4, a5, a3;"
					"m58: sll a5, a3, a7;"
					"m59: sll a3, a7, s2;"
					"m60: sll a7, s2, s3;"
					"m61: sll s2, s3, s4;"
					"m62: sll s3, s4, s5;"
					"m63: sll s4, s5, s6;"
					"m64: sll s5, s6, s7;"
					"m65: sll s6, s7, s8;"
					"m66: sll s7, s8, s9;"
					"m67: sll s8, s9, s10;"
					"m68: sll s9, s10, s11;"
					"m69: sll s10, s11, t3;"
					"m70: sll s11, t3, t4;"
					"m71: sll t3, t4, t5;"
					"m72: sll t4, t5, t6;"
					"m73: sll t5, t6, t0;"
					"m74: sll t6, t0, t1;"
					"m75: sll t0, t1, t2;"
					"m76: sll t1, t2, a0;"
					"m77: sll t2, a0, a1;"
					"m78: sll a0, a1, a2;"
					"m79: sll a1, a2, a3;"
					"m80: sll a2, a3, a4;"
					"m81: sll a3, a4, a5;"
					"m82: sll a4, a5, a3;"
					"m83: sll a5, a3, a7;"
					"m84: sll a3, a7, s2;"
					"m85: sll a7, s2, s3;"
					"m86: sll s2, s3, s4;"
					"m87: sll s3, s4, s5;"
					"m88: sll s4, s5, s6;"
					"m89: sll s5, s6, s7;"
					"m90: sll s6, s7, s8;"
					"m91: sll s7, s8, s9;"
					"m92: sll s8, s9, s10;"
					"m93: sll s9, s10, s11;"
					"m94: sll s10, s11, t3;"
					"m95: sll s11, t3, t4;"
					"m96: sll t3, t4, t5;"
					"m97: sll t4, t5, t6;"
					"m98: sll t5, t6, t0;"
					"m99: sll t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
