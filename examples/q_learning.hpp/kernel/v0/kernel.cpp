/*
 * This example runs the Q-learning algorithm. The goal in this problem is to 
 * predict the state value based on a feature list. The state value is calculated 
 * by performing a dot product between the feature vector and the weight vector. 
 * 
 * Training is done on a list of feature vectors and corresponding state values.
 * At every step, the error is calculated as the difference between prediction and 
 * the given state value. Then, the list of weights are updated based on the given 
 * error in the following way:
 * 
 * Error = Sum(W[i] . F[i]) - V
 * W_new[i] = W[i] + alpha . error . feature [i]
 */



// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <cstdint>

#include <q_learning.hpp>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


/* 
 * Version 0 
 */
template <typename T>
int  __attribute__ ((noinline)) q_learning (T* feature,
                                            T* value,
                                            uint32_t HEIGHT,
                                            uint32_t WIDTH,
                                            T* weight) {
                                            


        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_q_learning (float* feature,
                                                           float* value,
                                                           uint32_t HEIGHT,
                                                           uint32_t WIDTH,
                                                           float* weight) {
                //bsg_barrier <bsg_tiles_Y, bsg_tiles_X> barrier;

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = q_learning (feature,
                                 value,
                                 HEIGHT,
                                 WIDTH,
                                 weight); 

                bsg_cuda_print_stat_end(0);

                //barrier.sync();
                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
