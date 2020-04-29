#include <bfs/bfs-kernel-prologue-epilogue.hpp>
#include <bfs/blocked_edge_sparse_i_dense_o_prefetch.hpp>

extern "C" int bfs_blocked_edge_sparse_i_dense_o(int V, int E,
                                                 const node_data_t *nodes,
                                                 const int *edges,
                                                 int *blocked_sparse_i,
                                                 int *dense_o,
                                                 int *visited_io)
{
    bfs_kernel_prologue();
    bfs::bfs_blocked_edge_sparse_i_dense_o_prefetch<32, 64>(V, E, nodes, edges, // graph data
                                                            blocked_sparse_i, // frontier
                                                            dense_o, // output frontier
                                                            visited_io); // visited vertices
    bfs_kernel_epilogue();

    return 0;
}
