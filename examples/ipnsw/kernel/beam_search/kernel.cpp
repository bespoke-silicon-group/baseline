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
#include <algorithm>
#include <array>
//#include <hello_world.hpp>
#include "inner_product.hpp"
#include "heap.hpp"
//#include "inner_product.h"

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling
 */

//#define V  1000000
#define VSIZE 100
#define NG 4
#define V_ENTRY 82026

#define EF        128
#define N_RESULTS 10

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

//#define DEBUG_INPUT_TEST

    int input_test(const graph *Gs, const float *database, const float *query, int *seen)
    {
#if defined(DEBUG_INPUT_TEST)
        bsg_printf("Gs = %08x\n",       Gs);
        bsg_printf("database = %08x\n", database);
        bsg_printf("query = %08x\n",    query);
        bsg_printf("seen  = %08x\n",    seen);
#endif // #if defined(DEBUG_INPUT_TEST)

        struct graph G;
        int v_i [] = {G_0, G_1, G_2, G_3};
        for (int j = 0; j < 4; ++j) {
            int i = v_i[j];
            memcpy(&G, &Gs[i], sizeof(G));
#if defined(DEBUG_INPUT_TEST)
            bsg_printf("G[%d].offsets   = %08x\n", j, G.offsets);
            bsg_printf("G[%d].neighbors = %08x\n", j, G.neighbors);
            bsg_printf("G[%d].V = %d\n", j, G.V);
            bsg_printf("G[%d].E = %d\n", j, G.E);
#endif // #if defined(DEBUG_INPUT_TEST)
        }

        return 0;
    }

// Uncomment to turn on debugging
//#define DEBUG_GREEDY_VCURR_TR
//#define DEBUG_GREEDY_VIS_TR

#define distance(v0, v1)                                                \
    (-1 * inner_product<BSG_TILE_GROUP_X_DIM, BSG_TILE_GROUP_Y_DIM>(v0, v1))


    int ipnsw_beam_search(const graph *Gs, const float *database, const float *query, int *seen,
                          int *v_curr_o, float *d_curr_o,
                          std::pair<float, int> *candidates,
                          std::pair<float, int> *results)
    {
        struct graph G = Gs[G_0];
        float q[VSIZE];
        memcpy(q, query, sizeof(q));

        int v_curr   = *v_curr_o;
        float d_curr = *d_curr_o;
        bsg_print_int(v_curr);
        bsg_print_float(d_curr);

        using result_t = std::pair<int, float>;

        int n_candidates = 0;
        std::array<result_t, EF> candidates;
        candidates[n_candidates++] = {d_curr, v_curr};

        int n_results = 0;
        std::array<result_t, EF> results;
        results[n_results++] = {-d_curr, v_curr};

        return 0;
    }

#ifdef __cplusplus
}
#endif
