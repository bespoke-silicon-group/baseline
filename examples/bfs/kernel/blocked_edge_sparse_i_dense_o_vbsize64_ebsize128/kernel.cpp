#include <bfs/bfs-kernel-prologue-epilogue.hpp>
#include <bfs/blocked_edge_sparse_i_dense_o.hpp>

extern "C" int bfs_blocked_edge_sparse_i_dense_o(int V, int E,
                                                 const node_data_t *nodes,
                                                 const int *edges,
                                                 int *blocked_sparse_i,
                                                 int *dense_o,
                                                 int *visited_io)
{
    bfs_kernel_prologue();
    bfs::bfs_blocked_edge_sparse_i_dense_o<64, 128>(V, E, nodes, edges,
                                                    blocked_sparse_i, dense_o, visited_io);

    bfs_kernel_epilogue();
    return 0;
}
