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
    int  __attribute__ ((noinline)) kernel_or(int arg) {
        asm volatile(
					"li t0, 0x2f02dfa8;"
					"li t1, 0x0e25c496;"
					"li t2, 0x600644b6;"
					"li a0, 0x4ca1512f;"
					"li a1, 0xf79afe86;"
					"li a2, 0x9caf3d36;"
					"li a3, 0xdf5f2dd0;"
					"li a4, 0x54a36c48;"
					"li a5, 0x72e0e7fb;"
					"li a3, 0x9b6583e1;"
					"li a7, 0x5567b065;"
					"li s2, 0xfdd9f25d;"
					"li s3, 0x4fc7ba0a;"
					"li s4, 0x815cb21f;"
					"li s5, 0x11d5b76c;"
					"li s6, 0x7a7b536f;"
					"li s7, 0xb16342f4;"
					"li s8, 0x9b694cdd;"
					"li s9, 0xf43299a0;"
					"li s10, 0x2247f98b;"
					"li s11, 0x872e2c82;"
					"li t3, 0x501334ec;"
					"li t4, 0xa7f0884e;"
					"li t5, 0x48061e73;"
					"li t6, 0xdc65c5f4;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: or t0, t1, t2;"
					"m1: or t1, t2, a0;"
					"m2: or t2, a0, a1;"
					"m3: or a0, a1, a2;"
					"m4: or a1, a2, a3;"
					"m5: or a2, a3, a4;"
					"m6: or a3, a4, a5;"
					"m7: or a4, a5, a3;"
					"m8: or a5, a3, a7;"
					"m9: or a3, a7, s2;"
					"m10: or a7, s2, s3;"
					"m11: or s2, s3, s4;"
					"m12: or s3, s4, s5;"
					"m13: or s4, s5, s6;"
					"m14: or s5, s6, s7;"
					"m15: or s6, s7, s8;"
					"m16: or s7, s8, s9;"
					"m17: or s8, s9, s10;"
					"m18: or s9, s10, s11;"
					"m19: or s10, s11, t3;"
					"m20: or s11, t3, t4;"
					"m21: or t3, t4, t5;"
					"m22: or t4, t5, t6;"
					"m23: or t5, t6, t0;"
					"m24: or t6, t0, t1;"
					"m25: or t0, t1, t2;"
					"m26: or t1, t2, a0;"
					"m27: or t2, a0, a1;"
					"m28: or a0, a1, a2;"
					"m29: or a1, a2, a3;"
					"m30: or a2, a3, a4;"
					"m31: or a3, a4, a5;"
					"m32: or a4, a5, a3;"
					"m33: or a5, a3, a7;"
					"m34: or a3, a7, s2;"
					"m35: or a7, s2, s3;"
					"m36: or s2, s3, s4;"
					"m37: or s3, s4, s5;"
					"m38: or s4, s5, s6;"
					"m39: or s5, s6, s7;"
					"m40: or s6, s7, s8;"
					"m41: or s7, s8, s9;"
					"m42: or s8, s9, s10;"
					"m43: or s9, s10, s11;"
					"m44: or s10, s11, t3;"
					"m45: or s11, t3, t4;"
					"m46: or t3, t4, t5;"
					"m47: or t4, t5, t6;"
					"m48: or t5, t6, t0;"
					"m49: or t6, t0, t1;"
					"m50: or t0, t1, t2;"
					"m51: or t1, t2, a0;"
					"m52: or t2, a0, a1;"
					"m53: or a0, a1, a2;"
					"m54: or a1, a2, a3;"
					"m55: or a2, a3, a4;"
					"m56: or a3, a4, a5;"
					"m57: or a4, a5, a3;"
					"m58: or a5, a3, a7;"
					"m59: or a3, a7, s2;"
					"m60: or a7, s2, s3;"
					"m61: or s2, s3, s4;"
					"m62: or s3, s4, s5;"
					"m63: or s4, s5, s6;"
					"m64: or s5, s6, s7;"
					"m65: or s6, s7, s8;"
					"m66: or s7, s8, s9;"
					"m67: or s8, s9, s10;"
					"m68: or s9, s10, s11;"
					"m69: or s10, s11, t3;"
					"m70: or s11, t3, t4;"
					"m71: or t3, t4, t5;"
					"m72: or t4, t5, t6;"
					"m73: or t5, t6, t0;"
					"m74: or t6, t0, t1;"
					"m75: or t0, t1, t2;"
					"m76: or t1, t2, a0;"
					"m77: or t2, a0, a1;"
					"m78: or a0, a1, a2;"
					"m79: or a1, a2, a3;"
					"m80: or a2, a3, a4;"
					"m81: or a3, a4, a5;"
					"m82: or a4, a5, a3;"
					"m83: or a5, a3, a7;"
					"m84: or a3, a7, s2;"
					"m85: or a7, s2, s3;"
					"m86: or s2, s3, s4;"
					"m87: or s3, s4, s5;"
					"m88: or s4, s5, s6;"
					"m89: or s5, s6, s7;"
					"m90: or s6, s7, s8;"
					"m91: or s7, s8, s9;"
					"m92: or s8, s9, s10;"
					"m93: or s9, s10, s11;"
					"m94: or s10, s11, t3;"
					"m95: or s11, t3, t4;"
					"m96: or t3, t4, t5;"
					"m97: or t4, t5, t6;"
					"m98: or t5, t6, t0;"
					"m99: or t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
