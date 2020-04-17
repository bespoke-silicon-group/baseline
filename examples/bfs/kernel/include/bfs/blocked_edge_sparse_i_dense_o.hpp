#pragma once
#include <bfs-common.hpp>
#include <string.h>

//#define DEBUG
#if defined DEBUG
#define pr_dbg(fmt, ...)                        \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(...)
#endif

// might want to make a blocked array class
namespace bfs {
    template <int BLOCK_SIZE, int EDGE_BLOCK_SIZE>
    int bfs_blocked_edge_sparse_i_dense_o(int V, int E,
                                          const node_data_t *nodes,
                                          const int *edges,
                                          int *blocked_sparse_i,
                                          int *dense_o,
                                          int *visited_io)
    {
        node_data_t lcl_nodes [BLOCK_SIZE];
        int lcl_sparse_i      [BLOCK_SIZE];
        int lcl_edges    [EDGE_BLOCK_SIZE];
        int blk_src_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);

        for (int blk_src_i = bsg_id; blk_src_i < blk_src_n; blk_src_i += bsg_tiles_X*bsg_tiles_Y) {
            // copy in this block of the frontier
            int blk_src_base = blk_src_i * BLOCK_SIZE;
            memcpy(&lcl_sparse_i[0], &blocked_sparse_i[blk_src_base],
                   sizeof(lcl_sparse_i));

            pr_dbg("reading in block @ 0x%08x\n", &blocked_sparse_i[blk_src_base]);
            // does this have at least one active source?
            pr_dbg("lcl_sparse_i[0] = %d\n", lcl_sparse_i[0]);

            if (lcl_sparse_i[0] == -1) continue;
            // copy in blocks of the other data
            // copy in node info
            memcpy(&lcl_nodes[0], &nodes[blk_src_base],
                   sizeof(lcl_nodes));

            // location of the first edge block
            int blk_edge_base = lcl_nodes[0].offset;
            pr_dbg("blk_src_base = %d, blk_edge_base = %d\n",
                   blk_src_base, blk_edge_base);

            // sum the degree
            int blk_sum_degree = 0;
            for (int src_i = 0; src_i < BLOCK_SIZE; src_i++) {
                blk_sum_degree += lcl_nodes[src_i].degree;
            }

            // skip if there are no edges here
            if (blk_sum_degree == 0)
                continue;

            // load in the first block of edges
            memcpy(&lcl_edges[0], &edges[blk_edge_base], sizeof(lcl_edges));

            for (int src_i = 0; src_i < BLOCK_SIZE; src_i++) {
                int src = lcl_sparse_i[src_i];
                pr_dbg("src = %d\n", src);

                // -1 marks the end of this block
                if (src == -1)
                    break;

                int src_lcl = src - blk_src_base;
                // get the degree
                int dst_n = lcl_nodes[src_lcl].degree;
                // get the edges
                int dst_base = lcl_nodes[src_lcl].offset;
                pr_dbg("dst_base = %d, degree = %d\n", dst_base, dst_n);

                for (int dst_i = 0; dst_i < dst_n; dst_i++) {
                    // index into lcl_edges
                    int dst_lcl = dst_base + dst_i - blk_edge_base;
                    pr_dbg("dst_lcl = %d\n", dst_lcl);

                    // do we need to pull in the next edge block?
                    if (dst_lcl >= EDGE_BLOCK_SIZE) {
                        // skip ahead however many blocks
                        blk_edge_base
                            += EDGE_BLOCK_SIZE
                            * (dst_lcl / EDGE_BLOCK_SIZE);
                        // update dst_lcl
                        dst_lcl = dst_lcl % EDGE_BLOCK_SIZE;
                        memcpy(&lcl_edges[0], &edges[blk_edge_base], sizeof(lcl_edges));
                    }

                    // proceed with update
                    int dst = lcl_edges[dst_lcl];
                    pr_dbg("traversing (%d,%d)\n", src, dst);

                    // skip if already visited
                    if (visited_io[dst] == 1)
                        continue;

                    // update
                    visited_io[dst] = 1;
                    dense_o[dst] = 1;
                }
            }
        }

        return 0;
    }
}
