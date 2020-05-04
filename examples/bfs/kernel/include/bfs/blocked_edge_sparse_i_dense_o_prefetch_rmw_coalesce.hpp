#pragma once
#include <bfs-common.hpp>
#include <cstring>
#include <hammerblade_vanilla_memcpy.hpp>
#include <hammerblade_vanilla_load_multistride.hpp>
//#define DEBUG
#if defined DEBUG
#define pr_dbg(fmt, ...)                        \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(...)
#endif

// might want to make a blocked array class
namespace bfs {

    typedef struct rmw {
        int dst;
        int v;
    } rmw_t;

    static int bfs_sido_rmw(rmw_t *__restrict rmw,
                            int rmw_n,
                            int *__restrict dense_o,
                            int *__restrict visited_io)
    {
        // r
        for (int rmw_i = 0; rmw_i < rmw_n; rmw_i+=4) {
            int dst_0 = rmw[rmw_i+0].dst;
            int dst_1 = rmw[rmw_i+1].dst;
            int dst_2 = rmw[rmw_i+2].dst;
            int dst_3 = rmw[rmw_i+3].dst;

            asm volatile ( "" ::: "memory");

            int v_0, v_1, v_2, v_3;
            v_0 = visited_io[dst_0];
            if (rmw_i+1 < rmw_n) {
                v_1 = visited_io[dst_1];
                if (rmw_i+2 < rmw_n) {
                    v_2 = visited_io[dst_2];
                    if (rmw_i+3 < rmw_n) {
                        v_3 = visited_io[dst_3];
                    }
                }
            }

            asm volatile ("" ::: "memory");

            rmw[rmw_i+0].v = v_0;
            if (rmw_i+1 < rmw_n) {
                rmw[rmw_i+1].v = v_1;
                if (rmw_i+2 < rmw_n) {
                    rmw[rmw_i+2].v = v_2;
                    if (rmw_i+3 < rmw_n) {
                        rmw[rmw_i+3].v = v_3;
                    }
                }
            }
        }

        // mw
        for (int rmw_i = 0; rmw_i < rmw_n; rmw_i+=1) {
            int dst = rmw[rmw_i].dst;
            int v   = rmw[rmw_i].v;
            if (v == 0) {
                visited_io[dst] = 1;
                dense_o[dst]    = 1;
            }
        }

        return 0;
    }

    template <int BLOCK_SIZE, int EDGE_BLOCK_SIZE, int RMW_BLOCK_SIZE>
    static int bfs_blocked_edge_sparse_i_dense_o_prefetch_rmw_coalesce(int V, int E,
                                                                       const node_data_t *nodes,
                                                                       const int *edges,
                                                                       int *blocked_sparse_i,
                                                                       int *dense_o,
                                                                       int *visited_io)
    {
        node_data_t lcl_nodes [BLOCK_SIZE];
        int lcl_sparse_i      [BLOCK_SIZE];
        int lcl_edges    [EDGE_BLOCK_SIZE];
        rmw_t rmw         [RMW_BLOCK_SIZE];
        int   rmw_n = 0;

        int blk_src_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);

        for (int blk_src_i = bsg_id; blk_src_i < blk_src_n; blk_src_i += bsg_tiles_X*bsg_tiles_Y) {
            // copy in this block of the frontier
            int blk_src_base = blk_src_i * BLOCK_SIZE;
            hammerblade::vanilla::memcpy<BLOCK_SIZE>(&lcl_sparse_i[0],
                                                     &blocked_sparse_i[blk_src_base],
                                                     sizeof(lcl_sparse_i));

            pr_dbg("reading in block @ 0x%08x\n", &blocked_sparse_i[blk_src_base]);
            // does this have at least one active source?
            pr_dbg("lcl_sparse_i[0] = %d\n", lcl_sparse_i[0]);

            if (lcl_sparse_i[0] == -1) continue;
            // copy in blocks of the other data
            // copy in node info
            hammerblade::vanilla::memcpy<BLOCK_SIZE>(&lcl_nodes[0],
                                                     &nodes[blk_src_base],
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
            hammerblade::vanilla::memcpy<EDGE_BLOCK_SIZE>(&lcl_edges[0],
                                                          &edges[blk_edge_base],
                                                          sizeof(lcl_edges));

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
                        // load in data
                        hammerblade::vanilla::load_multistride<EDGE_BLOCK_SIZE>
                            (&lcl_edges[0], &edges[blk_edge_base]);
                    }

                    // proceed with update
                    int dst = lcl_edges[dst_lcl];
                    pr_dbg("traversing (%d,%d)\n", src, dst);

                    // coalesce RMWs
                    rmw[rmw_n++].dst = lcl_edges[dst_lcl];

                    // do perform RMWs if we have enough of them
                    if (rmw_n == RMW_BLOCK_SIZE) {
                        bfs_sido_rmw(rmw, rmw_n, dense_o, visited_io);
                        rmw_n = 0;
                    }
                }
            }
        }

        // flush remaining RMWs
        bfs_sido_rmw(rmw, rmw_n, dense_o, visited_io);

        return 0;
    }
}
