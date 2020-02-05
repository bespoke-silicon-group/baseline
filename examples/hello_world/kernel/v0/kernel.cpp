/*
 * This kernel prints the Hello World message 
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 1
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X bsg_tiles_X
#define bsg_tiles_Y bsg_tiles_Y
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>

#include <hello_world.hpp>

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
        int  __attribute__ ((noinline)) kernel_hello_world(int arg) {
                bsg_printf("Hello World! Tile Group Tile-ID: %d, Arg: %d\n", __bsg_id, arg);
                return 0;
        }
}
