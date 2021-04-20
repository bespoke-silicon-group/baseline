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
#include <set.hpp>
#include <cmath>

//#define DEBUG_DIJKSTRA_TRACE
//#define DEBUG_DIJKSTRA
//#define DEBUG_DIJKSTRA_ROOT_GOAL

#define array_size(array)                       \
    (sizeof(array)/sizeof(array[0]))

extern "C" int dijkstra(struct graph *g_mem,
                        int root,
                        int goal,
                        bsg_attr_remote float *distance,
                        bsg_attr_remote int   *path,
                        int *unvisited)
{
    struct graph g = *g_mem;    
    distance[root] = 0.0;
    path[root] = root;

    DenseSet<int>(unvisited, g.V);
#ifdef DEBUG_DIJKSTRA
    bsg_printf("g_mem=0x%08x, root=%4d, goal=%4d\n",
           reinterpret_cast<unsigned>(g_mem), root, goal);
#endif
#ifdef DEBUG_DIJKSTRA_ROOT_GOAL
    bsg_print_int(root);
    bsg_print_int(goal);
#endif    
    bsg_cuda_print_stat_kernel_start();

    while (!unvisited.empty()) {
        int best = -1;
        float dbest = INFINITY;

        float distance_lcl[32];
        for (int v0 = 0; v0 < g.V; v0 += array_size(distance_lcl)) {
            memcpy(distance_lcl, &distance[v0], sizeof(distance_lcl));
            for (int vi = 0; vi < array_size(distance_lcl); vi++) {
                int v = v0+vi;
                if (unvisited.in(v)) {
                    if (distance_lcl[vi] < dbest) {
                        best = v;
                        dbest = distance_lcl[vi];
                    }
                }
            }
        }

#ifdef DEBUG_DIJKSTRA_TRACE
        bsg_print_int(-best);
#endif        
        if (best == goal)
            break;

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
            }
        }
        unvisited.remove(best);
    }

    bsg_cuda_print_stat_kernel_end();

    return 0;
}
