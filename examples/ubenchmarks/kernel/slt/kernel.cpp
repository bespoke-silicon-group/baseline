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
    int  __attribute__ ((noinline)) kernel_slt(int arg) {
        asm volatile(
					"li t0, 0xca076813;"
					"li t1, 0x2b7204f1;"
					"li t2, 0x459c64d4;"
					"li a0, 0xa170bd71;"
					"li a1, 0xa2dba1db;"
					"li a2, 0xf31e6678;"
					"li a3, 0x7b78e468;"
					"li a4, 0xf57a4396;"
					"li a5, 0x8376116f;"
					"li a3, 0x47b70be4;"
					"li a7, 0xa3756264;"
					"li s2, 0xb20d357e;"
					"li s3, 0x17e0f3b7;"
					"li s4, 0xbd0992e8;"
					"li s5, 0x12b2be8a;"
					"li s6, 0x3209154d;"
					"li s7, 0xd1dac99a;"
					"li s8, 0x3a82910c;"
					"li s9, 0x51045d4c;"
					"li s10, 0x6d5e2f1e;"
					"li s11, 0x1f8d26c8;"
					"li t3, 0xba474632;"
					"li t4, 0x72d93d76;"
					"li t5, 0x7ef73084;"
					"li t6, 0x17f270a4;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: slt t0, t1, t2;"
					"m1: slt t1, t2, a0;"
					"m2: slt t2, a0, a1;"
					"m3: slt a0, a1, a2;"
					"m4: slt a1, a2, a3;"
					"m5: slt a2, a3, a4;"
					"m6: slt a3, a4, a5;"
					"m7: slt a4, a5, a3;"
					"m8: slt a5, a3, a7;"
					"m9: slt a3, a7, s2;"
					"m10: slt a7, s2, s3;"
					"m11: slt s2, s3, s4;"
					"m12: slt s3, s4, s5;"
					"m13: slt s4, s5, s6;"
					"m14: slt s5, s6, s7;"
					"m15: slt s6, s7, s8;"
					"m16: slt s7, s8, s9;"
					"m17: slt s8, s9, s10;"
					"m18: slt s9, s10, s11;"
					"m19: slt s10, s11, t3;"
					"m20: slt s11, t3, t4;"
					"m21: slt t3, t4, t5;"
					"m22: slt t4, t5, t6;"
					"m23: slt t5, t6, t0;"
					"m24: slt t6, t0, t1;"
					"m25: slt t0, t1, t2;"
					"m26: slt t1, t2, a0;"
					"m27: slt t2, a0, a1;"
					"m28: slt a0, a1, a2;"
					"m29: slt a1, a2, a3;"
					"m30: slt a2, a3, a4;"
					"m31: slt a3, a4, a5;"
					"m32: slt a4, a5, a3;"
					"m33: slt a5, a3, a7;"
					"m34: slt a3, a7, s2;"
					"m35: slt a7, s2, s3;"
					"m36: slt s2, s3, s4;"
					"m37: slt s3, s4, s5;"
					"m38: slt s4, s5, s6;"
					"m39: slt s5, s6, s7;"
					"m40: slt s6, s7, s8;"
					"m41: slt s7, s8, s9;"
					"m42: slt s8, s9, s10;"
					"m43: slt s9, s10, s11;"
					"m44: slt s10, s11, t3;"
					"m45: slt s11, t3, t4;"
					"m46: slt t3, t4, t5;"
					"m47: slt t4, t5, t6;"
					"m48: slt t5, t6, t0;"
					"m49: slt t6, t0, t1;"
					"m50: slt t0, t1, t2;"
					"m51: slt t1, t2, a0;"
					"m52: slt t2, a0, a1;"
					"m53: slt a0, a1, a2;"
					"m54: slt a1, a2, a3;"
					"m55: slt a2, a3, a4;"
					"m56: slt a3, a4, a5;"
					"m57: slt a4, a5, a3;"
					"m58: slt a5, a3, a7;"
					"m59: slt a3, a7, s2;"
					"m60: slt a7, s2, s3;"
					"m61: slt s2, s3, s4;"
					"m62: slt s3, s4, s5;"
					"m63: slt s4, s5, s6;"
					"m64: slt s5, s6, s7;"
					"m65: slt s6, s7, s8;"
					"m66: slt s7, s8, s9;"
					"m67: slt s8, s9, s10;"
					"m68: slt s9, s10, s11;"
					"m69: slt s10, s11, t3;"
					"m70: slt s11, t3, t4;"
					"m71: slt t3, t4, t5;"
					"m72: slt t4, t5, t6;"
					"m73: slt t5, t6, t0;"
					"m74: slt t6, t0, t1;"
					"m75: slt t0, t1, t2;"
					"m76: slt t1, t2, a0;"
					"m77: slt t2, a0, a1;"
					"m78: slt a0, a1, a2;"
					"m79: slt a1, a2, a3;"
					"m80: slt a2, a3, a4;"
					"m81: slt a3, a4, a5;"
					"m82: slt a4, a5, a3;"
					"m83: slt a5, a3, a7;"
					"m84: slt a3, a7, s2;"
					"m85: slt a7, s2, s3;"
					"m86: slt s2, s3, s4;"
					"m87: slt s3, s4, s5;"
					"m88: slt s4, s5, s6;"
					"m89: slt s5, s6, s7;"
					"m90: slt s6, s7, s8;"
					"m91: slt s7, s8, s9;"
					"m92: slt s8, s9, s10;"
					"m93: slt s9, s10, s11;"
					"m94: slt s10, s11, t3;"
					"m95: slt s11, t3, t4;"
					"m96: slt t3, t4, t5;"
					"m97: slt t4, t5, t6;"
					"m98: slt t5, t6, t0;"
					"m99: slt t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
