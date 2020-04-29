/*
 * This kernel prints the Hello World message
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.

#include <bfs/bfs-kernel-prologue-epilogue.hpp>
#include "bfs-common.hpp"

extern "C" int bfs_dense_i_dense_o(int V, int E, const node_data_t *rnode_data, const int *redges,
                                   int *dense_i,
                                   int *dense_o,
                                   int *visited_io)
{
    bfs_kernel_prologue();

    for (int dst = bsg_id; dst < V; dst += bsg_tiles_X*bsg_tiles_Y) {
        // skip visited
        if (visited_io[dst] == 1) continue;
        const int *neighbors = &redges[rnode_data[dst].offset];
        int src_n = rnode_data[dst].degree;
        for (int src_i = 0; src_i < src_n; src_i++) {
            int src = neighbors[src_i];
            // skip inactive
            if (dense_i[src] == 0) continue;

            // update
            dense_o[dst] = 1;
            visited_io[dst] = 1;
            break;
        }
    }

    bfs_kernel_epilogue();
    return 0;
}
