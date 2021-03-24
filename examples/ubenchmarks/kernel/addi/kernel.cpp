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
    int  __attribute__ ((noinline)) kernel_addi(int arg) {
        asm volatile(
					"li t0, 0x04d3d4cb;"
					"li t1, 0x11eb013a;"
					"li t2, 0x8c0c6c22;"
					"li a0, 0x11fa4e12;"
					"li a1, 0xcbd1e340;"
					"li a2, 0xe4e49ee1;"
					"li a3, 0x15421259;"
					"li a4, 0x8d0bae02;"
					"li a5, 0x1e41f54e;"
					"li a3, 0xfad2a53b;"
					"li a7, 0x5ebef8b7;"
					"li s2, 0x89011b92;"
					"li s3, 0x9de0640e;"
					"li s4, 0x79c7662f;"
					"li s5, 0xba14eae9;"
					"li s6, 0x5d3db1dc;"
					"li s7, 0x5de8d563;"
					"li s8, 0x09af1a86;"
					"li s9, 0x40331094;"
					"li s10, 0x89f69472;"
					"li s11, 0x3c48e04d;"
					"li t3, 0x368e035d;"
					"li t4, 0x7e241448;"
					"li t5, 0xa738f1b3;"
					"li t6, 0xca4d4b31;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: addi t0, t1, 0x482;"
					"m1: addi t1, t2, 0x128;"
					"m2: addi t2, a0, 0xf4d;"
					"m3: addi a0, a1, 0xb42;"
					"m4: addi a1, a2, 0xaad;"
					"m5: addi a2, a3, 0x0ca;"
					"m6: addi a3, a4, 0x99a;"
					"m7: addi a4, a5, 0x60e;"
					"m8: addi a5, a3, 0xcee;"
					"m9: addi a3, a7, 0xe03;"
					"m10: addi a7, s2, 0xf6a;"
					"m11: addi s2, s3, 0x3e7;"
					"m12: addi s3, s4, 0x665;"
					"m13: addi s4, s5, 0x093;"
					"m14: addi s5, s6, 0xc01;"
					"m15: addi s6, s7, 0x079;"
					"m16: addi s7, s8, 0x7b2;"
					"m17: addi s8, s9, 0x425;"
					"m18: addi s9, s10, 0xfaa;"
					"m19: addi s10, s11, 0xb8a;"
					"m20: addi s11, t3, 0x427;"
					"m21: addi t3, t4, 0x927;"
					"m22: addi t4, t5, 0x372;"
					"m23: addi t5, t6, 0x0b2;"
					"m24: addi t6, t0, 0x6c8;"
					"m25: addi t0, t1, 0x999;"
					"m26: addi t1, t2, 0x9db;"
					"m27: addi t2, a0, 0x100;"
					"m28: addi a0, a1, 0x04a;"
					"m29: addi a1, a2, 0xe69;"
					"m30: addi a2, a3, 0x710;"
					"m31: addi a3, a4, 0xa2c;"
					"m32: addi a4, a5, 0x56b;"
					"m33: addi a5, a3, 0xece;"
					"m34: addi a3, a7, 0x8c4;"
					"m35: addi a7, s2, 0xd50;"
					"m36: addi s2, s3, 0x8f5;"
					"m37: addi s3, s4, 0xe8d;"
					"m38: addi s4, s5, 0xc88;"
					"m39: addi s5, s6, 0xb75;"
					"m40: addi s6, s7, 0x8aa;"
					"m41: addi s7, s8, 0x452;"
					"m42: addi s8, s9, 0x53a;"
					"m43: addi s9, s10, 0x09f;"
					"m44: addi s10, s11, 0xb70;"
					"m45: addi s11, t3, 0xf7e;"
					"m46: addi t3, t4, 0x3f7;"
					"m47: addi t4, t5, 0x3ba;"
					"m48: addi t5, t6, 0xbf3;"
					"m49: addi t6, t0, 0xf25;"
					"m50: addi t0, t1, 0x9bc;"
					"m51: addi t1, t2, 0x4fd;"
					"m52: addi t2, a0, 0x200;"
					"m53: addi a0, a1, 0xce8;"
					"m54: addi a1, a2, 0x2e8;"
					"m55: addi a2, a3, 0x6e5;"
					"m56: addi a3, a4, 0x7db;"
					"m57: addi a4, a5, 0x44e;"
					"m58: addi a5, a3, 0xf8d;"
					"m59: addi a3, a7, 0x74c;"
					"m60: addi a7, s2, 0x02f;"
					"m61: addi s2, s3, 0x184;"
					"m62: addi s3, s4, 0x6bc;"
					"m63: addi s4, s5, 0x40b;"
					"m64: addi s5, s6, 0x6df;"
					"m65: addi s6, s7, 0x0ef;"
					"m66: addi s7, s8, 0x1bb;"
					"m67: addi s8, s9, 0x228;"
					"m68: addi s9, s10, 0xb34;"
					"m69: addi s10, s11, 0xbbb;"
					"m70: addi s11, t3, 0x555;"
					"m71: addi t3, t4, 0x1a7;"
					"m72: addi t4, t5, 0x2eb;"
					"m73: addi t5, t6, 0x78c;"
					"m74: addi t6, t0, 0x072;"
					"m75: addi t0, t1, 0x1db;"
					"m76: addi t1, t2, 0x398;"
					"m77: addi t2, a0, 0x339;"
					"m78: addi a0, a1, 0xe72;"
					"m79: addi a1, a2, 0xd7f;"
					"m80: addi a2, a3, 0xcd3;"
					"m81: addi a3, a4, 0xcb1;"
					"m82: addi a4, a5, 0xc51;"
					"m83: addi a5, a3, 0xf86;"
					"m84: addi a3, a7, 0xf4d;"
					"m85: addi a7, s2, 0xf94;"
					"m86: addi s2, s3, 0xd03;"
					"m87: addi s3, s4, 0x8b9;"
					"m88: addi s4, s5, 0x94e;"
					"m89: addi s5, s6, 0xb82;"
					"m90: addi s6, s7, 0x2f2;"
					"m91: addi s7, s8, 0xa41;"
					"m92: addi s8, s9, 0xe5b;"
					"m93: addi s9, s10, 0xba7;"
					"m94: addi s10, s11, 0x2ee;"
					"m95: addi s11, t3, 0x0dd;"
					"m96: addi t3, t4, 0x356;"
					"m97: addi t4, t5, 0xc59;"
					"m98: addi t5, t6, 0x65d;"
					"m99: addi t6, t0, 0xd0f;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
