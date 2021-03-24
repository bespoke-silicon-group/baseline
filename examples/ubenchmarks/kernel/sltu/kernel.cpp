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
    int  __attribute__ ((noinline)) kernel_sltu(int arg) {
        asm volatile(
					"li t0, 0xb1cdb71f;"
					"li t1, 0x633cd095;"
					"li t2, 0x1babd58c;"
					"li a0, 0x883b43a8;"
					"li a1, 0x7ec5bf6c;"
					"li a2, 0xb6472811;"
					"li a3, 0xbae0f37d;"
					"li a4, 0x52b372dc;"
					"li a5, 0x77236e34;"
					"li a3, 0xcea3e66d;"
					"li a7, 0x37a4b378;"
					"li s2, 0xcfd2bcbc;"
					"li s3, 0x0d458a36;"
					"li s4, 0x8a62c3e7;"
					"li s5, 0x2c1bbb51;"
					"li s6, 0xeb608d89;"
					"li s7, 0x0b876874;"
					"li s8, 0x15d73dc1;"
					"li s9, 0xb37c625e;"
					"li s10, 0x2314c964;"
					"li s11, 0xb1e9ab0c;"
					"li t3, 0xcd66117d;"
					"li t4, 0x0d1cdda3;"
					"li t5, 0x9ac62fa6;"
					"li t6, 0xb0df9fb7;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: sltu t0, t1, t2;"
					"m1: sltu t1, t2, a0;"
					"m2: sltu t2, a0, a1;"
					"m3: sltu a0, a1, a2;"
					"m4: sltu a1, a2, a3;"
					"m5: sltu a2, a3, a4;"
					"m6: sltu a3, a4, a5;"
					"m7: sltu a4, a5, a3;"
					"m8: sltu a5, a3, a7;"
					"m9: sltu a3, a7, s2;"
					"m10: sltu a7, s2, s3;"
					"m11: sltu s2, s3, s4;"
					"m12: sltu s3, s4, s5;"
					"m13: sltu s4, s5, s6;"
					"m14: sltu s5, s6, s7;"
					"m15: sltu s6, s7, s8;"
					"m16: sltu s7, s8, s9;"
					"m17: sltu s8, s9, s10;"
					"m18: sltu s9, s10, s11;"
					"m19: sltu s10, s11, t3;"
					"m20: sltu s11, t3, t4;"
					"m21: sltu t3, t4, t5;"
					"m22: sltu t4, t5, t6;"
					"m23: sltu t5, t6, t0;"
					"m24: sltu t6, t0, t1;"
					"m25: sltu t0, t1, t2;"
					"m26: sltu t1, t2, a0;"
					"m27: sltu t2, a0, a1;"
					"m28: sltu a0, a1, a2;"
					"m29: sltu a1, a2, a3;"
					"m30: sltu a2, a3, a4;"
					"m31: sltu a3, a4, a5;"
					"m32: sltu a4, a5, a3;"
					"m33: sltu a5, a3, a7;"
					"m34: sltu a3, a7, s2;"
					"m35: sltu a7, s2, s3;"
					"m36: sltu s2, s3, s4;"
					"m37: sltu s3, s4, s5;"
					"m38: sltu s4, s5, s6;"
					"m39: sltu s5, s6, s7;"
					"m40: sltu s6, s7, s8;"
					"m41: sltu s7, s8, s9;"
					"m42: sltu s8, s9, s10;"
					"m43: sltu s9, s10, s11;"
					"m44: sltu s10, s11, t3;"
					"m45: sltu s11, t3, t4;"
					"m46: sltu t3, t4, t5;"
					"m47: sltu t4, t5, t6;"
					"m48: sltu t5, t6, t0;"
					"m49: sltu t6, t0, t1;"
					"m50: sltu t0, t1, t2;"
					"m51: sltu t1, t2, a0;"
					"m52: sltu t2, a0, a1;"
					"m53: sltu a0, a1, a2;"
					"m54: sltu a1, a2, a3;"
					"m55: sltu a2, a3, a4;"
					"m56: sltu a3, a4, a5;"
					"m57: sltu a4, a5, a3;"
					"m58: sltu a5, a3, a7;"
					"m59: sltu a3, a7, s2;"
					"m60: sltu a7, s2, s3;"
					"m61: sltu s2, s3, s4;"
					"m62: sltu s3, s4, s5;"
					"m63: sltu s4, s5, s6;"
					"m64: sltu s5, s6, s7;"
					"m65: sltu s6, s7, s8;"
					"m66: sltu s7, s8, s9;"
					"m67: sltu s8, s9, s10;"
					"m68: sltu s9, s10, s11;"
					"m69: sltu s10, s11, t3;"
					"m70: sltu s11, t3, t4;"
					"m71: sltu t3, t4, t5;"
					"m72: sltu t4, t5, t6;"
					"m73: sltu t5, t6, t0;"
					"m74: sltu t6, t0, t1;"
					"m75: sltu t0, t1, t2;"
					"m76: sltu t1, t2, a0;"
					"m77: sltu t2, a0, a1;"
					"m78: sltu a0, a1, a2;"
					"m79: sltu a1, a2, a3;"
					"m80: sltu a2, a3, a4;"
					"m81: sltu a3, a4, a5;"
					"m82: sltu a4, a5, a3;"
					"m83: sltu a5, a3, a7;"
					"m84: sltu a3, a7, s2;"
					"m85: sltu a7, s2, s3;"
					"m86: sltu s2, s3, s4;"
					"m87: sltu s3, s4, s5;"
					"m88: sltu s4, s5, s6;"
					"m89: sltu s5, s6, s7;"
					"m90: sltu s6, s7, s8;"
					"m91: sltu s7, s8, s9;"
					"m92: sltu s8, s9, s10;"
					"m93: sltu s9, s10, s11;"
					"m94: sltu s10, s11, t3;"
					"m95: sltu s11, t3, t4;"
					"m96: sltu t3, t4, t5;"
					"m97: sltu t4, t5, t6;"
					"m98: sltu t5, t6, t0;"
					"m99: sltu t6, t0, t1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
