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

#include "gaussian_elimination.hpp"


/********************************************************************************/
/* Runs the gaussian elimination on an input MxN matrix.                        */
/* Input matrix represents a set of coefficients for an N-dimension linear      */
/* equation. The purpose of this kernel is to transform the input matrix into   */
/* a matrix where the triangle portion of the matrix below the diameter is zero.*/
/* Because of the nature of the application and the need for synchronization    */
/* among threads, the entire operation has to be done within one tile group.    */
/* Therefore, a single tile group has to handle the entire matrix, and the block*/
/* size (a tile group's workload) is set to the matrix height.                  */
/* Result is an MxN matrix.                                                     */
/********************************************************************************/



// Matirx dimensions
#define MATRIX_HEIGHT 8 
#define MATRIX_WIDTH 8





// Compute the sum of squared error between matricies A and B (M x N)
template <typename T>
double matrix_sse (const T *A, const T *B, uint64_t M, uint64_t N) {
        double sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        T diff = A[y * N + x] - B[y * N + x];
                        if(std::isnan(diff)){
                                return diff;
                        }
                        sum += diff * diff;
                }
        }
        return sum;
}

// Print matrix A (M x N). This works well for small matricies.
template <typename T>
void matrix_print(T *A, uint64_t M, uint64_t N) {
        T sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        std::cout << A[y * N + x] << " ";
                }
                std::cout << '\n';

        }
}

// Host side gaussian elimination
template <typename T>
void host_gaussian_elimination (T* A,
                                uint32_t M,
                                uint32_t N) {


        for (int y_src = 0; y_src < M; y_src ++) {
                for (int y_dst = y_src + 1; y_dst < M; y_dst ++) {
                        // Coefficient = A[y_dst][y_src] / A[y_src][y_src]
                        float c = A[y_dst * N + y_src] / A[y_src * N + y_src];
                        for (int x = 0; x < N; x ++) {
                                // A [y_dst][x] -= c * A[y_src][x]       
                                A[y_dst * N + x] -= c * A[y_src * N + x];
                        }
                }
        }
        return;
}




int kernel_gaussian_elimination (int argc, char **argv) {

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

                block_size = MATRIX_HEIGHT;
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

        // Allocate dense vectors on the host
        float A_host[MATRIX_HEIGHT * MATRIX_WIDTH];
        float A_from_host[MATRIX_HEIGHT * MATRIX_WIDTH];
        float A_from_device[MATRIX_HEIGHT * MATRIX_WIDTH];

        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        // Fill A with non-zero values
        for (uint64_t i = 0; i < MATRIX_HEIGHT * MATRIX_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res)     ||
                       !res);

                A_host[i] = static_cast<float>(res);
                A_from_host[i] = static_cast<float>(res);
        }



        // Generate the known-correct results on the host
        host_gaussian_elimination (A_from_host,
                                   MATRIX_HEIGHT,
                                   MATRIX_WIDTH);



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


        // Allocate memory on the device for the matrix.
        // Since sizeof(float) == sizeof(int32_t) > 
        // sizeof(int16_t) > sizeof(int8_t) we'll reuse the same buffers for 
        // each test (if multiple tests are conducted)
        hb_mc_eva_t A_device; 


        // Allocate A on the device
        rc = hb_mc_device_malloc(&device, MATRIX_HEIGHT * MATRIX_WIDTH * sizeof(float), &A_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }



        // Copy A from the host to the device
        void *dst = (void *) ((intptr_t) A_device);
        void *src = (void *) &A_host[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (MATRIX_HEIGHT * MATRIX_WIDTH) * sizeof(A_host[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }



        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[3] = {A_device, MATRIX_HEIGHT, MATRIX_WIDTH};


        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_gaussian_elimination", 3, cuda_argv);
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
        src = (void *) ((intptr_t) A_device);
        dst = (void *) &A_from_device[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  MATRIX_HEIGHT * MATRIX_WIDTH * sizeof(float),
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
        matrix_print(A_from_host, MATRIX_HEIGHT, MATRIX_WIDTH);
        matrix_print(A_from_device, MATRIX_HEIGHT, MATRIX_WIDTH);


        // Compare the known-correct result (result_from_host) 
        // and the result copied from device (result_from_device);
        float max = 0.1;
        double sse = matrix_sse(A_from_host, A_from_device, MATRIX_HEIGHT, MATRIX_WIDTH);

        bsg_pr_test_info ("SSE: %f\n", sse);

        if (std::isnan(sse) || sse > max) {
                bsg_pr_test_info(BSG_RED("Matrix Mismatch. SSE: %f\n"), sse);
                return HB_MC_FAIL;
        }


        bsg_pr_test_info(BSG_GREEN("Matrix Match.\n"));
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
        int rc = kernel_gaussian_elimination(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_gaussian_elimination(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

