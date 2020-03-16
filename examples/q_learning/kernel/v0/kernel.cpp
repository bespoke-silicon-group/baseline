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
                                            T* weight,
                                            float alpha) {
                                            

        //TileGroupStripedArray<T, WIDTH, bsg_tiles_X, bsg_tiles_Y, 1> sh_val;
        bsg_tile_group_shared_mem(float, sh_val, WIDTH);

        const int num_tiles = bsg_tiles_X * bsg_tiles_Y;

        for (int y = 0; y < HEIGHT; y ++) {

                for (int x = __bsg_id; x < WIDTH; x += num_tiles) {
                        //sh_val[x] = feature[y * WIDTH + x] * weight[x];
                        bsg_tile_group_shared_store (float, sh_val, x, (feature[y * WIDTH + x] * weight[x]));
                }

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                //reduce(sh_val, WIDTH);


                /*************/
                /* REDUCTION */
                /*************/
                int offset = 1;
                int mult = 2;        
        
                while (offset < WIDTH) {
                        for (int x = bsg_id; x < WIDTH; x += num_tiles) {
                                if (!(x % mult)){
                                        float lc_A, lc_B;
        
                                        // lc_A <-- sh_val[x]
                                        bsg_tile_group_shared_load (float, sh_val, x, lc_A);
                                        // lc_B <-- sh_val[x + offset]
                                        bsg_tile_group_shared_load (float, sh_val, x + offset, lc_B);
        
                                        // sh_val[x] <-- lc_A + lc_B
                                        bsg_tile_group_shared_store (float, sh_val, x, lc_A + lc_B);
                                }
                        }
        
                        mult *= 2;
                        offset *= 2;

                        bsg_tile_group_barrier(&r_barrier, &c_barrier);
        	}


                bsg_tile_group_barrier(&r_barrier, &c_barrier);



                //float err = value[y] - sh_val[0];
                float lc_val;
                bsg_tile_group_shared_load (float, sh_val, 0, lc_val);
                float err = value[y] - lc_val;

                for (int x = __bsg_id; x < WIDTH; x += num_tiles) {
                        //weight[x] += alpha * err * feature[y * WIDTH + x];
                        weight[x] += 0.25 * err * feature[y * WIDTH + x];
                }

                bsg_tile_group_barrier(&r_barrier, &c_barrier);
        }


        bsg_tile_group_barrier(&r_barrier, &c_barrier);



        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_q_learning (float* feature,
                                                           float* value,
                                                           uint32_t HEIGHT,
                                                           uint32_t WIDTH,
                                                           float* weight,
                                                           float alpha) {
                //bsg_barrier <bsg_tiles_Y, bsg_tiles_X> barrier;

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = q_learning (feature,
                                 value,
                                 HEIGHT,
                                 WIDTH,
                                 weight,
                                 alpha); 

                bsg_cuda_print_stat_end(0);

                //barrier.sync();
                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
