/*
 * This kernel prints the Hello World message
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include "bfs-common.hpp"
#include <hello_world.hpp>

INIT_TILE_GROUP_BARRIER(bfs_r_barrier, bfs_c_barrier,
                        0, bsg_tiles_X-1,
                        0, bsg_tiles_Y-1);

extern "C" int bfs_dense_i_dense_o(int V, int E, const node_data_t *rnode_data, const int *redges,
                                   int *dense_i,
                                   int *dense_o,
                                   int *visited_io)
{
    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_start();

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

    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_end();

    return 0;
}