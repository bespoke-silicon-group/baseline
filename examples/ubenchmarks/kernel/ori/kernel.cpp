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
    int  __attribute__ ((noinline)) kernel_ori(int arg) {
        asm volatile(
					"li t0, 0x19bd0db4;"
					"li t1, 0xeb7f8f88;"
					"li t2, 0xbd47d5a8;"
					"li a0, 0xd257d5c1;"
					"li a1, 0xe6ffd7e2;"
					"li a2, 0x6ebf404e;"
					"li a3, 0xf1d28b2d;"
					"li a4, 0x8e61ca23;"
					"li a5, 0xca2142dd;"
					"li a3, 0xc8fa6f21;"
					"li a7, 0xb6c6cf88;"
					"li s2, 0x574f6ef2;"
					"li s3, 0x638fbffa;"
					"li s4, 0x7f83155f;"
					"li s5, 0x518d4d12;"
					"li s6, 0xb2dc9e44;"
					"li s7, 0xb6d9a73e;"
					"li s8, 0xf42c36b4;"
					"li s9, 0x55b50f8b;"
					"li s10, 0xf387f176;"
					"li s11, 0x050d2e74;"
					"li t3, 0xc893f20e;"
					"li t4, 0xba6736f5;"
					"li t5, 0x6b12ff54;"
					"li t6, 0xfb36ca27;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: ori t0, t1, 0xce9;"
					"m1: ori t1, t2, 0x959;"
					"m2: ori t2, a0, 0x785;"
					"m3: ori a0, a1, 0x5b8;"
					"m4: ori a1, a2, 0x480;"
					"m5: ori a2, a3, 0xe4f;"
					"m6: ori a3, a4, 0xa77;"
					"m7: ori a4, a5, 0x1e6;"
					"m8: ori a5, a3, 0xba1;"
					"m9: ori a3, a7, 0x9a7;"
					"m10: ori a7, s2, 0xe97;"
					"m11: ori s2, s3, 0x61d;"
					"m12: ori s3, s4, 0xa05;"
					"m13: ori s4, s5, 0xde8;"
					"m14: ori s5, s6, 0xc2c;"
					"m15: ori s6, s7, 0x828;"
					"m16: ori s7, s8, 0xe25;"
					"m17: ori s8, s9, 0x33d;"
					"m18: ori s9, s10, 0xb7f;"
					"m19: ori s10, s11, 0x24a;"
					"m20: ori s11, t3, 0xb90;"
					"m21: ori t3, t4, 0xe66;"
					"m22: ori t4, t5, 0x326;"
					"m23: ori t5, t6, 0x8ac;"
					"m24: ori t6, t0, 0x645;"
					"m25: ori t0, t1, 0xed1;"
					"m26: ori t1, t2, 0x250;"
					"m27: ori t2, a0, 0x899;"
					"m28: ori a0, a1, 0xa68;"
					"m29: ori a1, a2, 0x9cd;"
					"m30: ori a2, a3, 0xde0;"
					"m31: ori a3, a4, 0xaab;"
					"m32: ori a4, a5, 0x8b2;"
					"m33: ori a5, a3, 0x31f;"
					"m34: ori a3, a7, 0xbb8;"
					"m35: ori a7, s2, 0x973;"
					"m36: ori s2, s3, 0xb68;"
					"m37: ori s3, s4, 0xdc7;"
					"m38: ori s4, s5, 0x577;"
					"m39: ori s5, s6, 0x165;"
					"m40: ori s6, s7, 0x40e;"
					"m41: ori s7, s8, 0x767;"
					"m42: ori s8, s9, 0xccd;"
					"m43: ori s9, s10, 0x7a9;"
					"m44: ori s10, s11, 0xb86;"
					"m45: ori s11, t3, 0x384;"
					"m46: ori t3, t4, 0xc18;"
					"m47: ori t4, t5, 0xb68;"
					"m48: ori t5, t6, 0x0ab;"
					"m49: ori t6, t0, 0xfef;"
					"m50: ori t0, t1, 0x2ba;"
					"m51: ori t1, t2, 0x604;"
					"m52: ori t2, a0, 0xa9a;"
					"m53: ori a0, a1, 0xaaa;"
					"m54: ori a1, a2, 0x128;"
					"m55: ori a2, a3, 0xc9b;"
					"m56: ori a3, a4, 0xdac;"
					"m57: ori a4, a5, 0x9bb;"
					"m58: ori a5, a3, 0xf73;"
					"m59: ori a3, a7, 0x3c4;"
					"m60: ori a7, s2, 0x0b9;"
					"m61: ori s2, s3, 0xcb0;"
					"m62: ori s3, s4, 0x995;"
					"m63: ori s4, s5, 0x860;"
					"m64: ori s5, s6, 0x473;"
					"m65: ori s6, s7, 0x914;"
					"m66: ori s7, s8, 0xaee;"
					"m67: ori s8, s9, 0xa32;"
					"m68: ori s9, s10, 0xfb8;"
					"m69: ori s10, s11, 0x7c3;"
					"m70: ori s11, t3, 0x80a;"
					"m71: ori t3, t4, 0xf43;"
					"m72: ori t4, t5, 0xce6;"
					"m73: ori t5, t6, 0x870;"
					"m74: ori t6, t0, 0xdc9;"
					"m75: ori t0, t1, 0xecc;"
					"m76: ori t1, t2, 0xa94;"
					"m77: ori t2, a0, 0x7c1;"
					"m78: ori a0, a1, 0x21d;"
					"m79: ori a1, a2, 0x84f;"
					"m80: ori a2, a3, 0xb03;"
					"m81: ori a3, a4, 0x1f9;"
					"m82: ori a4, a5, 0x4bb;"
					"m83: ori a5, a3, 0x4d2;"
					"m84: ori a3, a7, 0x941;"
					"m85: ori a7, s2, 0x350;"
					"m86: ori s2, s3, 0x392;"
					"m87: ori s3, s4, 0x9b7;"
					"m88: ori s4, s5, 0xccd;"
					"m89: ori s5, s6, 0x47d;"
					"m90: ori s6, s7, 0xdd6;"
					"m91: ori s7, s8, 0x1fb;"
					"m92: ori s8, s9, 0xe92;"
					"m93: ori s9, s10, 0x1ac;"
					"m94: ori s10, s11, 0x017;"
					"m95: ori s11, t3, 0x2f6;"
					"m96: ori t3, t4, 0x258;"
					"m97: ori t4, t5, 0x886;"
					"m98: ori t5, t6, 0x6d8;"
					"m99: ori t6, t0, 0xa12;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
