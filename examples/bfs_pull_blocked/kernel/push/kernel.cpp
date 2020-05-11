
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


template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier(vertexdata *out_vertices , int *out_neighbors, int* frontier, int * next_frontier, int * parent, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x)
{
  int BLOCK_SIZE = 32; //cache line size
  vertexdata lcl_nodes[ BLOCK_SIZE ];
  int lcl_frontier [ BLOCK_SIZE ];
  int blk_src_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);
  for (int blk_src_i = bsg_id; blk_src_i < blk_src_n; blk_src_i += bsg_tiles_X*bsg_tiles_Y) {
    int block_off = blk_src_i * BLOCK_SIZE;
    memcpy(&lcl_frontier[0], &frontier[block_off], sizeof(lcl_frontier));
    memcpy(&lcl_nodes[0], &out_vertices[block_off], sizeof(lcl_nodes));
    for(int s = 0; s < BLOCK_SIZE; s++) {
      if(lcl_frontier[s] == 0) continue;
      const int * neighbors = &out_neighbors[lcl_nodes[s].offset];
      int dst_n = lcl_nodes[s].degree;
      for( int d = 0; d < dst_n; d++) {
        int dst = neighbors[d];
        if(parent[dst] == -1) {
          next_frontier[dst] = 1;
          parent[dst] = block_off + s;
        } //end of to func
      } //end of for loop on neighbors
    } //end of for loop on source nodes
  } //end of loop on blocks
  barrier.sync();
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

extern "C" int __attribute__ ((noinline)) edgeset_apply_push_parallel_from_vertexset_to_filter_func_with_frontier_call(vertexdata *out_vertices, int *out_neighbors, int *frontier, int *next_frontier, int *parent, int V, int E, int block_size_x) {
  barrier.sync();
  bsg_cuda_print_stat_start(1);
  edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier(out_vertices, out_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
  bsg_cuda_print_stat_end(1);
  barrier.sync();
	return 0;
}
