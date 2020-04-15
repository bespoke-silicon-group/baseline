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
#include <hello_world.hpp>
#include "bfs-common.hpp"

INIT_TILE_GROUP_BARRIER(bfs_r_barrier, bfs_c_barrier,
                        0, bsg_tiles_X-1,
                        0, bsg_tiles_Y-1);

int degree(int v, int V, int E, const int *offsets, const int *edges)
{
    return (v < (V-1) ? offsets[v+1]-offsets[v] : E-offsets[v]);
}

extern "C" int bfs_sparse_in_dense_out(int V, int E,
                                       const node_data_t *node_data,
                                       const int *edges,
                                       int *sparse_i,
                                       int *dense_o,
                                       int *visited_io)
{
    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_start();

    for (int i = bsg_id; i < V; i += bsg_tiles_X*bsg_tiles_Y) {
        int src = sparse_i[i];
        if (src == -1) break;

        const int *neighbors = &edges[node_data[src].offset];
        int dst_n = node_data[src].degree;
        for (int dst_i = 0; dst_i < dst_n; dst_i++) {
            int dst = neighbors[dst_i];
            if (visited_io[dst] == 1) continue;
            visited_io[dst] = 1;
            dense_o[dst] = 1;
        }
    }

    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_end();

    return 0;
}
