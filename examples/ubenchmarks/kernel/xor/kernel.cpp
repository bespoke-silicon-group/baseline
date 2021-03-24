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
    int  __attribute__ ((noinline)) kernel_xor(int arg) {
        asm volatile(
					"li t0, 0xf78bb89a;"
					"li t1, 0x50c36320;"
					"li t2, 0xb2dbdfab;"
					"li a0, 0xcbd755fb;"
					"li a1, 0x55e9659a;"
					"li a2, 0xce3be9e5;"
					"li a3, 0x48784e60;"
					"li a4, 0x94a94d4a;"
					"li a5, 0xe65d055c;"
					"li a3, 0x1b4715ab;"
					"li a7, 0xd9d6d370;"
					"li s2, 0x48169de4;"
					"li s3, 0x9ec71135;"
					"li s4, 0xb6f21804;"
					"li s5, 0x2750a2a2;"
					"li s6, 0x66fb5841;"
					"li s7, 0x0173dad6;"
					"li s8, 0x3aeae3dd;"
					"li s9, 0x18d05f60;"
					"li s10, 0xa0850446;"
					"li s11, 0x3e9bac8c;"
					"li t3, 0x79673f0c;"
					"li t4, 0x372b02b8;"
					"li t5, 0xd569ee10;"
					"li t6, 0x45692435;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: xor t0, t1, t2;"
					"m1: xor t1, t2, a0;"
					"m2: xor t2, a0, a1;"
					"m3: xor a0, a1, a2;"
					"m4: xor a1, a2, a3;"
					"m5: xor a2, a3, a4;"
					"m6: xor a3, a4, a5;"
					"m7: xor a4, a5, a3;"
					"m8: xor a5, a3, a7;"
					"m9: xor a3, a7, s2;"
					"m10: xor a7, s2, s3;"
					"m11: xor s2, s3, s4;"
					"m12: xor s3, s4, s5;"
					"m13: xor s4, s5, s6;"
					"m14: xor s5, s6, s7;"
					"m15: xor s6, s7, s8;"
					"m16: xor s7, s8, s9;"
					"m17: xor s8, s9, s10;"
					"m18: xor s9, s10, s11;"
					"m19: xor s10, s11, t3;"
					"m20: xor s11, t3, t4;"
					"m21: xor t3, t4, t5;"
					"m22: xor t4, t5, t6;"
					"m23: xor t5, t6, t0;"
					"m24: xor t6, t0, t1;"
					"m25: xor t0, t1, t2;"
					"m26: xor t1, t2, a0;"
					"m27: xor t2, a0, a1;"
					"m28: xor a0, a1, a2;"
					"m29: xor a1, a2, a3;"
					"m30: xor a2, a3, a4;"
					"m31: xor a3, a4, a5;"
					"m32: xor a4, a5, a3;"
					"m33: xor a5, a3, a7;"
					"m34: xor a3, a7, s2;"
					"m35: xor a7, s2, s3;"
					"m36: xor s2, s3, s4;"
					"m37: xor s3, s4, s5;"
					"m38: xor s4, s5, s6;"
					"m39: xor s5, s6, s7;"
					"m40: xor s6, s7, s8;"
					"m41: xor s7, s8, s9;"
					"m42: xor s8, s9, s10;"
					"m43: xor s9, s10, s11;"
					"m44: xor s10, s11, t3;"
					"m45: xor s11, t3, t4;"
					"m46: xor t3, t4, t5;"
					"m47: xor t4, t5, t6;"
					"m48: xor t5, t6, t0;"
					"m49: xor t6, t0, t1;"
					"m50: xor t0, t1, t2;"
					"m51: xor t1, t2, a0;"
					"m52: xor t2, a0, a1;"
					"m53: xor a0, a1, a2;"
					"m54: xor a1, a2, a3;"
					"m55: xor a2, a3, a4;"
					"m56: xor a3, a4, a5;"
					"m57: xor a4, a5, a3;"
					"m58: xor a5, a3, a7;"
					"m59: xor a3, a7, s2;"
					"m60: xor a7, s2, s3;"
					"m61: xor s2, s3, s4;"
					"m62: xor s3, s4, s5;"
					"m63: xor s4, s5, s6;"
					"m64: xor s5, s6, s7;"
					"m65: xor s6, s7, s8;"
					"m66: xor s7, s8, s9;"
					"m67: xor s8, s9, s10;"
					"m68: xor s9, s10, s11;"
					"m69: xor s10, s11, t3;"
					"m70: xor s11, t3, t4;"
					"m71: xor t3, t4, t5;"
					"m72: xor t4, t5, t6;"
					"m73: xor t5, t6, t0;"
					"m74: xor t6, t0, t1;"
					"m75: xor t0, t1, t2;"
					"m76: xor t1, t2, a0;"
					"m77: xor t2, a0, a1;"
					"m78: xor a0, a1, a2;"
					"m79: xor a1, a2, a3;"
					"m80: xor a2, a3, a4;"
					"m81: xor a3, a4, a5;"
					"m82: xor a4, a5, a3;"
					"m83: xor a5, a3, a7;"
					"m84: xor a3, a7, s2;"
					"m85: xor a7, s2, s3;"
					"m86: xor s2, s3, s4;"
					"m87: xor s3, s4, s5;"
					"m88: xor s4, s5, s6;"
					"m89: xor s5, s6, s7;"
					"m90: xor s6, s7, s8;"
					"m91: xor s7, s8, s9;"
					"m92: xor s8, s9, s10;"
					"m93: xor s9, s10, s11;"
					"m94: xor s10, s11, t3;"
					"m95: xor s11, t3, t4;"
					"m96: xor t3, t4, t5;"
					"m97: xor t4, t5, t6;"
					"m98: xor t5, t6, t0;"
					"m99: xor t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
