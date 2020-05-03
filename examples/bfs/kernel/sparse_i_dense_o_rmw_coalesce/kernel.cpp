#include <bfs/bfs-kernel-prologue-epilogue.hpp>
#include <bfs/sparse_i_dense_o_rmw_coalesce.hpp>
#include <bsg_manycore.h>


extern "C" int bfs_sparse_i_dense_o(int V, int E, const int *offsets, const int *edges,
                                    int *sparse_i,
                                    int *dense_o,
                                    int *visited_io)
{
    bfs_kernel_prologue();

    bfs::bfs_sparse_i_dense_o_rmw_coalesce<256>
        (V, E, offsets, edges, sparse_i, dense_o, visited_io);

    bfs_kernel_epilogue();

    return 0;
}
