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
    int  __attribute__ ((noinline)) kernel_jal(int arg) {
        asm volatile(
					"li t0, 0x817c45dc;"
					"li t1, 0xfc349973;"
					"li t2, 0xee582277;"
					"li a0, 0xb78511bc;"
					"li a1, 0xc2286d61;"
					"li a2, 0x14cb3e74;"
					"li a3, 0x21a7a634;"
					"li a4, 0x792c3927;"
					"li a5, 0x9bff98d4;"
					"li a3, 0x3fb3aaa4;"
					"li a7, 0xf49c6cf6;"
					"li s2, 0x3802f2bb;"
					"li s3, 0x3ef5eeaf;"
					"li s4, 0xdfe93b03;"
					"li s5, 0xc9a594d9;"
					"li s6, 0xc0fc8f4c;"
					"li s7, 0xb583645b;"
					"li s8, 0x37408c28;"
					"li s9, 0xddaa2179;"
					"li s10, 0xa860819f;"
					"li s11, 0x7bb50c3e;"
					"li t3, 0x475ff539;"
					"li t4, 0x683478d2;"
					"li t5, 0x40e4f26f;"
					"li t6, 0x348cd893;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: jal m99;"
					"m1: jal m98;"
					"m2: jal m97;"
					"m3: jal m96;"
					"m4: jal m95;"
					"m5: jal m94;"
					"m6: jal m93;"
					"m7: jal m92;"
					"m8: jal m91;"
					"m9: jal m90;"
					"m10: jal m89;"
					"m11: jal m88;"
					"m12: jal m87;"
					"m13: jal m86;"
					"m14: jal m85;"
					"m15: jal m84;"
					"m16: jal m83;"
					"m17: jal m82;"
					"m18: jal m81;"
					"m19: jal m80;"
					"m20: jal m79;"
					"m21: jal m78;"
					"m22: jal m77;"
					"m23: jal m76;"
					"m24: jal m75;"
					"m25: jal m74;"
					"m26: jal m73;"
					"m27: jal m72;"
					"m28: jal m71;"
					"m29: jal m70;"
					"m30: jal m69;"
					"m31: jal m68;"
					"m32: jal m67;"
					"m33: jal m66;"
					"m34: jal m65;"
					"m35: jal m64;"
					"m36: jal m63;"
					"m37: jal m62;"
					"m38: jal m61;"
					"m39: jal m60;"
					"m40: jal m59;"
					"m41: jal m58;"
					"m42: jal m57;"
					"m43: jal m56;"
					"m44: jal m55;"
					"m45: jal m54;"
					"m46: jal m53;"
					"m47: jal m52;"
					"m48: jal m51;"
					"m49: jal m50;"
					"m50: jal ms;"
					"m51: jal m49;"
					"m52: jal m48;"
					"m53: jal m47;"
					"m54: jal m46;"
					"m55: jal m45;"
					"m56: jal m44;"
					"m57: jal m43;"
					"m58: jal m42;"
					"m59: jal m41;"
					"m60: jal m40;"
					"m61: jal m39;"
					"m62: jal m38;"
					"m63: jal m37;"
					"m64: jal m36;"
					"m65: jal m35;"
					"m66: jal m34;"
					"m67: jal m33;"
					"m68: jal m32;"
					"m69: jal m31;"
					"m70: jal m30;"
					"m71: jal m29;"
					"m72: jal m28;"
					"m73: jal m27;"
					"m74: jal m26;"
					"m75: jal m25;"
					"m76: jal m24;"
					"m77: jal m23;"
					"m78: jal m22;"
					"m79: jal m21;"
					"m80: jal m20;"
					"m81: jal m19;"
					"m82: jal m18;"
					"m83: jal m17;"
					"m84: jal m16;"
					"m85: jal m15;"
					"m86: jal m14;"
					"m87: jal m13;"
					"m88: jal m12;"
					"m89: jal m11;"
					"m90: jal m10;"
					"m91: jal m9;"
					"m92: jal m8;"
					"m93: jal m7;"
					"m94: jal m6;"
					"m95: jal m5;"
					"m96: jal m4;"
					"m97: jal m3;"
					"m98: jal m2;"
					"m99: jal m1;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
