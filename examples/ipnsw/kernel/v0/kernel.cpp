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
#include <string.h>
#include <queue>
//#include <hello_world.hpp>
#include "inner_product.hpp"
//#include "inner_product.h"

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling
 */

//#define V  1000000
#define VSIZE 100
#define NG 4
#define V_ENTRY 82026

#define G_0 3
#define G_1 2
#define G_2 1
#define G_3 0

struct graph {
    const int *offsets;
    const int *neighbors;
    int V;
    int E;
};

#ifdef __cplusplus
extern "C" {
#endif

    int input_test(const graph *Gs, const float *database, const float *query, int *seen)
    {
        bsg_printf("Gs = %08x\n",       Gs);
        bsg_printf("database = %08x\n", database);
        bsg_printf("query = %08x\n",    query);
        bsg_printf("seen  = %08x\n",    seen);

        struct graph G;
        int v_i [] = {G_0, G_1, G_2, G_3};
        for (int j = 0; j < 4; ++j) {
            int i = v_i[j];
            memcpy(&G, &Gs[i], sizeof(G));
            bsg_printf("G[%d].offsets   = %08x\n", j, G.offsets);
            bsg_printf("G[%d].neighbors = %08x\n", j, G.neighbors);
            bsg_printf("G[%d].V = %d\n", j, G.V);
            bsg_printf("G[%d].E = %d\n", j, G.E);
        }

        //int degree = G0.offsets[V_ENTRY+1]-G0.offsets[V_ENTRY];
        //bsg_printf("degree(%d) in G0=%d\n", V_ENTRY, degree);
        return 0;
    }

// Uncomment to turn on debugging
//#define DEBUG_GREEDY_VCURR_TR
//#define DEBUG_GREEDY_VIS_TR

    int ipnsw_greedy_search (const graph *Gs, const float *database, const float *query, int *seen)
    {
        float q[VSIZE];
        memcpy(q, query, sizeof(q));

        int   v_curr = V_ENTRY;
        float d_curr = 0;

        d_curr = -1 * inner_product<BSG_TILE_GROUP_X_DIM, BSG_TILE_GROUP_Y_DIM>(q, &database[v_curr*VSIZE]);

#if defined(DEBUG_GREEDY_VCURR_TR) || defined(DEBUG_GREEDY_VIS_TR)
        bsg_print_int(v_curr);
        bsg_print_float(d_curr);
#endif

        for (int i = 0; i < NG-1; i++) {
            struct graph G = Gs[i];
            bool changed = true;
            while (changed) {
                changed = false;
                // fetch neighbors
                int dst_0 = G.offsets[v_curr];
                int degree = v_curr == G.V-1 ? G.E - dst_0 : G.offsets[v_curr+1] - dst_0;
                for (int dst_i = 0; dst_i < degree; dst_i++) {
                    int dst = G.neighbors[dst_0+dst_i];
                    // calc. iproduct
                    float d = -1 * inner_product<BSG_TILE_GROUP_X_DIM,BSG_TILE_GROUP_Y_DIM>(q, &database[dst*VSIZE]);

#if defined(DEBUG_GREEDY_VIS_TR)
                    bsg_print_int(dst);
                    bsg_print_float(d);
#endif

                    if (d < d_curr) {
                        d_curr = d;
                        v_curr = dst;
                        changed = true;

#if defined(DEBUG_GREEDY_VIS_TR)
                        bsg_print_int(v_curr);
                        bsg_print_float(d_curr);
#endif
                    }
                }
            }
        }
        *seen = v_curr;
        return 0;
    }

    int ipnsw_beam_search(int arg)
    {
        return 0;
    }

    //DECL_inner_product(1, 1, float, 100, 10)

    int inner_product_ubmk(const float *database, const float *query)
    {
        const int N = 1;
        float q[VSIZE];
        float r = 0;

        memcpy(q, query, sizeof(q));

        bsg_cuda_print_stat_start(0);
        // perform a random inner product N times
        for (int i = 0; i < N; ++i) {
            const float *b = &database[i*2*VSIZE];
            r += inner_product<BSG_TILE_GROUP_X_DIM, BSG_TILE_GROUP_Y_DIM>(q,b);
            //r += inner_product_1_1(q, b);
        }
        bsg_cuda_print_stat_end(0);
        return (int)(r);
    }
#ifdef __cplusplus
}
#endif
