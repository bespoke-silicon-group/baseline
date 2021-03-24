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
    int  __attribute__ ((noinline)) kernel_li(int arg) {
        asm volatile(
					"li t0, 0xa080b16f;"
					"li t1, 0x6ae67d2a;"
					"li t2, 0xed174bf9;"
					"li a0, 0x6ea5e30f;"
					"li a1, 0x8a6802ac;"
					"li a2, 0x1ad14e3d;"
					"li a3, 0xf23d0cb0;"
					"li a4, 0xd42ed6bb;"
					"li a5, 0x28198023;"
					"li a3, 0xdd2273e4;"
					"li a7, 0x190f2952;"
					"li s2, 0x41c43e94;"
					"li s3, 0x2b6027e4;"
					"li s4, 0x91744ce2;"
					"li s5, 0x2f617b2a;"
					"li s6, 0xc61ef9ba;"
					"li s7, 0x5ff276a2;"
					"li s8, 0xef3e7135;"
					"li s9, 0xc3d928b1;"
					"li s10, 0x15b1b34e;"
					"li s11, 0x8eae53ef;"
					"li t3, 0x88d2d099;"
					"li t4, 0x99165563;"
					"li t5, 0x240658a3;"
					"li t6, 0xeae30460;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: li t0, 0xd31a2;"
					"m1: li t1, 0x410eb;"
					"m2: li t2, 0xf61be;"
					"m3: li a0, 0x3f9df;"
					"m4: li a1, 0xa6600;"
					"m5: li a2, 0x299e9;"
					"m6: li a3, 0x7eaa1;"
					"m7: li a4, 0x4de4c;"
					"m8: li a5, 0x1233c;"
					"m9: li a3, 0x74617;"
					"m10: li a7, 0x56272;"
					"m11: li s2, 0x0a00c;"
					"m12: li s3, 0x0b5dd;"
					"m13: li s4, 0x42074;"
					"m14: li s5, 0x95b10;"
					"m15: li s6, 0xbd15a;"
					"m16: li s7, 0xb1fe4;"
					"m17: li s8, 0x9e2b2;"
					"m18: li s9, 0x3ac5f;"
					"m19: li s10, 0x54c13;"
					"m20: li s11, 0xd6351;"
					"m21: li t3, 0x1d629;"
					"m22: li t4, 0x7ab1c;"
					"m23: li t5, 0x94c3a;"
					"m24: li t6, 0x068fb;"
					"m25: li t0, 0x45083;"
					"m26: li t1, 0x11bb2;"
					"m27: li t2, 0x14cac;"
					"m28: li a0, 0xd3728;"
					"m29: li a1, 0x601ef;"
					"m30: li a2, 0x9bbbb;"
					"m31: li a3, 0x2ec04;"
					"m32: li a4, 0xa5495;"
					"m33: li a5, 0x077f8;"
					"m34: li a3, 0x771af;"
					"m35: li a7, 0xe38d0;"
					"m36: li s2, 0x72290;"
					"m37: li s3, 0x775a2;"
					"m38: li s4, 0x24494;"
					"m39: li s5, 0x9bfcb;"
					"m40: li s6, 0xa476b;"
					"m41: li s7, 0xf60c3;"
					"m42: li s8, 0xa6006;"
					"m43: li s9, 0x5d40b;"
					"m44: li s10, 0x8a7d8;"
					"m45: li s11, 0xb4fa5;"
					"m46: li t3, 0xac6b4;"
					"m47: li t4, 0x6d335;"
					"m48: li t5, 0xa1a84;"
					"m49: li t6, 0x2f6b4;"
					"m50: li t0, 0x3401d;"
					"m51: li t1, 0xf8b49;"
					"m52: li t2, 0xa3d56;"
					"m53: li a0, 0xba220;"
					"m54: li a1, 0xb8a62;"
					"m55: li a2, 0x44a5f;"
					"m56: li a3, 0x1dd48;"
					"m57: li a4, 0x319bb;"
					"m58: li a5, 0x9e406;"
					"m59: li a3, 0xb32d5;"
					"m60: li a7, 0x84ab1;"
					"m61: li s2, 0x3e1ef;"
					"m62: li s3, 0xe3ce4;"
					"m63: li s4, 0x39d21;"
					"m64: li s5, 0xdac60;"
					"m65: li s6, 0x43425;"
					"m66: li s7, 0x59b4d;"
					"m67: li s8, 0x9b058;"
					"m68: li s9, 0xdefa9;"
					"m69: li s10, 0x7543f;"
					"m70: li s11, 0xaa1b7;"
					"m71: li t3, 0x5523e;"
					"m72: li t4, 0x05c7e;"
					"m73: li t5, 0x15c7e;"
					"m74: li t6, 0xe8363;"
					"m75: li t0, 0xce01f;"
					"m76: li t1, 0x3809e;"
					"m77: li t2, 0x423d5;"
					"m78: li a0, 0x682ed;"
					"m79: li a1, 0x7e968;"
					"m80: li a2, 0x28e60;"
					"m81: li a3, 0x0fdce;"
					"m82: li a4, 0x5b18e;"
					"m83: li a5, 0xd2d1d;"
					"m84: li a3, 0x6d28a;"
					"m85: li a7, 0x530d3;"
					"m86: li s2, 0x6b699;"
					"m87: li s3, 0xacac8;"
					"m88: li s4, 0x3a4f2;"
					"m89: li s5, 0x13039;"
					"m90: li s6, 0xa85b5;"
					"m91: li s7, 0x470c7;"
					"m92: li s8, 0x4d865;"
					"m93: li s9, 0x44958;"
					"m94: li s10, 0xff362;"
					"m95: li s11, 0xc1aad;"
					"m96: li t3, 0x6d195;"
					"m97: li t4, 0x1eb3f;"
					"m98: li t5, 0x9e79b;"
					"m99: li t6, 0x0b5ab;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
