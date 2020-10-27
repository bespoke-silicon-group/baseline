// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
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
#include <calculate_direction.h>
#define DEBUG
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

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(int *in_indices , int *in_neighbors, int * frontier, int * next_frontier, int * parent, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{

  int start, end;
  local_range(V, &start, &end);
  for ( int d = start; d < end; d++) {
        if (parent[d] == -1){ 
          int degree = in_indices[d + 1] - in_indices[d];
          int * neighbors = &in_neighbors[in_indices[d]];
          for(int s = 0; s < degree; s++) {
            int src = neighbors[s];
            if(frontier[src] == 1) {
              parent[d] = src;
              next_frontier[d] = 1;
	      			break;
            }
          } //end of loop on in neighbors
        } //end of to filtering
  } //end of outer for loop
  return 0;
} //end of edgeset apply function 


struct parent_generated_vector_op_apply_func_0
{
  void operator() (int v, int * parent)
  {
    parent[v] =  -(1) ;
  };
};
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
struct reset
{
  void operator() (int v, int * parent)
  {
    parent[v] =  -(1) ;
  };
};

extern "C" int  __attribute__ ((noinline)) parent_generated_vector_op_apply_func_0_kernel(int * parent, int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
			parent_generated_vector_op_apply_func_0()(start_x + iter_x, parent);
		}
		else {
			break;
		}
	}
	barrier.sync();
  return 0;
}
extern "C" int  __attribute__ ((noinline)) reset_kernel(int * parent, int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
			reset()(start_x + iter_x, parent);
		}
		else {
			break;
		}
	}
  barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call(int *in_indices, int *in_neighbors, int * frontier, int * next_frontier, int * parent, int V, int E, int block_size_x) {
  barrier.sync();
	edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(in_indices, in_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
	barrier.sync();
	return 0;
}

extern "C" int __attribute__ ((noinline)) edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier_call(int *out_indices, int *out_neighbors, int *frontier, int *next_frontier, int *parent, int V, int E, int block_size_x) {
  barrier.sync();
  edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier(out_indices, out_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
  barrier.sync();
  return 0;
}

extern "C" int __attribute__ ((noinline)) edgeset_apply_hybrid_parallel_call(int *out_indices, int *out_neighbors, int * in_indices, int * in_neighbors, int *frontier, int *next_frontier, int *parent, int V, int E, int block_size_x, int iter) { 
  barrier.sync();
  if(bsg_id == 1) bsg_printf("calculate direction: %i \n", iter);
  //bsg_cuda_print_stat_start(iter);
  int pull = calculate_direction(frontier, out_indices, V, E);
  bsg_cuda_print_stat_start(iter);
  if(pull == 1) {
    if(bsg_id == 1) bsg_printf("pull direction\n");
	  edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(in_indices, in_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
  }
  else {
    if(bsg_id == 1) bsg_printf("push direction\n");
    edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier(out_indices, out_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
  }
  bsg_cuda_print_stat_end(iter);
  barrier.sync();
  return 0;
}
