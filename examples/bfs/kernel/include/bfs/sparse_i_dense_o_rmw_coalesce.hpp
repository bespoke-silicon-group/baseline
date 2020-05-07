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

    static
    int degree(int v, int V, int E, const int *offsets, const int *edges)
    {
        return (v < (V-1) ? offsets[v+1]-offsets[v] : E-offsets[v]);
    }

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

    template <int BLOCK_SIZE>
    static
    int bfs_sparse_i_dense_o_rmw_coalesce(int V, int E,
                                          const int *offsets,
                                          const int *edges,
                                          int *sparse_i,
                                          int *dense_o,
                                          int *visited_io)
    {
        rmw_t rmw [BLOCK_SIZE];
        int   rmw_n = 0;

        for (int i = bsg_id; i < V; i += bsg_tiles_X*bsg_tiles_Y) {
            int src = sparse_i[i];
            if (src == -1) break;

            const int *neighbors = &edges[offsets[src]];
            int dst_n = degree(src, V, E, offsets, edges);

            for (int dst_i = 0; dst_i < dst_n; dst_i++) {
                int dst = neighbors[dst_i];
                rmw[rmw_n++].dst = dst;
                // check if we are at capacity for RMW
                if (rmw_n == BLOCK_SIZE) {
                    bfs_sido_rmw(rmw, rmw_n, dense_o, visited_io);
                    rmw_n = 0;
                }
            }
        }

        bfs_sido_rmw(rmw, rmw_n, dense_o, visited_io);
        return 0;
    }
}
