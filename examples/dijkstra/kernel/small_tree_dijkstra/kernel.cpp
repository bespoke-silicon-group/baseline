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
#include <cstring>

//#define DEBUG_DIJKSTRA_TRACE
//#define DEBUG_DIJKSTRA

// g_mem is the inverse graph (transpose)
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
    int   offsets[g.V];
    int   neighbors[g.E];
    float weights[g.E];

    memcpy(distance,  distance_mem, sizeof(float)*g.V);
    memcpy(path,      path_mem, sizeof(int)*g.V);
    memcpy(offsets,   g.offsets, sizeof(int)*g.V);
    memcpy(neighbors, g.neighbors, sizeof(int)*g.E);
    memcpy(weights,   g.weights, sizeof(float)*g.E);

    g.offsets = offsets;
    g.neighbors = neighbors;
    g.weights = weights;

#ifdef DEBUG_DIJKSTRA
    printf("g_mem=0x%08x, root=%4d, goal=%4d\n",
           reinterpret_cast<unsigned>(g_mem), root, goal);
#endif    
    bsg_print_int(root);
    bsg_print_int(goal);

    bsg_cuda_print_stat_kernel_start();

    int next = goal;
    int current = !next;    
    float d_goal = 0.0;

    while (current != next && next != root) {
        current = next;        
#ifdef DEBUG_DIJKSTRA_TRACE
        bsg_print_int(-current);
#endif
        int src_n = current == g.V-1 ? (g.E - g.offsets[current]) : (g.offsets[current+1] - g.offsets[current]);
        if (src_n == 0)
            continue;

        // topology of graph is tree (so only one incoming edge)
        int src_0 = g.offsets[current];
        int src = g.neighbors[src_0];
        float w = g.weights[src_0];
        
#ifdef DEBUG_DIJKSTRA_TRACE            
        bsg_print_int(src);
#endif
        d_goal += w;
        path[current] = src;
        next = src;
    }

    bsg_cuda_print_stat_kernel_end();

    if (next == root) {
        distance_mem[goal] = d_goal;
        memcpy(path_mem, path, sizeof(path));        
    }
    
    return 0;
}
