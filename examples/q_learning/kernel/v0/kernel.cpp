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


#define ALPHA 0.25

/* 
 * Version 0 
 */
template <typename T>
int  __attribute__ ((noinline)) q_learning (T* feature,
                                            T* value,
                                            uint32_t HEIGHT,
                                            uint32_t WIDTH,
                                            T* weight) {
                                            

        //TileGroupStripedArray<T, WIDTH, bsg_tiles_X, bsg_tiles_Y, 1> sh_val;
        bsg_tile_group_shared_mem(float, sh_val, WIDTH);

        const int num_tiles = bsg_tiles_X * bsg_tiles_Y;

        // Treat every row of the feature matrix as a new feature observation
        // With the corresponding value of value[y]
        // For every new feature observation, the prediction value is calculated
        // by performing a dot product of the row y of the feature matrix, and 
        // the weight vector. 
        // Each tile performes its share of the dot product and stores it in 
        // a shared array 
        // A sum reduction is performed among the values in the shared array to 
        // calcualte the value of the prediction
        // The error is calculated as the difference between the prediction and 
        // the actual value. 
        // Each weight in the weight vector is then updated as below:
        // weight[x] += ALPHA * error * feature[y][x]
        // The process repeats for all rows in the feature matrix 
        for (int y = 0; y < HEIGHT; y ++) {

                // Perform dot product between row y of the feature matrix and 
                // the weight vector and store the multiplication result into
                // tile group shared value array
                for (int x = __bsg_id; x < WIDTH; x += num_tiles) {
                        //sh_val[x] = feature[y * WIDTH + x] * weight[x];
                        bsg_tile_group_shared_store (float, sh_val, x, (feature[y * WIDTH + x] * weight[x]));
                }

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                //reduce(sh_val, WIDTH);


                // This while loop reduces all the elements in the shared value 
                // vector to the first element. For more details on how the reduction 
                // works, refer to the reduction example.
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



                // Update the weight vector
                //float err = value[y] - sh_val[0];
                float lc_val;
                bsg_tile_group_shared_load (float, sh_val, 0, lc_val);
                float err = value[y] - lc_val;

                for (int x = __bsg_id; x < WIDTH; x += num_tiles) {
                        weight[x] += ALPHA * err * feature[y * WIDTH + x];
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
                                 weight);

                bsg_cuda_print_stat_end(0);

                //barrier.sync();
                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
