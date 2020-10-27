#define BSG_TILE_GROUP_X_DIM 16 
#define BSG_TILE_GROUP_Y_DIM 8
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM 
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM

#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;
#include <cc.hpp>

#define DEBUG
#ifdef DEBUG
#define pr_dbg(fmt, ...)		\
	bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

__attribute__((section(".dram"))) int  * IDs;
__attribute__((section(".dram"))) int * update;
template <typename APPLY_FUNC > int edgeset_apply_pull_parallel_deduplicatied_with_frontier(int *in_indices , int *in_neighbors, int * next_frontier, APPLY_FUNC apply_func, int V, int E, int block_size_x) 
{ 
  if(bsg_id == 0) pr_dbg("V: %i\n", V);
  int start, end;
  local_range(V, &start, &end);
  if(bsg_id == ((bsg_tiles_X * bsg_tiles_Y) -1)) pr_dbg("start: %i end: %i\n", start, end);
  for ( int d = start; d < end; d++) {
      int degree = in_indices[d + 1] - in_indices[d];
      int * neighbors = &in_neighbors[in_indices[d]];
      for(int s = 0; s < degree; s++) { 
        if( apply_func ( neighbors[s] , d)) {
          next_frontier[d] = 1; 
        }
      } //end of loop on in neighbors
    } //end of outer for loop
    barrier.sync();
    return 0;
} //end of edgeset apply function 


struct IDs_generated_vector_op_apply_func_0
{
  void operator() (int v)
  {
    IDs[v] = (1) ;
  };
};
struct updateEdge
{
  bool operator() (int src, int dst)
  {
    bool output2 ;
    bool IDs_trackving_var_1 = (bool) 0;
    if ((IDs[dst]) != (IDs[src]))
     {
      if ( ( IDs[dst]) > ( IDs[src]) ) { 
        IDs[dst]= IDs[src]; 
        IDs_trackving_var_1 = true ; 
      } 
     } 
    output2 = IDs_trackving_var_1;
    return output2;
  };
};
struct init
{
  void operator() (int v)
  {
    IDs[v] = v;
  };
};
struct pjump
{
  void operator() (int v)
  {
    int y = IDs[v];
    int x = IDs[y];
    if ((x) != (y))
     { 
      IDs[v] = x;
      update[(0) ] = (1) ;
     } 
  };
};
struct printID
{
  void operator() (int v)
  {
    bsg_printf("%f\n", IDs[v]);
  };
};

extern "C" int  __attribute__ ((noinline)) IDs_generated_vector_op_apply_func_0_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		IDs_generated_vector_op_apply_func_0()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int  __attribute__ ((noinline)) init_kernel(int V) {
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		init()(iter_x);
	}
	barrier.sync();
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_parallel_deduplicated_with_frontier_call(int *in_indices, int *in_neighbors, int *next_frontier, int V, int E, int block_size_x) {
        bsg_cuda_print_stat_start(0);
  	edgeset_apply_pull_parallel_deduplicatied_with_frontier(in_indices, in_neighbors, next_frontier, updateEdge(), V, E, block_size_x);
        bsg_cuda_print_stat_end(0);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) pjump_kernel(int V, int tag) {
        bsg_cuda_print_stat_start(tag);
	int start, end;
	local_range(V, &start, &end);
	for (int iter_x = start; iter_x < end; iter_x++) {
		pjump()(iter_x);
	}
	barrier.sync();
        bsg_cuda_print_stat_end(tag);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) printID_kernel(int V) {
	if(bsg_id == 0) {
		for (int iter_x = 0; iter_x < V; iter_x++) {
			printID()(iter_x);
		}
	}
	barrier.sync();
	return 0;
}


