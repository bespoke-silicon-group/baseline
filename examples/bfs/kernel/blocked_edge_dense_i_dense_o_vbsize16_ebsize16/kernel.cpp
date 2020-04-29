#include <bfs/bfs-kernel-prologue-epilogue.hpp>
#include <bfs/blocked_edge_dense_i_dense_o.hpp>

extern "C" int bfs_blocked_edge_dense_i_dense_o(int V, int E,
                                                const node_data_t *rnodes, const int *redges,
                                                int *dense_i,
                                                int *dense_o,
                                                int *visited_io)
{
    bfs_kernel_prologue();
    bfs::bfs_blocked_edge_dense_i_dense_o<16, 16>(V, E, rnodes, redges, dense_i, dense_o, visited_io);
    bfs_kernel_epilogue();
    return 0;
}
