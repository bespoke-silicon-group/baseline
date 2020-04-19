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
    template <int BLOCK_SIZE, int EDGE_BLOCK_SIZE>
    int bfs_blocked_edge_dense_i_dense_o(int V, int E,
                                     const node_data_t *rnodes,
                                     const int *redges,
                                     int *dense_i,
                                     int *dense_o,
                                     int *visited_io)
    {
        node_data_t lcl_rnodes [BLOCK_SIZE];
        int lcl_visited_io     [BLOCK_SIZE];
        int lcl_redges         [EDGE_BLOCK_SIZE];
        int blk_dst_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);

        for (int blk_dst_i = bsg_id; blk_dst_i < blk_dst_n; blk_dst_i += bsg_tiles_X * bsg_tiles_Y) {
            int blk_dst_base = blk_dst_i * BLOCK_SIZE;
            // load in visited
            memcpy(&lcl_visited_io[0], &visited_io[blk_dst_base],
                   sizeof(lcl_visited_io));
            // load in node info
            memcpy(&lcl_rnodes[0], &rnodes[blk_dst_base],
                   sizeof(lcl_rnodes));

            // make sure there's work to be done in this block
            int sum_degree = 0;
            for (int dst_lcl = 0; dst_lcl < BLOCK_SIZE; dst_lcl++) {
                if (lcl_visited_io[dst_lcl] == 0)
                    sum_degree += lcl_rnodes[dst_lcl].degree;
            }

            // skip this block if we're not
            // going to traverse any edges
            if (sum_degree == 0)
                continue;

            // load in the first block of edges
            int blk_edge_base = lcl_rnodes[0].offset;
            memcpy(&lcl_redges[0], &redges[blk_edge_base], sizeof(lcl_redges));

            for (int dst_lcl = 0; dst_lcl < BLOCK_SIZE; dst_lcl++) {
                // skip if visited
                if (lcl_visited_io[dst_lcl] == 1)
                    continue;

                // the global value of dst
                int dst = blk_dst_base + dst_lcl;

                // look at each in-coming neighbor
                int src_n = lcl_rnodes[dst_lcl].degree;
                int src_base = lcl_rnodes[dst_lcl].offset;
                for (int src_i = 0; src_i < src_n; src_i++) {
                    // src_lcl - index into lcl_redges
                    int src_lcl = src_base + src_i - blk_edge_base;
                    // do we need to pull in the next edge block?
                    if (src_lcl >= EDGE_BLOCK_SIZE) {
                        // skip ahead however many blocks
                        blk_edge_base
                            += EDGE_BLOCK_SIZE
                            * (src_lcl / EDGE_BLOCK_SIZE);
                        // update src_lcl
                        src_lcl = src_lcl % EDGE_BLOCK_SIZE;
                        // do read in the next edge block
                        memcpy(&lcl_redges[0], &redges[blk_edge_base], sizeof(lcl_redges));
                    }

                    // read the next src
                    int src = lcl_redges[src_lcl];
                    pr_dbg("tile %2d: "
                           "(src = %d, dst = %d) "
                           "(blk_edge_base = %d, src_base = %d, src_i = %d, [DRAM] src = %d)\n",
                           bsg_id,
                           src, dst,
                           blk_edge_base, src_base, src_i, redges[src_base + src_i]);

                    // todo: this probably should be blocked somehow
                    if (dense_i[src] == 1) {
                        // pull update
                        lcl_visited_io[dst_lcl] = 1;
                        dense_o[dst] = 1;
                        break; // done with update
                    }
                }
            }

            memcpy(&visited_io[blk_dst_base], &lcl_visited_io[0],
                   sizeof(lcl_visited_io));
        }

        return 0;
    }
}
