#include <bfs/bfs-kernel-prologue-epilogue.hpp>

static
int degree(int v, int V, int E, const int *offsets, const int *edges)
{
    return (v < (V-1) ? offsets[v+1]-offsets[v] : E-offsets[v]);
}

extern "C" int bfs_dense_i_dense_o(int V, int E, const int *roffsets, const int *redges,
                                   int *dense_i,
                                   int *dense_o,
                                   int *visited_io)
{
    bfs_kernel_prologue();

    for (int dst = bsg_id; dst < V; dst += bsg_tiles_X*bsg_tiles_Y) {
        // skip visited
        if (visited_io[dst] == 1) continue;
        const int *neighbors = &redges[roffsets[dst]];
        int src_n = degree(dst, V, E, roffsets, redges);
        for (int src_i = 0; src_i < src_n; src_i++) {
            int src = neighbors[src_i];
            // skip inactive
            if (dense_i[src] == 0) continue;

            // update
            dense_o[dst] = 1;
            visited_io[dst] = 1;
            break;
        }
    }

    bfs_kernel_epilogue();

    return 0;
}
