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

template <typename APPLY_FUNC > int edgeset_apply_push_serial_weighted_deduplicatied_from_vertexset_with_frontier(vertexdata *out_indices , WNode *out_neighbors, int* frontier, int* next_frontier, int * SP, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  bsg_cuda_print_stat_start(1);
  int BLOCK_SIZE = 32; //cache line size
  vertexdata lcl_nodes[ BLOCK_SIZE ];
  int lcl_frontier [ BLOCK_SIZE ];
  int blk_src_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);
  for (int blk_src_i = bsg_id; blk_src_i < blk_src_n; blk_src_i += bsg_tiles_X*bsg_tiles_Y) {
    int block_off = blk_src_i * BLOCK_SIZE;
    memcpy(&lcl_frontier[0], &frontier[block_off], sizeof(lcl_frontier));
    memcpy(&lcl_nodes[0], &out_indices[block_off], sizeof(lcl_nodes));
    for(int s = 0; s < BLOCK_SIZE; s++) {
      if(lcl_frontier[s] == 0) continue;
      const WNode * neighbors = &out_neighbors[lcl_nodes[s].offset];
      int dst_n = lcl_nodes[s].degree;
      for( int d = 0; d < dst_n; d++) {
        WNode dst = neighbors[d];
        if( apply_func ( s , dst.vertex, dst.weight , SP)) {
          next_frontier[dst.vertex] = 1;
        }
      } //end of for loop on neighbors
    } //end of for loop on source nodes
  } //end of loop on blocks
  //barrier.sync();
  bsg_cuda_print_stat_end(1);
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



extern "C" int __attribute__ ((noinline)) edgeset_apply_push_serial_weighted_deduplicatied_from_vertexset_with_frontier_call(vertexdata *out_indices, WNode *out_neighbors, int *frontier, int * next_frontier, int * SP, int V, int E, int block_size_x) {
  edgeset_apply_push_serial_weighted_deduplicatied_from_vertexset_with_frontier(out_indices, out_neighbors, frontier, next_frontier, SP, updateEdge(), V, E, block_size_x);
  barrier.sync();
  return 0;
}
