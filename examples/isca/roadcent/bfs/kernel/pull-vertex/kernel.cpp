#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>

#include <bsg_tile_group_barrier.hpp>
bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;

#include <bfs_pull_benchmark.hpp>
#include <cstring>
#include <local_range.h>

#define DEBUG

#ifdef DEBUG
#define pr_dbg(fmt, ...)		\
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

__attribute__((section(".dram"))) int  * __restrict parent;

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(int *in_indices , int *in_neighbors, int* from_vertexset, int * next_frontier, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  bsg_cuda_print_stat_start(1);
  int start, end;
  local_range(V, &start, &end);
  if(bsg_id == 0) { pr_dbg("starting kernel: %i to %i\n", start, end); }
  for ( int d = start; d < end; d++) {
    if(bsg_id == 0 && d % 100 == 0) pr_dbg("on dst vertex: %i\n", d);
    if (to_func(d)){
        int degree = in_indices[d + 1] - in_indices[d];
        int * neighbors = &in_neighbors[in_indices[d]];
        for(int s = 0; s < degree; s++) {
          if(from_vertexset[neighbors[s]]) {
            if( apply_func ( d, neighbors[s] )) {
              next_frontier[d] = 1;
            }
          }
        } //end of loop on in neighbors
      } //end of to filtering
    } //end of outer for loop
    barrier.sync();
    return 0;
} //end of edgeset apply function

struct parent_generated_vector_op_apply_func_0
{
  void operator() (int v)
  {
    parent[v] =  -(1) ;
  };
};
struct updateEdge
{
  bool operator() (int src, int dst)
  {
    bool output2 ;
    parent[dst] = src;
    output2 = (bool) 1; 
    return output2;
  };
};
struct toFilter
{
  bool operator() (int v)
  {
    bool output ;
    output = (parent[v]) == ( -(1) );
    return output;
  };
};

extern "C" int  __attribute__ ((noinline)) parent_generated_vector_op_apply_func_0_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		parent_generated_vector_op_apply_func_0()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call(int *in_indices, int *in_neighbors, int *frontier, int *next_frontier, int V, int E, int block_size_x) {
        edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(in_indices, in_neighbors, frontier, next_frontier, toFilter(), updateEdge(), V, E, block_size_x);
        return 0;
}

