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
//#define DEBUG_DIJKSTRA_ROOT_GOAL

template <int TILING, typename HeapType>
__attribute__((noinline))
void visit_neighbors(struct graph &g,
                     int src,
                     float src_d,
                     float *__restrict distance,
                     int *__restrict path,
                     HeapType &queue)
{
    // ids and weights of dst nodes
    int dst_v[TILING+1];
    float w_v[TILING+1];
    // distance of dst nodes
    float distance_v[TILING+3];
    bool push_v[TILING] = {false};
    
    int dst_0 = g.offsets[src];
    int dst_n = src == g.V-1 ? (g.E - g.offsets[src]) : (g.offsets[src+1] - g.offsets[src]);
    for (int dst_i = 0; dst_i < dst_n; dst_i += TILING) {
        int dst_m = std::min(dst_n-dst_i, TILING);

        for (int dst_j = 0; dst_j < dst_m; dst_j+=2) {            
            int d0 = g.neighbors[dst_0+dst_i+dst_j+0];
            int d1 = g.neighbors[dst_0+dst_i+dst_j+1];
            asm volatile ("" ::: "memory");
            float dw0 = g.weights[dst_0+dst_i+dst_j+0];
            float dw1 = g.weights[dst_0+dst_i+dst_j+1];
            asm volatile ("" ::: "memory");
            dst_v[dst_j+0] = d0;
            dst_v[dst_j+1] = d1;
            w_v[dst_j+0] = dw0+src_d;
            w_v[dst_j+1] = dw1+src_d;
        }

        for (int dst_j = 0; dst_j < dst_m; dst_j+=4) {
            int d0 = dst_v[dst_j+0];
            int d1 = dst_v[dst_j+1];
            int d2 = dst_v[dst_j+2];
            int d3 = dst_v[dst_j+3];            
            float dw0 = distance[d0];
            float dw1 = distance[d1];
            float dw2 = distance[d2];
            float dw3 = distance[d3];            
            distance_v[dst_j+0]=dw0;
            distance_v[dst_j+1]=dw1;
            distance_v[dst_j+2]=dw2;
            distance_v[dst_j+3]=dw3;            
        }

        for (int dst_j = 0; dst_j < dst_m; dst_j++) {
            if (w_v[dst_j] < distance_v[dst_j]) {
                distance[dst_v[dst_j]]=w_v[dst_j];
                path[dst_v[dst_j]]=src;
                push_v[dst_j] = true;
            }
        }

        for (int dst_j = 0; dst_j < dst_m; dst_j++) {
            if (push_v[dst_j])
                queue.push(dst_v[dst_j]);
        }
    }
}

extern "C" int dijkstra(struct graph *g_mem,
                        int root,
                        int goal,
                        float *distance,
                        int   *path,
                        int *queue_mem)
{
    struct graph g = *g_mem;    
    distance[root] = 0.0;
    path[root] = root;

#ifdef DEBUG_DIJKSTRA
    printf("g_mem=0x%08x, root=%4d, goal=%4d\n",
           reinterpret_cast<unsigned>(g_mem), root, goal);
#endif
#ifdef DEBUG_DIJKSTRA_ROOT_GOAL
    bsg_print_int(root);
    bsg_print_int(goal);
#endif
    auto cmp = [distance](int lhs, int rhs) {
        return distance[lhs] < distance[rhs];
    };

    bsg_cuda_print_stat_kernel_start();

    DynHeap<int, decltype(cmp)> queue(queue_mem, g.V, cmp);
    queue.push(root);

    while (!queue.empty()) {
        int best = queue.pop();
#ifdef DEBUG_DIJKSTRA_TRACE
        bsg_print_int(-best);
#endif        
        if (best == goal)
            break;

        float d_best = distance[best];
        visit_neighbors<8>(g, best, d_best, distance, path, queue);        
    }
    bsg_cuda_print_stat_kernel_end();

    return 0;
}
