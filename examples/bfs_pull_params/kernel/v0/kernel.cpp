// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, bsg_tiles_X-1, 0, bsg_tiles_Y-1);

#include <bfs_pull_benchmark.hpp>
#include <cstring>
#include <local_range.h>

template <typename TO_FUNC , typename APPLY_FUNC> int edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(int *in_indices , int *in_neighbors, int * frontier, int * next_frontier, int * parent, TO_FUNC to_func, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{

  bsg_print_hexadecimal((unsigned int) frontier);
  //bsg_cuda_print_stat_start(1);
  int start, end;
  local_range(V, &start, &end);
  for ( int d = start; d < end; d++) {
    //if (to_func(d)){ 
      if(d < V-1) {
        if (parent[d] == -1){ 
          int degree = in_indices[d + 1] - in_indices[d];
          int * neighbors = &in_neighbors[in_indices[d]];
          //for(int s = in_indices[d]; s < in_indices[d+1]; s++) {
          for(int s = 0; s < degree; s++) {
            //if(frontier[in_neighbors[s]] == 1) {       
            //if( apply_func( in_neighbors[s], d )) { 
            int src = neighbors[s];
            //bool active = (frontier[src] == 1);
            //if(active){
            //bsg_printf("attempt to print from global scalar: %i\n", frontier[src]);
            //bsg_print_hexadecimal((unsigned int) &frontier[src]);
            if(frontier[src] == 1) {
            //if( apply_func( src, d )) { 
              //parent[d] = in_neighbors[s];
              //bsg_print_hexadecimal((unsigned int) &parent[d]);
              parent[d] = src;
              next_frontier[d] = 1;
              //if(bsg_id == 0) { iter++; } 
            }
          } //end of loop on in neighbors
        } //end of to filtering
      }
      else if(d == V-1) {
        if(parent[d] == -1) {
          int degree = E - in_indices[d];
          int * neighbors = &in_neighbors[in_indices[d]];
          //for(int s = in_indices[d]; s < E; s++) {
          for(int s = 0; s < degree; s++) {
            int src = neighbors[s];
            //if(frontier[in_neighbors[s]] == 1) {
            //if(apply_func(src, d)) {
            //bool active = (frontier[src] == 1);
            //if(active){
            if(frontier[src] == 1) {
              //bsg_print_hexadecimal((unsigned int) &parent[d]);
              //parent[d] = in_neighbors[s];
              parent[d] = src;
              next_frontier[d] = 1;
              //if(bsg_id == 0) { iter++; }
            }
          }
        }
      }
  } //end of outer for loop
  bsg_printf("reached end of loop %i\n", bsg_id);
  //bsg_cuda_print_stat_end(1);
  //bsg_tile_group_barrier(&r_barrier, &c_barrier);
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
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
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
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call(int *in_indices, int *in_neighbors, int * frontier, int * next_frontier, int * parent, int V, int E, int block_size_x) {
        bsg_cuda_print_stat_start(1);
        bsg_printf("before call to kernel\n");
        edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier(in_indices, in_neighbors, frontier, next_frontier, parent, toFilter(), updateEdge(), V, E, block_size_x);
        bsg_cuda_print_stat_end(1);
  	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}


