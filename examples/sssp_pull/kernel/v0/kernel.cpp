#define BSG_TILE_GROUP_X_DIM 16
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM

#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;

#include <sssp_pull.hpp>
#include <cstring>

#define DEBUG

#ifdef DEBUG
#define pr_dbg(fmt, ...)			\
		bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif


template <typename APPLY_FUNC > int edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier(int * in_indices, WNode * in_neighbors , int* frontier, int* next_frontier, int* SP, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  bsg_cuda_print_stat_start(1);
  int start, end;
  local_range(V, &start, &end);
  pr_dbg("id: %i, start: %i, end: %i \n", bsg_id, start, end);
  for ( int d=start; d < end; d++) {
    if(bsg_id == 0 && (d % 50 == 0)) pr_dbg("d: %i / %i \n", d, end);
    if(d < V) {
      for(int s = in_indices[d]; s < in_indices[d+1]; s++) {
        WNode src = in_neighbors[s];
        if(frontier[src.vertex]) {
          if( apply_func( in_neighbors[s].vertex, d , in_neighbors[s].weight, SP)) {
            next_frontier[d] = 1;
          }
        }
      } //end of loop on in neighbors
    }
  } //end of outer for loop
  bsg_cuda_print_stat_end(1);
  barrier.sync();
  return 0;
} //end of edgeset apply function


struct SP_generated_vector_op_apply_func_0
{
  void operator() (int v, int * SP)
  {
    SP[v] = (2147483647) ; //this is supposed to be int max
  };
};
struct updateEdge
{
  bool operator() (int src, int dst, float weight, int * SP)
  {
    bool output2 ;
    bool SP_trackving_var_1 = (bool) 0;
    if ( ( SP[dst]) > ( (SP[src] + weight)) ) {
      SP[dst]= (SP[src] + weight);
      SP_trackving_var_1 = true ;
    }
    output2 = SP_trackving_var_1;
    return output2;
  };
};
struct reset
{
  void operator() (int v, int * SP)
  {
    SP[v] = (2147483647) ;
  };
};

extern "C" int  __attribute__ ((noinline)) SP_generated_vector_op_apply_func_0_kernel(int * SP, int V, int E, int block_size_x) {
  int start, end;
  local_range(V, &start, &end);
	for (int v = start; v < end; v++) {
		if (v < V) {
			SP_generated_vector_op_apply_func_0()(v, SP);
		}
		else {
			break;
		}
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) reset_kernel(int * SP, int V, int E, int block_size_x) {
  int start, end;
  local_range(V, &start, &end);
	for (int v = start; v < end; v++) {
		if (v < V) {
			reset()(v, SP);
		}
		else {
			break;
		}
	}
	barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier_call(int *out_indices, WNode *out_neighbors, int *frontier, int * next_frontier, int * SP, int V, int E, int block_size_x) {
	edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier(out_indices, out_neighbors, frontier, next_frontier, SP, updateEdge(), V, E, block_size_x);
	return 0;
}
