
#define BSG_TILE_GROUP_X_DIM 16
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;

#include <bfs_pull_benchmark.hpp>
#include <cstring>
//# define DEBUG

#ifdef DEBUG
#define pr_dbg(fmt, ...)                        \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(vertexdata *in_vertices , int *in_neighbors, int * frontier, int * next_frontier, int * parent, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  int BLOCK_SIZE = 32;
  vertexdata lcl_nodes [ BLOCK_SIZE ];
  int lcl_next_frontier [ BLOCK_SIZE ];
  int lcl_visited [ BLOCK_SIZE ];
  int blk_dst_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);
  if(bsg_id == 0) pr_dbg("num blocks: %i\n", blk_dst_n);
  for (int blk_dst_i = bsg_id; blk_dst_i < blk_dst_n; blk_dst_i += bsg_tiles_X * bsg_tiles_Y) {
    if(bsg_id == 0) pr_dbg("on block: %i / %i\n", blk_dst_i, blk_dst_n);
    int blk_dst_base = blk_dst_i * BLOCK_SIZE;
    memcpy(&lcl_visited[0], &parent[blk_dst_base],sizeof(lcl_visited));
    memcpy(&lcl_nodes[0], &in_vertices[blk_dst_base], sizeof(lcl_nodes));
    memset(&lcl_next_frontier[0], 0, sizeof(lcl_next_frontier));
    for ( int d = 0; d < BLOCK_SIZE; d++) {
      if ( lcl_visited[d] != -1)
        continue; //skip visited nodes
      //if (to_func(d) && from_vertexset[d] == 1){
      int degree = lcl_nodes[d].degree;
      int * neighbors = &in_neighbors[lcl_nodes[d].offset];
      if(bsg_id == 0) pr_dbg("inside block, degree = %i \n", degree);
			for(int s = 0; s < degree; s++) {
        int src = neighbors[s];
        if(frontier[src] == 1) {
          lcl_next_frontier[d] = 1;
          lcl_visited[d] = src;
        }
      } //end of loop on in neighbors
    } //end of dst node for loop
    memcpy(&next_frontier[blk_dst_base], &lcl_next_frontier[0],sizeof(lcl_next_frontier));
    memcpy(&parent[blk_dst_base], &lcl_visited[0], sizeof(lcl_visited));
  } //end of outer blocked loop
  pr_dbg("reached end of loop %i,\n", bsg_id);

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

extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call(vertexdata *out_vertices, int *out_neighbors, int *frontier, int *next_frontier, int *parent, int V, int E, int block_size_x) {
  barrier.sync();
  bsg_cuda_print_stat_start(1);
  edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(out_vertices, out_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
  bsg_cuda_print_stat_end(1);
  barrier.sync();
	return 0;
}
