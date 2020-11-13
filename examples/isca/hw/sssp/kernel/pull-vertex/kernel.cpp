#define BSG_TILE_GROUP_X_DIM 16 
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;
#include <sssp.hpp>

//#define DEBUG
#ifdef DEBUG
#define pr_dbg(fmt, ...)	\
	bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif


__attribute__((section(".dram"))) int  * __restrict dist;

template <typename APPLY_FUNC> int edgeset_apply_push_parallel(int * out_indices, WNode *out_neighbors, int *from_vertexset, int *next_frontier, APPLY_FUNC apply_func, int V, int E, int block_size_x) {
  int start, end;
  local_range(V, &start, &end);
  pr_dbg("%i: %i to %i\n", bsg_id, start, end);
  for(int s = start; s < end; s++) {
    //if(s % 100 == 0) pr_dbg("%i on vtx %i\n", bsg_id, s);
    if(s < V && from_vertexset[s]) 
    { pr_dbg("working on src: %i\n", s);
      int degree = out_indices[s+1] - out_indices[s];
      WNode * neighbors = &out_neighbors[out_indices[s]];
      for(int d = 0; d < degree; d++) {
        if(apply_func(s, neighbors[d].vertex, neighbors[d].weight)) {
          next_frontier[d] = 1;
        }
      }
    }
  }
}

template <typename APPLY_FUNC > int edgeset_apply_pull_parallel_weighted_deduplicated_from_vertexset_with_frontier(int *in_indices , WNode *in_neighbors, int* from_vertexset, int * next_frontier, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{ 
  int start, end;
  local_range(V, &start, &end);
  if(bsg_id == 0) pr_dbg("elem 1: %i and dist: %i\n", from_vertexset[1], dist[1]);
  for ( int d = start; d < end; d++) {
    int degree = in_indices[d + 1] - in_indices[d];
    WNode * neighbors = &in_neighbors[in_indices[d]];
    for(int s = 0; s < degree; s++) { 
      if(from_vertexset[neighbors[s].vertex]) {
        if( apply_func ( neighbors[s].vertex, d, neighbors[s].weight )) { 
          next_frontier[d] = 1;
        }
      }
    } //end of loop on in neighbors
  } //end of outer for loop
  barrier.sync();
  return 0;
} //end of edgeset apply function 


struct dist_generated_vector_op_apply_func_0
{
  void operator() (int v)
  {
    dist[v] = (2147483647) ;
  };
};
struct updateEdge
{
  bool operator() (int src, int dst, int weight)
  {
    bool output3 = false;
    int new_dist = (dist[src] + weight);
    if(dist[dst] > new_dist) {
      dist[dst] = new_dist;
      output3 = true;
    }
    return output3;
  };
};
struct updateEdgeAtomic
{
  bool operator() (int src, int dst, int weight)
  {
    bool output1;
    int new_dist = (dist[src] + weight);
    output1 = writeMin(dist[dst], new_dist);
    return output1;
  }
};

struct printDist
{
  void operator() (int v)
  {
    bsg_printf("%i\n", dist[v]);
  };
};
struct reset
{
  void operator() (int v)
  {
    dist[v] = (2147483647) ;
  };
};

extern "C" int  __attribute__ ((noinline)) dist_generated_vector_op_apply_func_0_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		dist_generated_vector_op_apply_func_0()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) reset_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		reset()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_weighted_deduplicated_from_vertexset_with_frontier_call(int *in_indices, WNode *in_neighbors,int *out_indices, WNode *out_neighbors, int *frontier, int *modified_vertexsubset1, int V, int E, int block_size_x) {
        if(bsg_id == 0) pr_dbg("inside the kernel\n");
        barrier.sync();
        bsg_cuda_print_stat_start(1);
        if(calculate_direction(frontier, out_indices, V, E)){
        if(bsg_id == 0) pr_dbg("pull\n");
	  edgeset_apply_pull_parallel_weighted_deduplicated_from_vertexset_with_frontier(in_indices, in_neighbors, frontier, modified_vertexsubset1, updateEdge(), V, E, block_size_x);
        } else {
        if(bsg_id == 0) pr_dbg("push\n");
          edgeset_apply_push_parallel(out_indices, out_neighbors, frontier, modified_vertexsubset1, updateEdgeAtomic(), V, E, block_size_x);
        }
        bsg_cuda_print_stat_end(1);
	return 0;
}


