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

#ifdef DEBUG_DIJKSTRA
    printf("g_mem=0x%08x, root=%4d, goal=%4d\n",
           reinterpret_cast<unsigned>(g_mem), root, goal);
#endif    
    bsg_print_int(root);
    bsg_print_int(goal);

    auto cmp = [distance](int lhs, int rhs) {
        return distance[lhs] < distance[rhs];
    };

    bsg_cuda_print_stat_kernel_start();

    int converged = 0;
    int next_best = root;
    int best = !next_best;

    while (best != next_best && best != goal) {
#ifdef DEBUG_DIJKSTRA_TRACE
        bsg_print_int(-best);
#endif
        best = next_best;

        float d_best = distance[best];
        int dst_n = best == g.V-1 ? (g.E - g.offsets[best]) : (g.offsets[best+1] - g.offsets[best]);
        if (dst_n == 0)
            continue;

        // topology of graph is list
        int dst_0 = g.offsets[best];
        int dst = g.neighbors[dst_0];

#ifdef DEBUG_DIJKSTRA_TRACE            
        bsg_print_int(dst);
#endif
        float w = g.weights[dst_0];
        // relax edge
        if (d_best+w < distance[dst]) {
            distance[dst] = d_best+w;
            path[dst] = best;
            next_best = dst;
        }
    }
    bsg_cuda_print_stat_kernel_end();

    return 0;
}
