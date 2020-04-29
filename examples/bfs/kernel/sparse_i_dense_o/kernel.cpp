#include <bfs/bfs-kernel-prologue-epilogue.hpp>
#include <bsg_manycore.h>

static
int degree(int v, int V, int E, const int *offsets, const int *edges)
{
    return (v < (V-1) ? offsets[v+1]-offsets[v] : E-offsets[v]);
}


extern "C" int bfs_sparse_i_dense_o(int V, int E, const int *offsets, const int *edges,
                                    int *sparse_i,
                                    int *dense_o,
                                    int *visited_io)
{
    bfs_kernel_prologue();

    for (int i = bsg_id; i < V; i += bsg_tiles_X*bsg_tiles_Y) {
        int src = sparse_i[i];
        if (src == -1) break;

        const int *neighbors = &edges[offsets[src]];
        int dst_n = degree(src, V, E, offsets, edges);
        for (int dst_i = 0; dst_i < dst_n; dst_i++) {
            int dst = neighbors[dst_i];
            if (visited_io[dst] == 1) continue;
            visited_io[dst] = 1;
            dense_o[dst] = 1;
        }
    }

    bfs_kernel_epilogue();

    return 0;
}
