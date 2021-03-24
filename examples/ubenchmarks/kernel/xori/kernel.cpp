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
    int  __attribute__ ((noinline)) kernel_xori(int arg) {
        asm volatile(
					"li t0, 0xa77d3281;"
					"li t1, 0xbc89d8f9;"
					"li t2, 0x8bb4528d;"
					"li a0, 0x1bd7e309;"
					"li a1, 0xfbd26bef;"
					"li a2, 0xae1ec369;"
					"li a3, 0xd594275b;"
					"li a4, 0xdfb74e49;"
					"li a5, 0xdd85065a;"
					"li a3, 0x0b2db193;"
					"li a7, 0x08e7eafa;"
					"li s2, 0xade33c49;"
					"li s3, 0xdf762f9d;"
					"li s4, 0xebdf4c7a;"
					"li s5, 0x4e563b3a;"
					"li s6, 0x6164aaf4;"
					"li s7, 0xea4b44af;"
					"li s8, 0x9fd4212f;"
					"li s9, 0x04ec7c8f;"
					"li s10, 0xc9a168a7;"
					"li s11, 0x01367d7d;"
					"li t3, 0xd649e3b7;"
					"li t4, 0x847f0341;"
					"li t5, 0x5b2a4f63;"
					"li t6, 0xc748a983;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: xori t0, t1, 0xe97;"
					"m1: xori t1, t2, 0xfae;"
					"m2: xori t2, a0, 0xf28;"
					"m3: xori a0, a1, 0x0ac;"
					"m4: xori a1, a2, 0x486;"
					"m5: xori a2, a3, 0xdda;"
					"m6: xori a3, a4, 0xa3a;"
					"m7: xori a4, a5, 0x6d3;"
					"m8: xori a5, a3, 0x51d;"
					"m9: xori a3, a7, 0xd9e;"
					"m10: xori a7, s2, 0xfd9;"
					"m11: xori s2, s3, 0xe84;"
					"m12: xori s3, s4, 0x2c3;"
					"m13: xori s4, s5, 0x728;"
					"m14: xori s5, s6, 0x088;"
					"m15: xori s6, s7, 0x937;"
					"m16: xori s7, s8, 0xbeb;"
					"m17: xori s8, s9, 0xf1f;"
					"m18: xori s9, s10, 0xa92;"
					"m19: xori s10, s11, 0xf99;"
					"m20: xori s11, t3, 0x7ac;"
					"m21: xori t3, t4, 0x417;"
					"m22: xori t4, t5, 0xfbf;"
					"m23: xori t5, t6, 0xbd6;"
					"m24: xori t6, t0, 0x199;"
					"m25: xori t0, t1, 0x8f2;"
					"m26: xori t1, t2, 0x3ef;"
					"m27: xori t2, a0, 0x8d8;"
					"m28: xori a0, a1, 0xa91;"
					"m29: xori a1, a2, 0x9d6;"
					"m30: xori a2, a3, 0x57a;"
					"m31: xori a3, a4, 0xb30;"
					"m32: xori a4, a5, 0x0cb;"
					"m33: xori a5, a3, 0x50d;"
					"m34: xori a3, a7, 0x2d4;"
					"m35: xori a7, s2, 0xae0;"
					"m36: xori s2, s3, 0x151;"
					"m37: xori s3, s4, 0x60b;"
					"m38: xori s4, s5, 0x8cf;"
					"m39: xori s5, s6, 0x693;"
					"m40: xori s6, s7, 0xca7;"
					"m41: xori s7, s8, 0x71d;"
					"m42: xori s8, s9, 0x49d;"
					"m43: xori s9, s10, 0x2e0;"
					"m44: xori s10, s11, 0xaab;"
					"m45: xori s11, t3, 0x89c;"
					"m46: xori t3, t4, 0x03f;"
					"m47: xori t4, t5, 0x492;"
					"m48: xori t5, t6, 0x7c8;"
					"m49: xori t6, t0, 0xc81;"
					"m50: xori t0, t1, 0x7c5;"
					"m51: xori t1, t2, 0x0d8;"
					"m52: xori t2, a0, 0x30e;"
					"m53: xori a0, a1, 0x561;"
					"m54: xori a1, a2, 0xd92;"
					"m55: xori a2, a3, 0x09a;"
					"m56: xori a3, a4, 0x942;"
					"m57: xori a4, a5, 0x454;"
					"m58: xori a5, a3, 0x98f;"
					"m59: xori a3, a7, 0x383;"
					"m60: xori a7, s2, 0xe37;"
					"m61: xori s2, s3, 0x94e;"
					"m62: xori s3, s4, 0x655;"
					"m63: xori s4, s5, 0x2e3;"
					"m64: xori s5, s6, 0xc32;"
					"m65: xori s6, s7, 0x7ab;"
					"m66: xori s7, s8, 0xbf3;"
					"m67: xori s8, s9, 0xf7b;"
					"m68: xori s9, s10, 0xdb3;"
					"m69: xori s10, s11, 0xdf4;"
					"m70: xori s11, t3, 0x11f;"
					"m71: xori t3, t4, 0xaf3;"
					"m72: xori t4, t5, 0x902;"
					"m73: xori t5, t6, 0xa9e;"
					"m74: xori t6, t0, 0x98d;"
					"m75: xori t0, t1, 0xf25;"
					"m76: xori t1, t2, 0x9a7;"
					"m77: xori t2, a0, 0xeed;"
					"m78: xori a0, a1, 0x98d;"
					"m79: xori a1, a2, 0xdb9;"
					"m80: xori a2, a3, 0xe20;"
					"m81: xori a3, a4, 0xf81;"
					"m82: xori a4, a5, 0xf5f;"
					"m83: xori a5, a3, 0xdef;"
					"m84: xori a3, a7, 0x8c5;"
					"m85: xori a7, s2, 0xf7c;"
					"m86: xori s2, s3, 0x1f2;"
					"m87: xori s3, s4, 0x909;"
					"m88: xori s4, s5, 0x033;"
					"m89: xori s5, s6, 0x3fe;"
					"m90: xori s6, s7, 0xc59;"
					"m91: xori s7, s8, 0x72a;"
					"m92: xori s8, s9, 0x11d;"
					"m93: xori s9, s10, 0xd14;"
					"m94: xori s10, s11, 0x0f8;"
					"m95: xori s11, t3, 0x217;"
					"m96: xori t3, t4, 0x9b1;"
					"m97: xori t4, t5, 0xfc9;"
					"m98: xori t5, t6, 0x56c;"
					"m99: xori t6, t0, 0xa40;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
