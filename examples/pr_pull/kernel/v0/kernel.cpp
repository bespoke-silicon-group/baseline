
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, bsg_tiles_X-1, 0, bsg_tiles_Y-1);

#include <pr_pull.hpp>
#include <cstring>

#ifdef DEBUG
#define pr_dbg(fmt, ...)                        \
    bsg_printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

//TODO: get rid of these/use these as params instead of globals
__attribute__((section(".dram"))) double  * __restrict old_rank;
__attribute__((section(".dram"))) double  * __restrict new_rank;
__attribute__((section(".dram"))) int  * __restrict out_degree;
__attribute__((section(".dram"))) double  * __restrict contrib;
__attribute__((section(".dram"))) double  * __restrict error;
__attribute__((section(".dram"))) int  * __restrict generated_tmp_vector_2;
//keep these:
__attribute__((section(".dram"))) float damp;
__attribute__((section(".dram"))) float beta_score;

template <typename APPLY_FUNC > int edgeset_apply_pull_serial(int *in_indices , int *in_neighbors, int * new_rank, int * contrib, APPLY_FUNC apply_func, int V, int E)
{
    for ( int d=0; d < V; d++) {
    for(int s = in_indices[d]; s < in_indices[d+1]; s++) {
      apply_func( in_neighbors[s], d , new_rank, contrib);
    } //end of loop on in neighbors
  } //end of outer for loop
  bsg_tile_group_barrier(&r_barrier, &c_barrier);
  return 0;
} //end of edgeset apply function


struct error_generated_vector_op_apply_func_5
{
  void operator() (int v, int * error)
  {
    error[v] = ((float) 0) ;
  };
};
struct contrib_generated_vector_op_apply_func_4
{
  void operator() (int v, int * contrib)
  {
    contrib[v] = ((float) 0) ;
  };
};
struct generated_vector_op_apply_func_3
{
  void operator() (int v, int * out_degree, int * generated_tmp_vector_2)
  {
    out_degree[v] = generated_tmp_vector_2[v];
  };
};
struct new_rank_generated_vector_op_apply_func_1
{
  void operator() (int v, int * new_rank)
  {
    new_rank[v] = ((float) 0) ;
  };
};
struct old_rank_generated_vector_op_apply_func_0
{
  void operator() (int v, int * old_rank, int E)
  {
    old_rank[v] = (((float) 1)  / E);
  };
};
struct computeContrib
{
  void operator() (int v, int * old_rank, int * out_degree)
  {
    contrib[v] = (old_rank[v] / out_degree[v]);
  };
};
struct updateEdge
{
  void operator() (int src, int dst, int * new_rank, int * contrib)
  {
    new_rank[dst] += contrib[src];
  };
};
struct updateVertex
{
  void operator() (int v, int * old_rank, int *new_rank, int * error)
  {
    double old_score = old_rank[v];
    new_rank[v] = (beta_score + (damp * new_rank[v]));
    error[v] = fabs((new_rank[v] - old_rank[v])) ;
    old_rank[v] = new_rank[v];
    new_rank[v] = ((float) 0) ;
  };
};

struct reset
{
  void operator() (int v, int * old_rank, int * new_rank, int E)
  {
    old_rank[v] = (((float) 1)  / E);
    new_rank[v] = ((float) 0) ;
  };
};

extern "C" int  __attribute__ ((noinline)) old_rank_generated_vector_op_apply_func_0_kernel(int * old_rank, int V, int E) {
	int start, end;
  local_range(V, &start, &end);
	for (int d = start; d < end; d++) {
	   old_rank_generated_vector_op_apply_func_0()(d, old_rank, E);
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) new_rank_generated_vector_op_apply_func_1_kernel(int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
	//		new_rank_generated_vector_op_apply_func_1()(start_x + iter_x);
		}
		else {
			break;
		}
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) generated_vector_op_apply_func_3_kernel(int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
//			generated_vector_op_apply_func_3()(start_x + iter_x);
		}
		else {
			break;
		}
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) contrib_generated_vector_op_apply_func_4_kernel(int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
//			contrib_generated_vector_op_apply_func_4()(start_x + iter_x);
		}
		else {
			break;
		}
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) error_generated_vector_op_apply_func_5_kernel(int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
//			error_generated_vector_op_apply_func_5()(start_x + iter_x);
		}
		else {
			break;
		}
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) reset_kernel(int V, int E, int block_size_x) {
	int start_x = block_size_x * (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x);
	for (int iter_x = __bsg_id; iter_x < block_size_x; iter_x += bsg_tiles_X * bsg_tiles_Y) {
		if ((start_x + iter_x) < V) {
//			reset()(start_x + iter_x);
		}
		else {
			break;
		}
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) computeContrib_kernel(int * old_rank, int * out_degree, int V) {
  int start, end;
  local_range(V, &start, &end);
	for (int d = start; d < end; d++) {
		computeContrib()(d, old_rank, out_degree);
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
extern "C" int __attribute__ ((noinline)) edgeset_apply_pull_serial_call(int *out_indices, int *out_neighbors, int * new_rank, int * contrib, int V, int E) {
	edgeset_apply_pull_serial(out_indices, out_neighbors, new_rank, contrib, updateEdge(), V, E);
	return 0;
}
extern "C" int  __attribute__ ((noinline)) updateVertex_kernel(int * old_rank, int *new_rank, int * error, int V, int E) {
  int start, end;
  local_range(V, &start, &end);
	for (int d = start; d < end; d++) {
			updateVertex()(d, old_rank, new_rank, error);
	}
	bsg_tile_group_barrier(&r_barrier, &c_barrier);
	return 0;
}
