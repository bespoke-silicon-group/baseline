/*
 * This kernel prints the Hello World message 
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 1
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <graph.hpp>
#include <heap.hpp>
#include <cmath>

//#define DEBUG_DIJKSTRA_TRACE
//#define DEBUG_DIJKSTRA
//#define DEBUG_DIJKSTRA_ROOT_GOAL

// g_mem is reverse graph
extern "C" int dijkstra(struct graph *g_mem,
                        int root,
                        int goal,
                        bsg_attr_remote float *distance,
                        bsg_attr_remote int   *path,
                        int *queue_mem)
{
    struct graph g = *g_mem;    
    distance[root] = 0.0;
    path[root] = root;

#ifdef DEBUG_DIJKSTRA_ROOT_GOAL
    bsg_print_int(root);
    bsg_print_int(goal);
#endif
    
    //int num_iters = g.V-1;
    int num_iters = 2; // two iterations for now..
    // time the second iteration
            
    for (int iter = 0; iter < num_iters; iter++) {
        if (iter == 1)
            bsg_cuda_print_stat_kernel_start();

        for (int dst = 0; dst < g.V; dst++) {
            int dst_n = dst == g.V-1 ? g.E-g.offsets[dst] : g.offsets[dst+1]-g.offsets[dst];
            int dst_0 = g.offsets[dst];
#ifdef DEBUG_DIJKSTRA_TRACE
            bsg_print_int(-dst);
#endif
            for (int dst_i = 0; dst_i < dst_n; dst_i++) {
                int src = g.neighbors[dst_0+dst_i];
#ifdef DEBUG_DIJKSTRA_TRACE
                bsg_print_int(src);
#endif
                float w = g.weights[dst_0+dst_i];
                if (distance[src]+w < distance[dst]) {
                    distance[dst] = distance[src]+w;
                    path[dst] = src;
                }
            }
        }

        if (iter == 1)
            bsg_cuda_print_stat_kernel_end();
    }
    
    bsg_cuda_print_stat_kernel_end();
    
    return 0;
}
