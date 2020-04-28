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
#include <bfs/blocked_dense_i_dense_o_coalesce_dense_o.hpp>

INIT_TILE_GROUP_BARRIER(bfs_r_barrier, bfs_c_barrier,
                        0, bsg_tiles_X-1,
                        0, bsg_tiles_Y-1);

extern "C" int bfs_blocked_dense_i_dense_o_coalesce_dense_o(int V, int E, const node_data_t *rnodes, const int *redges,
                                           int *dense_i,
                                           int *dense_o,
                                           int *visited_io)
{
    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_start();

    bfs::bfs_blocked_dense_i_dense_o_coalesce_dense_o<16>(V, E, rnodes, redges, dense_i, dense_o, visited_io);

    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_end();

    return 0;
}
