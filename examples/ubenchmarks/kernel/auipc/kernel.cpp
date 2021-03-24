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
    int  __attribute__ ((noinline)) kernel_auipc(int arg) {
        asm volatile(
					"li t0, 0x64bcfd2c;"
					"li t1, 0x91b20cdc;"
					"li t2, 0xc2cb12a8;"
					"li a0, 0xd53437fb;"
					"li a1, 0x31d6fba5;"
					"li a2, 0xfd3b91a7;"
					"li a3, 0x738dc4a1;"
					"li a4, 0xade8498c;"
					"li a5, 0x447e1f4d;"
					"li a3, 0xbd59a452;"
					"li a7, 0xad741ca8;"
					"li s2, 0x3b229099;"
					"li s3, 0x9fe603ac;"
					"li s4, 0x7921497d;"
					"li s5, 0x19e89aaa;"
					"li s6, 0x091a8e10;"
					"li s7, 0x275a2837;"
					"li s8, 0x87fd1bc9;"
					"li s9, 0x64b7bd68;"
					"li s10, 0x306fdd5a;"
					"li s11, 0x18963c44;"
					"li t3, 0x38085a13;"
					"li t4, 0xd77e0172;"
					"li t5, 0x4f9945c6;"
					"li t6, 0x875a9623;"

                       );
        asm volatile ("addi zero,zero,1;");
        asm volatile (
					"m0: auipc t0, 0xaa40f;"
					"m1: auipc t1, 0xd0183;"
					"m2: auipc t2, 0x09f7e;"
					"m3: auipc a0, 0x65471;"
					"m4: auipc a1, 0x81732;"
					"m5: auipc a2, 0x48389;"
					"m6: auipc a3, 0x33b94;"
					"m7: auipc a4, 0x0c6aa;"
					"m8: auipc a5, 0x3aa67;"
					"m9: auipc a3, 0x300bb;"
					"m10: auipc a7, 0xdab2f;"
					"m11: auipc s2, 0x057b4;"
					"m12: auipc s3, 0x7f5bf;"
					"m13: auipc s4, 0x5718c;"
					"m14: auipc s5, 0x0575e;"
					"m15: auipc s6, 0x23e5c;"
					"m16: auipc s7, 0x1162b;"
					"m17: auipc s8, 0xb1dd0;"
					"m18: auipc s9, 0xb3586;"
					"m19: auipc s10, 0x45e85;"
					"m20: auipc s11, 0x6daea;"
					"m21: auipc t3, 0xaad0c;"
					"m22: auipc t4, 0x6991e;"
					"m23: auipc t5, 0x1140a;"
					"m24: auipc t6, 0x02054;"
					"m25: auipc t0, 0xd105e;"
					"m26: auipc t1, 0x6a2a2;"
					"m27: auipc t2, 0x63038;"
					"m28: auipc a0, 0xb28c4;"
					"m29: auipc a1, 0x66bb2;"
					"m30: auipc a2, 0xbeeb2;"
					"m31: auipc a3, 0xd87d6;"
					"m32: auipc a4, 0xe0880;"
					"m33: auipc a5, 0x1a13a;"
					"m34: auipc a3, 0xab54e;"
					"m35: auipc a7, 0xa3ebe;"
					"m36: auipc s2, 0x8e8e2;"
					"m37: auipc s3, 0x0482a;"
					"m38: auipc s4, 0x6cb73;"
					"m39: auipc s5, 0x8dbd3;"
					"m40: auipc s6, 0x35c03;"
					"m41: auipc s7, 0xdc27c;"
					"m42: auipc s8, 0x370df;"
					"m43: auipc s9, 0x5ade9;"
					"m44: auipc s10, 0x71ab9;"
					"m45: auipc s11, 0x5a618;"
					"m46: auipc t3, 0x7d8fb;"
					"m47: auipc t4, 0xaabfd;"
					"m48: auipc t5, 0xa7272;"
					"m49: auipc t6, 0xe3afc;"
					"m50: auipc t0, 0xc7b65;"
					"m51: auipc t1, 0x83a4f;"
					"m52: auipc t2, 0x228d1;"
					"m53: auipc a0, 0xb2b6a;"
					"m54: auipc a1, 0x93ded;"
					"m55: auipc a2, 0x76b0a;"
					"m56: auipc a3, 0xdc59f;"
					"m57: auipc a4, 0x13b3d;"
					"m58: auipc a5, 0x9907c;"
					"m59: auipc a3, 0x792a7;"
					"m60: auipc a7, 0xaab08;"
					"m61: auipc s2, 0x0d81b;"
					"m62: auipc s3, 0xf0225;"
					"m63: auipc s4, 0x15877;"
					"m64: auipc s5, 0xc5591;"
					"m65: auipc s6, 0x9c581;"
					"m66: auipc s7, 0x3e462;"
					"m67: auipc s8, 0xf319f;"
					"m68: auipc s9, 0xe8faa;"
					"m69: auipc s10, 0xcdbda;"
					"m70: auipc s11, 0x394ee;"
					"m71: auipc t3, 0x06205;"
					"m72: auipc t4, 0xb1ae8;"
					"m73: auipc t5, 0x603da;"
					"m74: auipc t6, 0x454ea;"
					"m75: auipc t0, 0x86503;"
					"m76: auipc t1, 0x59bf6;"
					"m77: auipc t2, 0x3ec21;"
					"m78: auipc a0, 0x38a18;"
					"m79: auipc a1, 0x1610e;"
					"m80: auipc a2, 0xbab7b;"
					"m81: auipc a3, 0xb26e8;"
					"m82: auipc a4, 0x2409f;"
					"m83: auipc a5, 0xbcf6a;"
					"m84: auipc a3, 0x0aed5;"
					"m85: auipc a7, 0xc2331;"
					"m86: auipc s2, 0xc8b9f;"
					"m87: auipc s3, 0x2ff39;"
					"m88: auipc s4, 0x6a394;"
					"m89: auipc s5, 0xabcca;"
					"m90: auipc s6, 0xe84fc;"
					"m91: auipc s7, 0x4460c;"
					"m92: auipc s8, 0x41e76;"
					"m93: auipc s9, 0xa1806;"
					"m94: auipc s10, 0x26ff6;"
					"m95: auipc s11, 0x081d0;"
					"m96: auipc t3, 0x7482c;"
					"m97: auipc t4, 0x22bec;"
					"m98: auipc t5, 0xe6f25;"
					"m99: auipc t6, 0xd8ba9;"

                     );
        asm volatile (" ms: addi zero,zero,2");
        return 0;
    }
}
