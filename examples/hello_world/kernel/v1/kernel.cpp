/*
 * This kernel prints the Hello World message 
 */

#include "bsg_manycore.h"
#include "bsg_set_tile_x_y.h"

#define BSG_TILE_GROUP_X_DIM bsg_tiles_X
#define BSG_TILE_GROUP_Y_DIM bsg_tiles_Y
#define IGNORE_TAG 0
#include "bsg_tile_group_barrier.h"
#include <hello_world.hpp>
#include <cstring>

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {
        int  __attribute__ ((noinline)) kernel_hello_world(int tag) {
                bsg_printf(" Hello World!\n");
                return IGNORE_TAG;
        }
}
