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
    int  __attribute__ ((noinline)) kernel_andi(int arg) {
        asm volatile(
					"li t0, 0x4ea17907;"
					"li t1, 0x117021aa;"
					"li t2, 0x766c0fe9;"
					"li a0, 0x1c44be7c;"
					"li a1, 0x7d84f958;"
					"li a2, 0x8fa60157;"
					"li a3, 0x5c8fa302;"
					"li a4, 0xce839227;"
					"li a5, 0xbad6f846;"
					"li a3, 0xfa189ff9;"
					"li a7, 0x330e32be;"
					"li s2, 0x4311f40f;"
					"li s3, 0x1ff71e13;"
					"li s4, 0xd1ebf283;"
					"li s5, 0xce33cd18;"
					"li s6, 0x9da6966c;"
					"li s7, 0xfd6c4380;"
					"li s8, 0x6fbc0207;"
					"li s9, 0x7ed86359;"
					"li s10, 0x551273eb;"
					"li s11, 0x48dd908b;"
					"li t3, 0xc70d16a5;"
					"li t4, 0x3d900a85;"
					"li t5, 0x271978c2;"
					"li t6, 0x344a7873;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: andi t0, t1, 0xfef;"
					"m1: andi t1, t2, 0x60f;"
					"m2: andi t2, a0, 0x964;"
					"m3: andi a0, a1, 0x24d;"
					"m4: andi a1, a2, 0x667;"
					"m5: andi a2, a3, 0x4bd;"
					"m6: andi a3, a4, 0x63a;"
					"m7: andi a4, a5, 0x77f;"
					"m8: andi a5, a3, 0xb43;"
					"m9: andi a3, a7, 0xd2f;"
					"m10: andi a7, s2, 0x442;"
					"m11: andi s2, s3, 0x37f;"
					"m12: andi s3, s4, 0xe43;"
					"m13: andi s4, s5, 0xe0a;"
					"m14: andi s5, s6, 0xaf3;"
					"m15: andi s6, s7, 0xa74;"
					"m16: andi s7, s8, 0xd16;"
					"m17: andi s8, s9, 0x578;"
					"m18: andi s9, s10, 0xd9a;"
					"m19: andi s10, s11, 0xd12;"
					"m20: andi s11, t3, 0x98f;"
					"m21: andi t3, t4, 0x4bf;"
					"m22: andi t4, t5, 0xe3c;"
					"m23: andi t5, t6, 0xdc2;"
					"m24: andi t6, t0, 0xaed;"
					"m25: andi t0, t1, 0x8ce;"
					"m26: andi t1, t2, 0x58c;"
					"m27: andi t2, a0, 0x158;"
					"m28: andi a0, a1, 0x5b6;"
					"m29: andi a1, a2, 0x427;"
					"m30: andi a2, a3, 0xfcf;"
					"m31: andi a3, a4, 0xa9f;"
					"m32: andi a4, a5, 0xc09;"
					"m33: andi a5, a3, 0x4e1;"
					"m34: andi a3, a7, 0xe8a;"
					"m35: andi a7, s2, 0x873;"
					"m36: andi s2, s3, 0x773;"
					"m37: andi s3, s4, 0xcbd;"
					"m38: andi s4, s5, 0xc5d;"
					"m39: andi s5, s6, 0x90e;"
					"m40: andi s6, s7, 0x50c;"
					"m41: andi s7, s8, 0x4d4;"
					"m42: andi s8, s9, 0x627;"
					"m43: andi s9, s10, 0xc6c;"
					"m44: andi s10, s11, 0xe49;"
					"m45: andi s11, t3, 0x25a;"
					"m46: andi t3, t4, 0x331;"
					"m47: andi t4, t5, 0x6ea;"
					"m48: andi t5, t6, 0xabe;"
					"m49: andi t6, t0, 0xe21;"
					"m50: andi t0, t1, 0xd93;"
					"m51: andi t1, t2, 0xab5;"
					"m52: andi t2, a0, 0x59c;"
					"m53: andi a0, a1, 0xb85;"
					"m54: andi a1, a2, 0x6b4;"
					"m55: andi a2, a3, 0x58e;"
					"m56: andi a3, a4, 0x65a;"
					"m57: andi a4, a5, 0xbd4;"
					"m58: andi a5, a3, 0xb3c;"
					"m59: andi a3, a7, 0x894;"
					"m60: andi a7, s2, 0xdd2;"
					"m61: andi s2, s3, 0xf73;"
					"m62: andi s3, s4, 0x601;"
					"m63: andi s4, s5, 0x0e4;"
					"m64: andi s5, s6, 0x9a6;"
					"m65: andi s6, s7, 0x5f9;"
					"m66: andi s7, s8, 0x3b2;"
					"m67: andi s8, s9, 0xfd2;"
					"m68: andi s9, s10, 0xe9f;"
					"m69: andi s10, s11, 0x598;"
					"m70: andi s11, t3, 0xc46;"
					"m71: andi t3, t4, 0x0bd;"
					"m72: andi t4, t5, 0x4f0;"
					"m73: andi t5, t6, 0xcca;"
					"m74: andi t6, t0, 0x6c4;"
					"m75: andi t0, t1, 0x8e2;"
					"m76: andi t1, t2, 0xf74;"
					"m77: andi t2, a0, 0xb4c;"
					"m78: andi a0, a1, 0x212;"
					"m79: andi a1, a2, 0xf71;"
					"m80: andi a2, a3, 0x46b;"
					"m81: andi a3, a4, 0xb5a;"
					"m82: andi a4, a5, 0xffb;"
					"m83: andi a5, a3, 0x3e1;"
					"m84: andi a3, a7, 0x2c0;"
					"m85: andi a7, s2, 0x4cc;"
					"m86: andi s2, s3, 0xcb3;"
					"m87: andi s3, s4, 0xe8c;"
					"m88: andi s4, s5, 0xa6c;"
					"m89: andi s5, s6, 0xa0d;"
					"m90: andi s6, s7, 0x896;"
					"m91: andi s7, s8, 0x80a;"
					"m92: andi s8, s9, 0xf54;"
					"m93: andi s9, s10, 0x53d;"
					"m94: andi s10, s11, 0x902;"
					"m95: andi s11, t3, 0x839;"
					"m96: andi t3, t4, 0x91a;"
					"m97: andi t4, t5, 0x13d;"
					"m98: andi t5, t6, 0x235;"
					"m99: andi t6, t0, 0xb52;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
