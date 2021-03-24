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
    int  __attribute__ ((noinline)) kernel_srl(int arg) {
        asm volatile(
					"li t0, 0x1c061d3c;"
					"li t1, 0x0991539d;"
					"li t2, 0x5d1991c5;"
					"li a0, 0x8887c109;"
					"li a1, 0xcedeaa37;"
					"li a2, 0xcfd984d9;"
					"li a3, 0xeb77c87f;"
					"li a4, 0x0d3b7e52;"
					"li a5, 0x97696b5a;"
					"li a3, 0xeef8c3cc;"
					"li a7, 0xaca4f3d0;"
					"li s2, 0x37475dbf;"
					"li s3, 0x7338c5e1;"
					"li s4, 0x611f2eed;"
					"li s5, 0xda643f30;"
					"li s6, 0x63ba0c18;"
					"li s7, 0xf70218bc;"
					"li s8, 0xe6d92520;"
					"li s9, 0x713771fb;"
					"li s10, 0x602669c7;"
					"li s11, 0x551303c7;"
					"li t3, 0x2b81c104;"
					"li t4, 0xb4c50b05;"
					"li t5, 0x4737cfa0;"
					"li t6, 0x5e8eb15a;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: srl t0, t1, t2;"
					"m1: srl t1, t2, a0;"
					"m2: srl t2, a0, a1;"
					"m3: srl a0, a1, a2;"
					"m4: srl a1, a2, a3;"
					"m5: srl a2, a3, a4;"
					"m6: srl a3, a4, a5;"
					"m7: srl a4, a5, a3;"
					"m8: srl a5, a3, a7;"
					"m9: srl a3, a7, s2;"
					"m10: srl a7, s2, s3;"
					"m11: srl s2, s3, s4;"
					"m12: srl s3, s4, s5;"
					"m13: srl s4, s5, s6;"
					"m14: srl s5, s6, s7;"
					"m15: srl s6, s7, s8;"
					"m16: srl s7, s8, s9;"
					"m17: srl s8, s9, s10;"
					"m18: srl s9, s10, s11;"
					"m19: srl s10, s11, t3;"
					"m20: srl s11, t3, t4;"
					"m21: srl t3, t4, t5;"
					"m22: srl t4, t5, t6;"
					"m23: srl t5, t6, t0;"
					"m24: srl t6, t0, t1;"
					"m25: srl t0, t1, t2;"
					"m26: srl t1, t2, a0;"
					"m27: srl t2, a0, a1;"
					"m28: srl a0, a1, a2;"
					"m29: srl a1, a2, a3;"
					"m30: srl a2, a3, a4;"
					"m31: srl a3, a4, a5;"
					"m32: srl a4, a5, a3;"
					"m33: srl a5, a3, a7;"
					"m34: srl a3, a7, s2;"
					"m35: srl a7, s2, s3;"
					"m36: srl s2, s3, s4;"
					"m37: srl s3, s4, s5;"
					"m38: srl s4, s5, s6;"
					"m39: srl s5, s6, s7;"
					"m40: srl s6, s7, s8;"
					"m41: srl s7, s8, s9;"
					"m42: srl s8, s9, s10;"
					"m43: srl s9, s10, s11;"
					"m44: srl s10, s11, t3;"
					"m45: srl s11, t3, t4;"
					"m46: srl t3, t4, t5;"
					"m47: srl t4, t5, t6;"
					"m48: srl t5, t6, t0;"
					"m49: srl t6, t0, t1;"
					"m50: srl t0, t1, t2;"
					"m51: srl t1, t2, a0;"
					"m52: srl t2, a0, a1;"
					"m53: srl a0, a1, a2;"
					"m54: srl a1, a2, a3;"
					"m55: srl a2, a3, a4;"
					"m56: srl a3, a4, a5;"
					"m57: srl a4, a5, a3;"
					"m58: srl a5, a3, a7;"
					"m59: srl a3, a7, s2;"
					"m60: srl a7, s2, s3;"
					"m61: srl s2, s3, s4;"
					"m62: srl s3, s4, s5;"
					"m63: srl s4, s5, s6;"
					"m64: srl s5, s6, s7;"
					"m65: srl s6, s7, s8;"
					"m66: srl s7, s8, s9;"
					"m67: srl s8, s9, s10;"
					"m68: srl s9, s10, s11;"
					"m69: srl s10, s11, t3;"
					"m70: srl s11, t3, t4;"
					"m71: srl t3, t4, t5;"
					"m72: srl t4, t5, t6;"
					"m73: srl t5, t6, t0;"
					"m74: srl t6, t0, t1;"
					"m75: srl t0, t1, t2;"
					"m76: srl t1, t2, a0;"
					"m77: srl t2, a0, a1;"
					"m78: srl a0, a1, a2;"
					"m79: srl a1, a2, a3;"
					"m80: srl a2, a3, a4;"
					"m81: srl a3, a4, a5;"
					"m82: srl a4, a5, a3;"
					"m83: srl a5, a3, a7;"
					"m84: srl a3, a7, s2;"
					"m85: srl a7, s2, s3;"
					"m86: srl s2, s3, s4;"
					"m87: srl s3, s4, s5;"
					"m88: srl s4, s5, s6;"
					"m89: srl s5, s6, s7;"
					"m90: srl s6, s7, s8;"
					"m91: srl s7, s8, s9;"
					"m92: srl s8, s9, s10;"
					"m93: srl s9, s10, s11;"
					"m94: srl s10, s11, t3;"
					"m95: srl s11, t3, t4;"
					"m96: srl t3, t4, t5;"
					"m97: srl t4, t5, t6;"
					"m98: srl t5, t6, t0;"
					"m99: srl t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
