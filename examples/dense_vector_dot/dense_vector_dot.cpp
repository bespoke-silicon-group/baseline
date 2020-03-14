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

#include "dense_vector_dot.hpp"


/******************************************************************************/
/* Runs the dense vector vector dot product kernel.                           */
/* Result is a single number.                                                 */
/******************************************************************************/



// Dense vector sizes
#define A_WIDTH 16
#define B_WIDTH 8





// Print vector V (N). This works well for small vectors
template <typename T>
void vector_print(T *A, uint64_t N) {
        T sum = 0;
        for (uint64_t x = 0; x < N; x ++) {
                std::cout << A[x] << " ";
        }
        std::cout << '\n';
}


// Compute the sum of squared error between two single numbers
template <typename T>
double single_sse (const T *A, const T *B) {
        double diff = *A - *B;
        if(std::isnan(diff)) {
                return diff;
        }
        return diff * diff;
}


// Host side dense vector vector dot product calculation
template <typename TA, typename TB, typename TR>
void host_dense_vector_dot (int* dense_A_index,
                            TA*  dense_A_data,
                            uint32_t A_width,
                            int* dense_B_index,
                            TB*  dense_B_data,
                            uint32_t B_width,
                            TR* result) {

        return;
}




int kernel_dense_vector_dot (int argc, char **argv) {

        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running Sparse Matrix Dense Vector Multiplication Kernel.\n\n");

        // Define block_size: amount of work for each tile group
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size
        uint32_t block_size = 0;
        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        hb_mc_dimension_t grid_dim = { .x = 0, .y = 0 };



        if(!strcmp("v0", test_name)) {

                block_size = 64;
                tg_dim = { .x = 1, .y = 1 };
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

        // Allocate dense vectors on the host
        int dense_A_index [A_WIDTH];
        int dense_A_data [A_WIDTH];
        int dense_B_index [B_WIDTH];
        int dense_B_data [B_WIDTH];
        int result_from_host;
        int result_from_device;

        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        // Fill dense A values
        for (uint64_t i = 0; i < A_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                dense_A_data[i] = static_cast<int>(res);
        }

        // Fill dense A indices
        for (uint64_t i = 0; i < A_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                dense_A_index[i] = (static_cast<int>(res)) % A_WIDTH;
        }

        // Fill dense B values
        for (uint64_t i = 0; i < B_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                dense_B_data[i] = static_cast<int>(res);
        }

        // Fill dense B indices
        for (uint64_t i = 0; i < B_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                dense_B_index[i] = (static_cast<int>(res)) % B_WIDTH;
        }



        // Generate the known-correct results on the host
        host_dense_vector_dot (dense_A_index,
                               dense_A_data,
                               A_WIDTH,
                               dense_B_index,
                               dense_B_data,
                               B_WIDTH,
                               &result_from_host);



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


        // Allocate memory on the device for sparse matrix, dense vector, and 
        // the sparse result vector. Since sizeof(float) == sizeof(int32_t) > 
        // sizeof(int16_t) > sizeof(int8_t) we'll reuse the same buffers for 
        // each test (if multiple tests are conducted)
        hb_mc_eva_t dense_A_index_device,
                    dense_A_data_device,
                    dense_B_index_device,
                    dense_B_data_device,
                    result_device;


        // Allocate Dense A indices vector on the device
        rc = hb_mc_device_malloc(&device, A_WIDTH * sizeof(float), &dense_A_index_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate Dense A data vector on the device
        rc = hb_mc_device_malloc(&device, A_WIDTH * sizeof(float), &dense_A_data_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate Dense B indices vector on the device
        rc = hb_mc_device_malloc(&device, B_WIDTH * sizeof(float), &dense_B_index_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate Dense B data vector on the device
        rc = hb_mc_device_malloc(&device, B_WIDTH * sizeof(float), &dense_B_data_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate result on the device
        rc = hb_mc_device_malloc(&device, 1 * sizeof(float), &result_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }




        // Copy sparse dense vector indices and data onto the device
        void *dst = (void *) ((intptr_t) dense_A_index_device);
        void *src = (void *) &dense_A_index[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (A_WIDTH) * sizeof(dense_A_index[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) dense_A_data_device);
        src = (void *) &dense_A_data[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (A_WIDTH) * sizeof(dense_A_data[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) dense_B_index_device);
        src = (void *) &dense_B_index[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (B_WIDTH) * sizeof(dense_B_index[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) dense_B_data_device);
        src = (void *) &dense_B_data[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (B_WIDTH) * sizeof(dense_B_data[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }




        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[7] = {dense_A_index_device,
                                 dense_A_data_device,
                                 A_WIDTH,
                                 dense_B_index_device,
                                 dense_B_data_device,
                                 B_WIDTH,
                                 result_device};


        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_dense_vector_dot", 7, cuda_argv);
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

        // Copy result back from device DRAM into host memory.
        src = (void *) ((intptr_t) result_device);
        dst = (void *) &result_from_device;
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  1 * sizeof(float),
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
        // vector_print(sparse_result_host, MATRIX_HEIGHT);
        // vector_print(sparse_result_device, MATRIX_HEIGHT);


        // Compare the known-correct result (result_from_host) 
        // and the result copied from device (result_from_device);
        float max = 0.1;
        double sse = single_sse(&result_from_host, &result_from_device);

        bsg_pr_test_info ("SSE: %f\n", sse);

        if (std::isnan(sse) || sse > max) {
                bsg_pr_test_info(BSG_RED("Product Mismatch. SSE: %f\n"), sse);
                return HB_MC_FAIL;
        }


        bsg_pr_test_info(BSG_GREEN("Product Match.\n"));
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
        int rc = kernel_dense_vector_dot(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_dense_vector_dot(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

