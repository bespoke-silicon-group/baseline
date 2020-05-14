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

template <typename APPLY_FUNC > int edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier(vertexdata * in_vertices, WNode * in_neighbors , int* frontier, int* next_frontier, int* SP, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  bsg_cuda_print_stat_start(1);
  int BLOCK_SIZE = 32;
  vertexdata lcl_nodes [ BLOCK_SIZE ];
  int lcl_next_frontier [ BLOCK_SIZE ];
  int lcl_sp [ BLOCK_SIZE ];
  int blk_dst_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);
  for (int blk_dst_i = bsg_id; blk_dst_i < blk_dst_n; blk_dst_i += bsg_tiles_X * bsg_tiles_Y) {
    int blk_dst_base = blk_dst_i * BLOCK_SIZE;
    memcpy(&lcl_sp[0], &SP[blk_dst_base],sizeof(lcl_sp));
    memcpy(&lcl_nodes[0], &in_vertices[blk_dst_base], sizeof(lcl_nodes));
    memset(&lcl_next_frontier[0], next_frontier[blk_dst_base], sizeof(lcl_next_frontier));
    for ( int d = 0; d < BLOCK_SIZE; d++) {
      int degree = lcl_nodes[d].degree;
      WNode * neighbors = &in_neighbors[lcl_nodes[d].offset];
      for(int s = 0; s < degree; s++) {
        if(frontier[neighbors[s].vertex]) {
          if(lcl_sp[d] > SP[neighbors[s].vertex] + neighbors[s].weight) {
            lcl_next_frontier[d] = 1;
            lcl_sp[d] = SP[neighbors[s].vertex] + neighbors[s].weight;
          }
        }
      } //end of loop on in neighbors
    } //end of dst node for loop
    memcpy(&next_frontier[blk_dst_base], &lcl_next_frontier[0],sizeof(lcl_next_frontier));
    memcpy(&SP[blk_dst_base], &lcl_sp[0], sizeof(lcl_sp));
  } //end of outer blocked loop
  bsg_cuda_print_stat_end(1);
  return 0;
} //end of edgeset apply function


struct updateEdge
{
  bool operator() (int src, int dst, int weight)
  {
    bool output2 ;
    bool SP_trackving_var_1 = (bool) 0;
    //if ( ( SP[dst]) > ( (SP[src] + weight)) ) {
    //  SP[dst]= (SP[src] + weight);
    //  SP_trackving_var_1 = true ;
    //}
    output2 = SP_trackving_var_1;
    return output2;
  };
};



extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier_call(vertexdata *out_indices, WNode *out_neighbors, int *frontier, int * next_frontier, int * SP, int V, int E, int block_size_x) {
  edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier(out_indices, out_neighbors, frontier, next_frontier, SP, updateEdge(), V, E, block_size_x);
  return 0;
}
