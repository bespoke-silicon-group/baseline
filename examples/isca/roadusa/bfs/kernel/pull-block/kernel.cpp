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

template <typename APPLY_FUNC > int edgeset_apply_pull_parallel_from_vertexset_with_frontier(vertexdata *in_vertices , int *in_neighbors, int* frontier, int * next_frontier, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{ 
  int BLOCK_SIZE = 32; //cache line size
  vertexdata lcl_nodes [ BLOCK_SIZE ];
  int lcl_next_frontier [ BLOCK_SIZE ];
  int blk_dst_n = V/BLOCK_SIZE + (V%BLOCK_SIZE == 0 ? 0 : 1);
  for (int blk_dst_i = bsg_id; blk_dst_i < blk_dst_n; blk_dst_i += bsg_tiles_X * bsg_tiles_Y) {
    int blk_dst_base = blk_dst_i * BLOCK_SIZE;
    memcpy(&lcl_nodes[0], &in_vertices[blk_dst_base], BLOCK_SIZE * sizeof(lcl_nodes[0]));
    memset(&lcl_next_frontier[0], next_frontier[blk_dst_base], BLOCK_SIZE * sizeof(lcl_nodes[0]));
    for ( int d = 0; d < BLOCK_SIZE; d++) {
      if (parent[blk_dst_base + d] != 1)
        continue; //skip visited nodes
        int degree = lcl_nodes[d].degree;
        int * neighbors = &in_neighbors[lcl_nodes[d].offset];
        for(int s = 0; s < degree; s++) {
          if(frontier[neighbors[s]]) {
            if(bsg_id == 0) pr_dbg("inside: %i\n", blk_dst_base + d);
            if( apply_func ( neighbors[s], blk_dst_base + d )) {
              lcl_next_frontier[d] = 1;
            }
          }
        } //end of loop on in neighbors
    } //end of dst node for loop
    memcpy(&next_frontier[blk_dst_base], &lcl_next_frontier[0],BLOCK_SIZE * sizeof(lcl_nodes[0]));
  } //end of outer blocked loop
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
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_from_vertexset_with_frontier_call(vertexdata *out_indices, int *out_neighbors, int *frontier, int *next_frontier, int V, int E, int block_size_x) {
	edgeset_apply_pull_parallel_from_vertexset_with_frontier(out_indices, out_neighbors, frontier, next_frontier, updateEdge(), V, E, block_size_x);
	return 0;
}


