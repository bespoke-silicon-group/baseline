#define BSG_TILE_GROUP_X_DIM 16
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM

#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>

bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;

#include <sssp_pull.hpp>
#include <cstring>

//#define DEBUG

#ifdef DEBUG
#define pr_dbg(fmt, ...)      \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif
template <typename APPLY_FUNC > int edgeset_apply_push_serial_weighted_deduplicatied_from_vertexset_with_frontier(int *out_indices , WNode *out_neighbors, int* from_vertexset, int * next_frontier, int * SP, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
    bsg_cuda_print_stat_start(1);
    int start, end;
    edge_aware_local_range(V, E, &start, &end, out_indices);
    for ( int s=start; s < end; s++) {
      if(from_vertexset[s]) {
        int degree = out_indices[s + 1] - out_indices[s];
        WNode * neighbors = &out_neighbors[out_indices[s]];
        for(int d = 0; d < degree; d++) {
          if( apply_func ( s , neighbors[d].vertex, neighbors[d].weight , SP )  ) {
            next_frontier[neighbors[d].vertex] = 1;
          }
        } //end of for loop on neighbors
      }
    }
    bsg_cuda_print_stat_end(1);
    barrier.sync();
    return 0;
} //end of edgeset apply function


struct updateEdge
{
  bool operator() (int src, int dst, int weight, int * SP)
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


extern "C" int __attribute__ ((noinline)) edgeset_apply_push_serial_weighted_deduplicatied_from_vertexset_with_frontier_call(int *out_indices, WNode *out_neighbors, int *frontier, int * next_frontier, int * SP, int V, int E, int block_size_x) {
	edgeset_apply_push_serial_weighted_deduplicatied_from_vertexset_with_frontier(out_indices, out_neighbors, frontier, next_frontier, SP, updateEdge(), V, E, block_size_x);

	return 0;
}
