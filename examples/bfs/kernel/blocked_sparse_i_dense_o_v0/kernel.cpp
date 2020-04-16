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
#include <bfs-common.hpp>
#include <string.h>

#if !defined(BFS_BLOCK_SIZE)
#error "Please define BFS_BLOCK_SIZE"
#endif

static constexpr int BLOCK_SIZE = BFS_BLOCK_SIZE;

INIT_TILE_GROUP_BARRIER(bfs_r_barrier, bfs_c_barrier,
                        0, bsg_tiles_X-1,
                        0, bsg_tiles_Y-1);

extern "C" int bfs_blocked_sparse_i_dense_o(int V, int E,
                                            const node_data_t *nodes,
                                            const int *edges,
                                            int *blocked_sparse_i,
                                            int *dense_o,
                                            int *visited_io)
{
    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_start();

    node_data_t lcl_nodes [BLOCK_SIZE];
    int lcl_sparse_i      [BLOCK_SIZE];
    int blk_src_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);
        
    for (int blk_src_i = bsg_id; blk_src_i < blk_src_n; blk_src_i += bsg_tiles_X*bsg_tiles_Y) {
        // copy in this block of the frontier
        int blk_off = blk_src_i * BLOCK_SIZE;
        memcpy(&lcl_sparse_i[0], &blocked_sparse_i[blk_off],
               BLOCK_SIZE * sizeof(blocked_sparse_i[0]));
        bsg_printf("reading in block @ 0x%08x\n", &blocked_sparse_i[blk_off]);
        // does this have at least one active source?
        bsg_printf("lcl_sparse_i[0] = %d\n", lcl_sparse_i[0]);
        if (lcl_sparse_i[0] == -1) continue;
        // copy in blocks of the other data
        // copy in node info
        memcpy(&lcl_nodes[0], &nodes[blk_off],
               BLOCK_SIZE * sizeof(nodes[0]));
        
        for (int src_i = 0; src_i < BLOCK_SIZE; src_i++) {            
            int src = lcl_sparse_i[src_i];

            bsg_printf("blk = %d, src =%d\n", blk_src_i, src);
            
            if (src == -1) break;
            // index into local data
            int src_lcl = src - blk_off;
            // neighbors of this source
            const int *neighbors = &edges[lcl_nodes[src_lcl].offset];
            // degree of this source
            int dst_n = lcl_nodes[src_lcl].degree;
            // bsg_printf("src =%d, degree = %d, neigbors = 0x%08x\n",
            //            src, dst_n, neighbors);
            
            // for each out neighbor...
            for (int dst_i = 0; dst_i < dst_n; dst_i++) {
                // read the dst out of dram
                int dst = neighbors[dst_i];
                // skip if already visited
                if (visited_io[dst] == 1)
                    continue;
                // update
                visited_io[dst] = 1;
                dense_o[dst] = 1;
            }
        }
    }

    bsg_tile_group_barrier(&bfs_r_barrier, &bfs_c_barrier);
    bsg_cuda_print_stat_kernel_end();

    return 0;
}
