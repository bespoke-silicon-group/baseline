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

#define C_NUM_ELEMENTS 4

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, BSG_TILE_GROUP_X_DIM-1, 0, BSG_TILE_GROUP_Y_DIM-1);

int kernel_dest(int *dest,
                const uint32_t nelements){
        
        // To use the Circular Buffer class, instantiate the
        // Dest/Source pair.
        CircularBuffer::Dest<unsigned int, C_SOURCE_Y, C_SOURCE_X, C_DEST_Y, C_DEST_X, C_NUM_ELEMENTS> fifo;

        // THEN, call init_wait. This completes pairing. If multiple
        // Dest/Source pairs are used, you must instantiate ALL of
        // them and THEN call init_wait for each pair.
        
        // It is not possible to do this in the constructor, because
        // there's no guarantee that all Dest/Source objects are
        // constructed in some globally-agreed order to prevent
        // deadlock. This is a better solution.
        fifo.init_wait();

        // Once init is done, we can call 
        const unsigned int * buf_p;

        for(int i = 0; i < 10; ++i){
                buf_p = fifo.obtain_rd_ptr_wait();
                for(int n = 0; n < C_NUM_ELEMENTS; ++n){
                        bsg_print_int(buf_p[n]);
                }
                fifo.finish_rd_ptr();
        }

        for(int i = 0; i < nelements; i += C_NUM_ELEMENTS){
                // Wait until a write pointer is available. 
                buf_p = fifo.obtain_rd_ptr_wait();
                for(int n = 0; n < C_NUM_ELEMENTS; ++n){
                        dest[i + n] = buf_p[n];
                }
                // Signal that that this write pointer is finished.
                fifo.finish_rd_ptr();
        }

        return 0;
}

int kernel_src(const int *src,
               const uint32_t nelements){

        // To use the Circular Buffer class, instantiate the
        // Dest/Source pair.
        CircularBuffer::Source<unsigned int, C_SOURCE_Y, C_SOURCE_X, C_DEST_Y, C_DEST_X, C_NUM_ELEMENTS> fifo;

        // THEN, call init_wait. This completes pairing. If multiple
        // Dest/Source pairs are used, you must instantiate ALL of
        // them and THEN call init_wait for each pair.
        
        // It is not possible to do this in the constructor, because
        // there's no guarantee that all Dest/Source objects are
        // constructed in some globally-agreed order to prevent
        // deadlock. This is a better solution.
        fifo.init_wait();

        unsigned int * buf_p;

        for(int i = 0; i < 10; ++i){
                // Wait until a write pointer is available. 
                buf_p = fifo.obtain_wr_ptr_wait();
                for(int n = 0; n < C_NUM_ELEMENTS; ++n){
                        buf_p[n] = 42 * 1000000 + i * 1000 + n;
                }
                // Signal that that this write pointer is finished.
                fifo.finish_wr_ptr();
        }

        for(int i = 0; i < nelements; i += C_NUM_ELEMENTS){
                // Wait until a write pointer is available. 
                buf_p = fifo.obtain_wr_ptr_wait();
                for(int n = 0; n < C_NUM_ELEMENTS; ++n){
                        buf_p[n] = src[i + n];
                }
                // Signal that that this write pointer is finished.
                fifo.finish_wr_ptr();
        }

        return 0;
}

extern "C" {
        __attribute__((noinline))
        int kernel_tile_circular_buffer(const int *src,
                                        const uint32_t nelements,
                                        int *dest){

                if (__bsg_x == C_DEST_X && __bsg_y == C_DEST_Y){
                        kernel_dest(dest, nelements);
                }

                if (__bsg_x == C_SOURCE_X && __bsg_y == C_SOURCE_Y){
                        kernel_src(src, nelements);
                }
                bsg_print_int(1000 + __bsg_id);

                bsg_tile_group_barrier(&r_barrier, &c_barrier); 

                return 0;
        }
}
