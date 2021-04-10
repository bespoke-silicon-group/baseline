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
#include <string.h>

//#define DEBUG_DIJKSTRA_TRACE

// if the entire graph can fit in local memory
extern "C" int dijkstra(struct graph *g_mem,
                        int root,
                        int goal,
                        float *distance_mem,
                        int   *path_mem,
                        int *unused)
{
    struct graph g = *g_mem;

    float distance[g.V];
    int   path[g.V];
    int   queue_mem[g.V];
    int   offsets[g.V];
    int   neighbors[g.E];
    float weights[g.E];

    memcpy(distance, distance_mem, sizeof(float)*g.V);
    memcpy(path,     path_mem, sizeof(int)*g.V);
    memset(queue_mem, 0, sizeof(int)*g.V);
    memcpy(offsets, g.offsets, sizeof(int)*g.V);
    memcpy(neighbors, g.neighbors, sizeof(int)*g.E);
    memcpy(weights, g.weights, sizeof(float)*g.E);

    g.offsets = offsets;
    g.neighbors = neighbors;
    g.weights = weights;
    
    distance[root] = 0.0;
    path[root] = root;

    bsg_cuda_print_stat_kernel_start();

    auto cmp = [&distance](int lhs, int rhs) {
        return distance[lhs] < distance[rhs];
    };

    DynHeap<int, decltype(cmp)> queue(queue_mem, g.V, cmp);
    queue.push(root);

    while (!queue.empty()) {
        int best = queue.pop();        
        if (best == goal)
            break;
#ifdef DEBUG_DIJKSTRA_TRACE
        bsg_print_int(-best);
#endif
        float d_best = distance[best];

        int dst_n = best == g.V-1 ? (g.E - g.offsets[best]) : (g.offsets[best+1] - g.offsets[best]);
        int dst_0 = g.offsets[best];
        for (int dst_i = 0; dst_i < dst_n; dst_i++) {
            int dst = g.neighbors[dst_0+dst_i];
#ifdef DEBUG_DIJKSTRA_TRACE            
            bsg_print_int(dst);
#endif
            float w = g.weights[dst_0+dst_i];            
            // relax edge
            if (d_best+w < distance[dst]) {
                distance[dst] = d_best+w;
                path[dst] = best;
                queue.push(dst);                
            }
        }
    }
    bsg_cuda_print_stat_kernel_end();
    memcpy(distance_mem, distance, sizeof(distance));
    memcpy(path_mem, path, sizeof(path));
    return 0;
}
