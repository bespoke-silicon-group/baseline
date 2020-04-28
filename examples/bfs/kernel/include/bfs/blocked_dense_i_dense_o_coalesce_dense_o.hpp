#pragma once
#include <bfs-common.hpp>
#include <string.h>

#if defined DEBUG
#define pr_dbg(fmt, ...)                        \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(...)
#endif

namespace bfs {
    template <int BLOCK_SIZE>
    int bfs_blocked_dense_i_dense_o_coalesce_dense_o(int V, int E,
                                                     const node_data_t *rnodes,
                                                     const int *redges,
                                                     int *dense_i,
                                                     int *dense_o,
                                                     int *visited_io)
    {
        node_data_t lcl_nodes [BLOCK_SIZE];
        int lcl_dense_o       [BLOCK_SIZE];
        int lcl_visited_io    [BLOCK_SIZE];
        int blk_dst_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);

        for (int blk_dst_i = bsg_id;
             blk_dst_i < blk_dst_n;
             blk_dst_i += bsg_tiles_X * bsg_tiles_Y)
        {
            // global offset of this block of dest nodes
            int blk_dst_base = blk_dst_i * BLOCK_SIZE;

            // load in visited
            memcpy(&lcl_visited_io[0], &visited_io[blk_dst_base],
                   sizeof(lcl_visited_io));
            // load in node info
            memcpy(&lcl_nodes[0], &rnodes[blk_dst_base],
                   sizeof(lcl_nodes));
            // clear local dense_o
            memset(&lcl_dense_o[0], 0, sizeof(lcl_dense_o));

            for (int dst_i = 0; dst_i < BLOCK_SIZE; dst_i++) {
                // skip if visited
                if (lcl_visited_io[dst_i] == 1)
                    continue;

                // look at each in coming neighbor
                int dst = blk_dst_base + dst_i;
                int src_n = lcl_nodes[dst_i].degree;
                const int *neighbors = &redges[lcl_nodes[dst_i].offset];

                for (int src_i = 0; src_i < src_n; src_i++) {
                    int src = neighbors[src_i];
                    pr_dbg("src = %d\n", src);
                    if (dense_i[src] == 1) {
                        // pull update
                        lcl_visited_io[dst_i] = 1;
                        lcl_dense_o[dst_i] = 1;
                        break;
                    }
                }
            }

            // flush dense_o
            memcpy(&dense_o[blk_dst_base], &lcl_dense_o[0],
                   sizeof(lcl_dense_o));

            memcpy(&visited_io[blk_dst_base], &lcl_visited_io[0],
                   sizeof(lcl_visited_io));
        }

        return 0;
    }
}
