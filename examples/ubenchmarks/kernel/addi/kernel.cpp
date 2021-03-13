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
                         "li t0,0x74b0dc51;"
                         "li t1,0x19495cff;"
                         "li t2,0x2ae8944a;"
                         "li a0,0x46e87ccd;"
                         "li a1,0x3d1b58ba;"
                         "li a2,0x507ed7ab;"
                         "li a3,0x2eb141f2;"
                         "li a4,0x41b71efb;"
                         "li a5,0x79e2a9e3;"
                         "li a6,0x7545e146;"
                         "li a7,0x515f007c;"
                         "li s2,0x5bd062c2;"
                         "li s3,0x12200854;"
                         "li s4,0x4db127f8;"
                         "li s5,0x216231b;"
                         "li s6,0x1f16e9e8;"
                         "li s7,0x1190cde7;"
                         "li s8,0x66ef438d;"
                         "li s9,0x140e0f76;"
                         "li s10,0x3352255a;"
                         "li s11,0x109cf92e;"
                         "li t3,0xded7263;"
                         "li t4,0x7fdcc233;"
                         "li t5,0x1befd79f;"
                       );
        asm volatile ("addi zero,zero,1");
        asm volatile (
                        "andi t0, t0, 1975;"
                        "andi t1, t1, 561;"
                        "andi t2, t2, 1112;"
                        "andi s1, s1, 346;"
                        "andi a0, a0, 293;"
                        "andi a1, a1, 349;"
                        "andi a2, a2, 261;"
                        "andi a3, a3, 791;"
                        "andi a4, a4, 88;"
                        "andi a5, a5, 745;"
                        "andi a6, a6, 1118;"
                        "andi a7, a7, 212;"
                        "andi s2, s2, 1451;"
                        "andi s3, s3, 1202;"
                        "andi s4, s4, 205;"
                        "andi s5, s5, 198;"
                        "andi s6, s6, 1691;"
                        "andi s7, s7, 1716;"
                        "andi s8, s8, 1108;"
                        "andi s9, s9, 1553;"
                        "andi s10, s10, 1038;"
                        "andi s11, s11, 1410;"
                        "andi t3, t3, 116;"
                        "andi t4, t4, 1601;"
                        "andi t5, t5, 1313;"
                        "andi t0, t0, 1975;"
                        "andi t1, t1, 561;"
                        "andi t2, t2, 1112;"
                        "andi s1, s1, 346;"
                        "andi a0, a0, 293;"
                        "andi a1, a1, 349;"
                        "andi a2, a2, 261;"
                        "andi a3, a3, 791;"
                        "andi a4, a4, 88;"
                        "andi a5, a5, 745;"
                        "andi a6, a6, 1118;"
                        "andi a7, a7, 212;"
                        "andi s2, s2, 1451;"
                        "andi s3, s3, 1202;"
                        "andi s4, s4, 205;"
                        "andi s5, s5, 198;"
                        "andi s6, s6, 1691;"
                        "andi s7, s7, 1716;"
                        "andi s8, s8, 1108;"
                        "andi s9, s9, 1553;"
                        "andi s10, s10, 1038;"
                        "andi s11, s11, 1410;"
                        "andi t3, t3, 116;"
                        "andi t4, t4, 1601;"
                        "andi t5, t5, 1313;"
                        "andi t0, t0, 1975;"
                        "andi t1, t1, 561;"
                        "andi t2, t2, 1112;"
                        "andi s1, s1, 346;"
                        "andi a0, a0, 293;"
                        "andi a1, a1, 349;"
                        "andi a2, a2, 261;"
                        "andi a3, a3, 791;"
                        "andi a4, a4, 88;"
                        "andi a5, a5, 745;"
                        "andi a6, a6, 1118;"
                        "andi a7, a7, 212;"
                        "andi s2, s2, 1451;"
                        "andi s3, s3, 1202;"
                        "andi s4, s4, 205;"
                        "andi s5, s5, 198;"
                        "andi s6, s6, 1691;"
                        "andi s7, s7, 1716;"
                        "andi s8, s8, 1108;"
                        "andi s9, s9, 1553;"
                        "andi s10, s10, 1038;"
                        "andi s11, s11, 1410;"
                        "andi t3, t3, 116;"
                        "andi t4, t4, 1601;"
                        "andi t5, t5, 1313;"
                        "andi t0, t0, 1975;"
                        "andi t1, t1, 561;"
                        "andi t2, t2, 1112;"
                        "andi s1, s1, 346;"
                        "andi a0, a0, 293;"
                        "andi a1, a1, 349;"
                        "andi a2, a2, 261;"
                        "andi a3, a3, 791;"
                        "andi a4, a4, 88;"
                        "andi a5, a5, 745;"
                        "andi a6, a6, 1118;"
                        "andi a7, a7, 212;"
                        "andi s2, s2, 1451;"
                        "andi s3, s3, 1202;"
                        "andi s4, s4, 205;"
                        "andi s5, s5, 198;"
                        "andi s6, s6, 1691;"
                        "andi s7, s7, 1716;"
                        "andi s8, s8, 1108;"
                        "andi s9, s9, 1553;"
                        "andi s10, s10, 1038;"
                        "andi s11, s11, 1410;"
                        "andi t3, t3, 116;"
                        "andi t4, t4, 1601;"
                        "andi t5, t5, 1313;"
                    );
        asm volatile ("addi zero,zero,2");
        return 0;
    }
}
