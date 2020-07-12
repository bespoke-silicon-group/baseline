#define BSG_TILE_GROUP_X_DIM 16
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;

#include <bfs_pull_benchmark.hpp>
#include <cstring>
#include <local_range.h>

#ifdef DEBUG
#define pr_dbg(fmt, ...)                        \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier(int *out_indices , int *out_neighbors, int* from_vertexset, int * next_frontier, int * parent, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
    int start, end;
    local_range(V, &start, &end);
    for ( int s=start; s < end; s++) {
      if(from_vertexset[s]) {
        int degree = out_indices[s + 1] - out_indices[s];
        int * neighbors = &out_neighbors[out_indices[s]];
        for(int d = 0; d < degree; d++) {
          if(parent[neighbors[d]] == -1) {
            parent[neighbors[d]] = s;
            next_frontier[neighbors[d]] = 1;
          } //end of to func
        } //end of for loop on neighbors
      }
    }
    //barrier.sync();
    return 0;
} //end of edgeset apply function



struct updateEdge
{
  bool operator() (int src, int dst, int * parent)
  {
    bool output1 ;
    parent[dst] = src;
    output1 = (bool) 1;
    return output1;
  };
};
struct toFilter
{
  bool operator() (int v, int * parent)
  {
    bool output ;
    output = (parent[v]) == ( -(1) );
    return output;
  };
};


extern "C" int __attribute__ ((noinline)) edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier_call(int *out_indices, int *out_neighbors, int *frontier, int *next_frontier, int *parent, int V, int E, int block_size_x) {
  barrier.sync();
  bsg_cuda_print_stat_start(1);
	edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier(out_indices, out_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
  bsg_cuda_print_stat_end(1);
  barrier.sync();
	return 0;
}
