// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses memcpy as a baseline.
//   * memcpy is unrolled by a factor of 8 internally (https://sourceware.org/git/gitweb.cgi?p=newlib-cygwin.git;a=blob;f=newlib/libc/machine/riscv/memcpy.c)

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 2
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <cstdint>
#include <cstring>
#include <bsg_circular_buffer.hpp>

#define C_SOURCE_X 0
#define C_SOURCE_Y 0

#define C_DEST_X 1
#define C_DEST_Y 0

int kernel_dest(){
        std::array<volatile unsigned int, 8> buf;
        CircularBuffer<volatile unsigned int, 4, 2, C_SOURCE_Y,C_SOURCE_X, C_DEST_Y,C_DEST_X> foo = CircularBuffer<volatile unsigned int, 4, 2, C_SOURCE_Y,C_SOURCE_X, C_DEST_Y,C_DEST_X>(buf);
        foo.wait();
        return 0;
}

int kernel_src(){
        std::array<volatile unsigned char, 2> occ;
        CircularBuffer<volatile unsigned int, 4, 2, C_SOURCE_Y,C_SOURCE_X, C_DEST_Y,C_DEST_X> foo = CircularBuffer<volatile unsigned int, 4, 2, C_SOURCE_Y,C_SOURCE_X, C_DEST_Y,C_DEST_X>(occ);
        foo.wait();
        return 0;
}

extern "C" {
        __attribute__((noinline))
        int kernel_tile_circular_buffer(const int *src,
                                        const uint32_t i_nelements,
                                        int *dest){

                if (__bsg_x == C_DEST_X && __bsg_y == C_DEST_Y){
                        kernel_dest();
                }

                if (__bsg_x == C_SOURCE_X && __bsg_y == C_SOURCE_Y){
                        kernel_src();
                }
                bsg_print_int(42); // TODO: Only seeing 42 from one tile
                return 0;
        }
}
