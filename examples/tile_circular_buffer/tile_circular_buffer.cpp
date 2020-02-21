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

#include "tile_circular_buffer.hpp"
#include <iostream>

#define C_LENGTH 256

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

int kernel_circular_buffer(int argc, char **argv)
{       
        bsg_pr_test_info("Running CUDA Circular_Buffer Kernel on a 1x1 tile group.\n\n");
        char *elf, *test_name;
        struct arguments_path args = { NULL, NULL };
        argp_parse(&argp_path, argc, argv, 0, 0, &args);
        elf = args.path;
        test_name = args.name;

        int rc;
        hb_mc_device_t manycore, *mc = &manycore;
        rc = hb_mc_device_init(mc, test_name, 0);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to initialize device.\n");
                return rc;
        }

        rc = hb_mc_device_program_init(mc, elf, "default_allocator", 0);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to initialize the program.\n");
                return rc;
        }

        // Initialize the random number generators
        std::numeric_limits<int32_t> lim_int32; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_int_distribution<int> data_distribution(lim_int32.min(),lim_int32.max());

        // N: Number of elements in the 1-D input vector
        uint32_t N = C_LENGTH;
        
        int A[N];
        int B[N], B_result[N];

        eva_t A_device, B_device;
        rc = hb_mc_device_malloc(mc, sizeof(A), &A_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate A on the manycore.\n");
                return rc;
        }
        
        rc = hb_mc_device_malloc(mc, sizeof(B), &B_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate B on the manycore.\n");
                return rc;
        }

        for(int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
        {
                A[i] = data_distribution(generator);
                B[i] = A[i];
        }
        
        rc = hb_mc_device_memcpy(mc,
                                 (void *) ((intptr_t) A_device),
                                 (void *) &A[0],
                                 sizeof(A), HB_MC_MEMCPY_TO_DEVICE);

        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to copy A to the manycore.\n");
                return rc;
        }
        

        hb_mc_dimension_t tilegroup_dim = { .x = 2, .y = 1 };
        hb_mc_dimension_t grid_dim = { .x = 1, .y = 1 };

        uint32_t cuda_argv[] = {A_device, N, B_device};
        size_t cuda_argc = sizeof(cuda_argv) / sizeof(cuda_argv[0]);
        rc = hb_mc_kernel_enqueue(mc, grid_dim, tilegroup_dim, 
                                  "kernel_tile_circular_buffer", 
                                  cuda_argc, cuda_argv);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to initialize grid.\n");
                return rc;
        }

        rc = hb_mc_device_tile_groups_execute(mc);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to execute tilegroups.\n");
                return rc;
        }

        rc = hb_mc_device_memcpy(mc, (void *) B_result,
                                 (void *) ((intptr_t) B_device),
                                 sizeof(B), HB_MC_MEMCPY_TO_HOST);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to copy result to host.\n");
                return rc;
        }

        rc = hb_mc_device_finish(mc);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to deinitialize the manycore.\n");
                return rc;
        }

        float sse;
        sse = matrix_sse(B, B_result, 1, N);

        if(std::isnan(sse) || sse > .01)
        {
                bsg_pr_test_err(BSG_RED("Result mismatch! SSE: %f\n"), sse);
                return HB_MC_FAIL;
        }
        bsg_pr_test_info(BSG_GREEN("Result match! (SSE: %f)\n"), sse);
        return HB_MC_SUCCESS;
}

#ifdef COSIM
void cosim_main(uint32_t *exit_code, char *args)
{
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
        int rc = kernel_circular_buffer(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char **argv)
{
        int rc = kernel_circular_buffer(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

