/*
 * This kernel prints the Hello World message
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.

#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <bfs-common.hpp>
#include <string.h>
#include <bfs/blocked_edge_sparse_i_dense_o_prefetch.hpp>

INIT_TILE_GROUP_BARRIER(bfs_r_barrier, bfs_c_barrier,
                        0, bsg_tiles_X-1,
                        0, bsg_tiles_Y-1);

extern "C" int bfs_blocked_edge_sparse_i_dense_o(int V, int E,
                                                 const node_data_t *nodes,
                                                 const int *edges,
                                                 int *blocked_sparse_i,
                                                 int *dense_o,
                                                 int *visited_io)
{
    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_start();

    bfs::bfs_blocked_edge_sparse_i_dense_o_prefetch<32, 64>(V, E, nodes, edges, // graph data
                                                            blocked_sparse_i, // frontier
                                                            dense_o, // output frontier
                                                            visited_io); // visited vertices

    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_end();

    return 0;
}
