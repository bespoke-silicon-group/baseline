
#include "graph_algorithm/csr_setup_graph_data.hpp"
#include "threading/local_range.h"

#define BSG_TILE_GROUP_X_DIM bsg_tiles_X
#define BSG_TILE_GROUP_Y_DIM bsg_tiles_Y

#include "bsg_tile_group_barrier.h"

using formats::csr_blob_header_t;

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, bsg_tiles_X-1, 0, bsg_tiles_Y-1)

static void barrier()
{
    bsg_tile_group_barrier(&r_barrier, &c_barrier);
}

extern "C" int bfs_sparse_in_dense_out
(	const csr_blob_header_t *graph,
	int			*visited,
	const int		*frontier_in_sparse,
	int			*frontier_out_dense)
{
    csr_setup_graph_data(graph);    
    barrier();

    for (int src_i = thread_id(); src_i < NODES; src_i += num_threads()) {
	// get next source vertex
	int src = frontier_in_sparse[src_i];
	if (src == -1) break;
	// get the neighbors and degree
	static_assert(sizeof(int) == sizeof(long int));
	const int *neighbors = (const int*)(&F_NEIGH[F_OFF[src]]);
	int degree = F_DEGREE[src];
	// traverse edges
	for (int dst_i = 0; dst_i < degree; dst_i++) {	    
	    int dst = neighbors[dst_i];
	    // have we visited already?
	    if (visited[dst] != 1) {
		// push update
		visited[dst] = 1;
		frontier_out_dense[dst] = 1;
	    }
	}
    }

    barrier();
    
    return 0;
}

extern "C" int bfs_dense_in_dense_out
(const csr_blob_header_t *graph,
 int                     *visited,
 const int               *frontier_in_dense,
 int                     *frontier_out_dense)
{
    csr_setup_graph_data(graph);
    barrier();

    // get my range
    int dst_s, dst_e;
    local_range(NODES, &dst_s, &dst_e);

    // iterate over all nodes
    for (int dst = dst_s; dst < dst_e; dst++) {
	// visited?
	if (visited[dst] == 1) continue;
	// get the neighbors and degree
	static_assert(sizeof(int) == sizeof(long int));
	const int *neighbors = (const int*)(&B_NEIGH[B_OFF[dst]]);
	int degree = B_DEGREE[dst];
	// traverse edges
	for (int src_i = 0; src_i < degree; src_i++) {
	    int src = neighbors[src_i];
	    if (frontier_in_dense[src] == 1) {
		// pull update
		visited[dst] = 1;
		frontier_out_dense[dst] = 1;
		break; // done with this destination node
	    }
	}
    }
    
    barrier();
    return 0;
}
