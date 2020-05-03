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

    static
    int bfs_sido_rmw(rmw_t *rmw, int rmw_n, int *dense_o, int *visited_io)
    {
        // read
#pragma GCC unroll 32
        for (int rmw_i = 0; rmw_i < rmw_n; rmw_i++) {
            int dst = rmw[rmw_i].dst;
            rmw[rmw_i].v = visited_io[dst];
        }

        // modify-write
        for (int rmw_i = 0; rmw_i < rmw_n; rmw_i++) {
            int dst     = rmw[rmw_i].dst;
            int visited = rmw[rmw_i].v;
            // skip if visited
            if (visited == 1)
                continue;
            // do update
            visited_io[dst] = 1;
            dense_o[dst] = 1;
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

#pragma GCC unroll 32
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
