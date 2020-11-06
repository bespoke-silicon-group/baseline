#define BSG_TILE_GROUP_X_DIM 16 
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;
#include <bc.hpp>

//#define DEBUG
#ifdef DEBUG
#define pr_dbg(fmt, ...)	\
	bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

__attribute__((section(".dram"))) float  *  num_paths;
__attribute__((section(".dram"))) float  *  dependences;
__attribute__((section(".dram"))) int  * __restrict visited;

template <typename TO_FUNC, typename APPLY_FUNC> int edgeset_apply_push_parallel(int * out_indices, int *out_neighbors, int *from_vertexset, int *next_frontier, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  int start, end;
  local_range(V, &start, &end);
  for(int s = start; s < end; s++) {
    if(from_vertexset[s]) {
      int degree = out_indices[s+1] - out_indices[s];
      int *neighbors = &out_neighbors[s];
      for(int d = 0; d < degree; d++) {
        if(to_func(neighbors[d])) {
          if(apply_func(s, neighbors[d])) {
            next_frontier[d] = 1;
          }
        }
      }
    } 
  }
  barrier.sync();
  return 0;
}

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_pull_parallel_deduplicated_from_vertexset_to_filter_func_with_frontier(int *in_indices , int *in_neighbors, int* from_vertexset, int * next_frontier, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{ 
  int start, end;
  local_range(V, &start, &end);
  if(bsg_id == 0) pr_dbg("start: %i end: %i size: %i\n", start, end, V);
  if(bsg_id == 0) pr_dbg("frontier: 0x%08x\n", &from_vertexset[0]);
  if(bsg_id == 0) pr_dbg("frontier: %i\n", from_vertexset[0]);
  if(bsg_id == 0) pr_dbg(" next frontier: %i\n", next_frontier[0]);
  if(bsg_id == 0) pr_dbg("num_paths: %i\n", (int) num_paths[0]);
  if(bsg_id == 0) pr_dbg("visited: %i\n", visited[0]);
  for ( int d = start; d < end; d++) {
    if (to_func(d)){
        int degree = in_indices[d + 1] - in_indices[d];
        int * neighbors = &in_neighbors[in_indices[d]];
        for(int s = 0; s < degree; s++) { 
          if(from_vertexset[neighbors[s]]) {
            //pr_dbg("%i: found an active vertex: %i\n", bsg_id, neighbors[s]);
            if( apply_func (neighbors[s] , d)) { 
              next_frontier[d] = 1; 
              //pr_dbg("%i: added %i to the next frontier\n", bsg_id, d);  
              //if(!to_func(d)) break;
            }
          }
        } //end of loop on in neighbors
      } //end of to filtering
    } //end of outer for loop
    barrier.sync();
    return 0;
} //end of edgeset apply function 

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_push_parallel_from_vertexset_to_filter_func(int *out_indices , int *out_neighbors, int* from_vertexset, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{ 
      int start, end;
      local_range(V, &start, &end);
      for ( int s = start; s < end; s++) {
        if(from_vertexset[s]) {
          int degree = out_indices[s + 1] - out_indices[s];
          int * neighbors = &out_neighbors[out_indices[s]];
          for(int d = 0; d < degree; d++) { 
            if(to_func(neighbors[d])) { 
              apply_func ( s, neighbors[d] );
            } //end of to func
          } //end of for loop on neighbors
        }
      }
      barrier.sync();
      return 0;
} //end of edgeset apply function 


struct visited_generated_vector_op_apply_func_2
{
  void operator() (int v)
  {
    visited[v] = (int) 0;
  };
};
struct dependences_generated_vector_op_apply_func_1
{
  void operator() (int v)
  {
    dependences[v] = (0) ;
  };
};
struct num_paths_generated_vector_op_apply_func_0
{
  void operator() (int v)
  {
    num_paths[v] = (0) ;
  };
};
struct forward_update
{
  bool operator() (int src, int dst)
  {
    bool output4 ;
    bool num_paths_trackving_var_3 = (bool) 0;
    num_paths[dst] += num_paths[src];
    num_paths_trackving_var_3 = true ; 
    output4 = num_paths_trackving_var_3;
    return output4;
  };
};
struct forward_update_atomic
{
  bool operator() (int src, int dst)
  {
    bool output4 ;
    bool num_paths_trackving_var_3 = (bool) 0;
    writeAdd(num_paths[dst], num_paths[src]);
    num_paths_trackving_var_3 = true ; 
    output4 = num_paths_trackving_var_3;
    return output4;
  };
};
struct visited_vertex_filter
{
  bool operator() (int v)
  {
    bool output ;
    output = (visited[v]) == ((int) 0);
    return output;
  };
};
struct mark_visited
{
  void operator() (int v)
  {
    visited[v] = (int) 1;
  };
};
struct mark_unvisited
{
  void operator() (int v)
  {
    visited[v] = (int) 0;
  };
};
struct backward_vertex_f
{
  void operator() (int v)
  {
    visited[v] = (int) 1;
    dependences[v] += ((1)  / num_paths[v]);
  };
};
struct backward_update
{
  void operator() (int src, int dst)
  {
    dependences[dst] += dependences[src]; 
  };
};
struct final_vertex_f
{
  void operator() (int v)
  {
    if ((num_paths[v]) != ((0) ))
     { 
      dependences[v] = ((dependences[v] - ((1)  / num_paths[v])) * num_paths[v]);
     } 
    else
     { 
      dependences[v] = (0) ;

     } 
  };
};
struct printDependences
{
  void operator() (int v)
  {
    bsg_printf("%f\n", dependences[v]);
  };
};

extern "C" int  __attribute__ ((noinline)) num_paths_generated_vector_op_apply_func_0_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		num_paths_generated_vector_op_apply_func_0()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) dependences_generated_vector_op_apply_func_1_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		dependences_generated_vector_op_apply_func_1()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) visited_generated_vector_op_apply_func_2_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		visited_generated_vector_op_apply_func_2()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_deduplicated_from_vertexset_to_filter_func_with_frontier_call(int *in_indices, int *in_neighbors, int *frontier, int *output, int V, int E, int block_size_x) {
        barrier.sync();
        bsg_cuda_print_stat_start(1);
	edgeset_apply_pull_parallel_deduplicated_from_vertexset_to_filter_func_with_frontier(in_indices, in_neighbors, frontier, output, visited_vertex_filter(), forward_update(), V, E, block_size_x);
        bsg_cuda_print_stat_end(1);
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_push_parallel_deduplicated_from_vertexset_to_filter_func_with_frontier_call(int *out_indices, int *out_neighbors, int *frontier, int *output, int V, int E, int block_size_x) {
        barrier.sync();
        bsg_cuda_print_stat_start(1);
	edgeset_apply_push_parallel(out_indices, out_neighbors, frontier, output, visited_vertex_filter(), forward_update_atomic(), V, E, block_size_x);
        bsg_cuda_print_stat_end(1);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) mark_visited_kernel(int * output, int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		if(output[iter_x] == 1) mark_visited()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) mark_unvisited_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		mark_unvisited()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) backward_vertex_f_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		backward_vertex_f()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_push_parallel_from_vertexset_to_filter_func_call(int *out_indices, int *out_neighbors, int *frontier, int V, int E, int block_size_x) {
	edgeset_apply_push_parallel_from_vertexset_to_filter_func(out_indices, out_neighbors, frontier, visited_vertex_filter(), backward_update(), V, E, block_size_x);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) final_vertex_f_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		final_vertex_f()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) printDependences_kernel(int V) {
	if(bsg_id == 0) {
		for (int iter_x = 0; iter_x < V; iter_x++) {
			printDependences()(iter_x);
		}
	}
	barrier.sync();
	return 0;
}


