// Copyright (c) 2019, University of Washington All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this list
// of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice, this
// list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// Neither the name of the copyright holder nor the names of its contributors may
// be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "q_learning.hpp"


/***********************************************************************************/
/* This example runs the Q-learning algorithm. The goal in this problem is to      */ 
/* predict the state value based on a feature list. The state value is calculated  */
/* by performing a dot product between the feature vector and the weight vector.   */
/*                                                                                 */
/* Training is done on a list of feature vectors and corresponding state values.   */
/* At every step, the error is calculated as the difference between prediction and */
/* the given state value. Then, the list of weights are updated based on the given */
/* error in the following way:                                                     */
/*                                                                                 */
/* Error = Sum(W[i] . F[i]) - V                                                    */
/* W_new[i] = W[i] + alpha . error . feature [i]                                   */
/*                                                                                 */
/* Input is a feature matrix and a value vector. Each row i in the feature matrix  */
/* is a feature vector, and the i-th element in the value vector is its            */
/* corresponding value. Feature vectors are in-order observations of the algorithm.*/
/* Output is a weight vector with the same dimension of the feature matrix width.  */
/***********************************************************************************/



// Feature vector width (WDITH) and number of feature vectors (HEIGHT)
#define HEIGHT 8
#define WIDTH  8





// Compute the sum of squared error between vectors A and B (N)
template <typename T>
double vector_sse (const T *A, const T *B, uint64_t N) {
        double sum = 0;
        for (uint64_t x = 0; x < N; x ++) {
                T diff = A[x] - B[x];
                if(std::isnan(diff)){
                        return diff;
                }
                sum += diff * diff;
        }
        return sum;
}

// Print vector A (N). This works well for small vectors.
template <typename T>
void vector_print(T *A, uint64_t N) {
        T sum = 0;
        for (uint64_t x = 0; x < N; x ++) {
                std::cout << A[x] << " ";
        }
        std::cout << '\n';
}

// Host side gaussian elimination
template <typename T>
void host_q_learning (T* feature,
                      T* value,
                      uint64_t M,
                      uint64_t N,
                      T* weight) {

        return;
}




int kernel_q_learning (int argc, char **argv) {

        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running Q-Learning Kernel.\n\n");

        // Define block_size: amount of work for each tile group
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size
        uint32_t block_size = 0;
        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        hb_mc_dimension_t grid_dim = { .x = 0, .y = 0 };



        if(!strcmp("v0", test_name)) {

                block_size = WIDTH;
                tg_dim = { .x = 4, .y = 4 };
                grid_dim = { .x = 1,
                             .y = 1 };

        } else {
                bsg_pr_test_err("Invalid version provided!.\n");
                return HB_MC_INVALID;
        }


        // Initialize the random number generators
        std::numeric_limits<int8_t> lim; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        // Random numbers are RGB, so the values are limited to [0,255]
        //std::uniform_real_distribution<float> distribution(lim.min(),lim.max());
        std::uniform_real_distribution<float> distribution(0, 255);

        // Allocate feature matrix, value vector and weight vector  on the host
        float feature_host[HEIGHT * WIDTH];
        float value_host[HEIGHT];
        float weight_host[WIDTH];
        float weight_from_host[WIDTH];
        float weight_from_device[WIDTH];        


        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        // Fill feature matrix with random values
        for (uint64_t i = 0; i < HEIGHT * WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                feature_host[i] = static_cast<float>(res);
        }

        // Fill value vector with random values
        for (uint64_t i = 0; i < HEIGHT; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                value_host[i] = static_cast<float>(res);
        }

        // Set weight vectors to zero
        for (uint64_t i = 0; i < WIDTH; i++) {
                weight_host[i] = 0;
                weight_from_host[i] = 0;
                weight_from_device[i] = 0;
        }



        // Generate the known-correct results on the host
        host_q_learning (feature_host,
                         value_host,
                         HEIGHT,
                         WIDTH,
                         weight_from_host);



        // Initialize device, load binary and unfreeze tiles.
        hb_mc_device_t device;
        rc = hb_mc_device_init(&device, test_name, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize device.\n");
                return rc;
        }


        rc = hb_mc_device_program_init(&device, bin_path,
                                       "default_allocator", 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize program.\n");
                return rc;
        }


        // Allocate memory on the device for the feature matrix, value vector
        // and weight vectos.
        // Since sizeof(float) == sizeof(int32_t) > 
        // sizeof(int16_t) > sizeof(int8_t) we'll reuse the same buffers for 
        // each test (if multiple tests are conducted)
        hb_mc_eva_t feature_device,
                    value_device,
                    weight_device;


        // Allocate feature matrix on the device
        rc = hb_mc_device_malloc(&device, HEIGHT * WIDTH * sizeof(float), &feature_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate value vector on the device
        rc = hb_mc_device_malloc(&device, HEIGHT * sizeof(float), &value_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate weight vector on the device
        rc = hb_mc_device_malloc(&device, WIDTH * sizeof(float), &weight_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }


        // Copy feature matrix from the host to the device
        void *dst = (void *) ((intptr_t) feature_device);
        void *src = (void *) &feature_host[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (HEIGHT * WIDTH) * sizeof(feature_host[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        // Copy value vector from the host to the device
        dst = (void *) ((intptr_t) value_device);
        src = (void *) &value_host[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (HEIGHT) * sizeof(value_host[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        // Copy weight vector from the host to the device
        dst = (void *) ((intptr_t) weight_device);
        src = (void *) &weight_host[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (WIDTH) * sizeof(weight_host[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }



        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[5] = {feature_device, value_device, HEIGHT, WIDTH, weight_device};


        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_q_learning", 5, cuda_argv);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize grid.\n");
                return rc;
        }

        // Launch and execute all tile groups on device and wait for all to finish.
        rc = hb_mc_device_tile_groups_execute(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to execute tile groups.\n");
                return rc;
        }

        // Copy weight result back from device DRAM into host memory.
        src = (void *) ((intptr_t) weight_device);
        dst = (void *) &weight_from_device[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  WIDTH * sizeof(float),
                                  HB_MC_MEMCPY_TO_HOST);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory from device.\n");
                return rc;
        }

        // Freeze the tiles and memory manager cleanup.
        rc = hb_mc_device_finish(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to de-initialize device.\n");
                return rc;
        }

        // Print result 
        vector_print(weight_from_host, WIDTH);
        vector_print(weight_from_device, WIDTH);


        // Compare the known-correct result (result_from_host) 
        // and the result copied from device (result_from_device);
        float max = 0.1;
        double sse = vector_sse(weight_from_host, weight_from_device, WIDTH);

        bsg_pr_test_info ("SSE: %f\n", sse);

        if (std::isnan(sse) || sse > max) {
                bsg_pr_test_info(BSG_RED("Vector Mismatch. SSE: %f\n"), sse);
                return HB_MC_FAIL;
        }


        bsg_pr_test_info(BSG_GREEN("Vector Match.\n"));
        return HB_MC_SUCCESS;
}

#ifdef COSIM
void cosim_main(uint32_t *exit_code, char * args) {
        // We aren't passed command line arguments directly so we parse them
        // from *args. args is a string from VCS - to pass a string of arguments
        // to args, pass c_args to VCS as follows: +c_args="<space separated
        // list of args>"
        int argc = get_argc(args);
        char *argv[argc];
        get_argv(args, argc, argv);

#ifdef VCS
        svScope scope;
        scope = svGetScopeFromName("tb");
        svSetScope(scope);
#endif
        int rc = kernel_q_learning(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_q_learning(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

