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

#include "conv1d.hpp"

#define C_F_LENGTH 4
#define C_A_LENGTH 128
#define C_PAD_LENGTH 8
#define C_STEP_LENGTH 2

// Compute the sum of squared error between matricies A and B (M x N)
template <typename T>
double matrix_sse (const T *A, const T *B, uint64_t M, uint64_t N) {
        double sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        T diff = A[y * N + x] - B[y * N + x];
                        sum += diff * diff;
                }
        }
        return sum;
}

uint32_t compute_M(uint32_t N, uint32_t F, uint32_t P, uint32_t S)
{
        return 1 + (N - F + 2 * P) / S;
}

template <typename TA, typename TF, typename TB>
void conv1d(const TA *A, const uint32_t A_LENGTH,
            const TF *F, const uint32_t F_LENGTH,
            const uint32_t PAD_LENGTH, 
            const uint32_t S_LENGTH, 
            TB *B){

        uint32_t M = compute_M(A_LENGTH, F_LENGTH, PAD_LENGTH, S_LENGTH);
        for(uint32_t i = 0; i < M; i++)
        {
                uint32_t window_idx = i * S_LENGTH;
                TB res = 0;
                for(uint32_t j = 0; j < F_LENGTH; j++)
                {
                        uint32_t a_idx = window_idx - PAD_LENGTH + j;
                        float a = 0;
                        if(0 <= a_idx && a_idx < A_LENGTH)
                                a = A[a_idx];

                        res += F[j] * a;
                }
                B[i] = res;
        }
}

int kernel_conv1d(int argc, char **argv)
{       
        bsg_pr_test_info("Running CUDA Conv1D Kernel on a 2x2 tile group.\n\n");
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
        std::numeric_limits<int8_t> lim_int8; // Used to get INT_MIN and INT_MAX in C++
        std::numeric_limits<uint32_t> lim_uint32; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_real_distribution<float> data_distribution(lim_int8.min(),lim_int8.max());
        std::uniform_real_distribution<float> filter_distribution(lim_int8.min(),lim_int8.max());
        
        // N: Number of elements in the 1-D input vector, A
        uint32_t N = C_A_LENGTH;
        // F: Number of filter coefficients in 1-D filter, F
        uint32_t F = C_F_LENGTH;
        // P: Padding (symmetric, number of elements on both side of the input)
        uint32_t P = C_PAD_LENGTH;
        // S: Step size of convolution
        uint32_t S = C_STEP_LENGTH;
        uint32_t M = compute_M(N, F, P, S);
        
        size_t A_size = sizeof(float) * N;
        size_t F_size = sizeof(float) * F;
        size_t B_size = sizeof(float) * M;
        
        float A_host[N];
        float filter_host[F];
        float B_expected[M], B_result[M];

        eva_t A_device, B_device, filter_device;
        rc = hb_mc_device_malloc(mc, A_size, &A_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate A on the manycore.\n");
                return rc;
        }

        rc = hb_mc_device_malloc(mc, F_size, &filter_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate F on the manycore.\n");
                return rc;
        }
        
        rc = hb_mc_device_malloc(mc, B_size, &B_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate B on the manycore.\n");
                return rc;
        }

        for(int i = 0; i < sizeof(A_host) / sizeof(A_host[0]); i++)
        {
                A_host[i] = data_distribution(generator);
                bsg_pr_test_info("A_host[%d] = %.9f \n",
                                 i, A_host[i]);
        }

        for(int i = 0; i < sizeof(filter_host) / sizeof(filter_host[0]); i++)
        {
                filter_host[i] = filter_distribution(generator);
                bsg_pr_test_info("filter_host[%d] = %.9f \n",
                                 i, filter_host[i]);
        }
        
        rc = hb_mc_device_memcpy(mc, 
                                 (void *) ((intptr_t) A_device),
                                 (void *) &A_host[0],
                                 A_size, HB_MC_MEMCPY_TO_DEVICE);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to copy A to the manycore.\n");
                return rc;
        }
        
        rc = hb_mc_device_memcpy(mc, (void *) ((intptr_t) filter_device), 
                                 (void *) &filter_host[0], 
                                 F_size, HB_MC_MEMCPY_TO_DEVICE);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to copy F to the manycore.\n");
                return rc;
        }

        uint32_t block_size = M;

        hb_mc_dimension_t tilegroup_dim = { .x = 2, .y = 2 };
        hb_mc_dimension_t grid_dim = { .x = 1, .y = 1 };

        uint32_t cuda_argv[] = { A_device, N, filter_device, F, P, B_device, S, block_size };
        size_t cuda_argc = sizeof(cuda_argv) / sizeof(cuda_argv[0]);
        rc = hb_mc_kernel_enqueue(mc, grid_dim, tilegroup_dim, "kernel_conv1d", cuda_argc, cuda_argv);
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
                                 B_size, HB_MC_MEMCPY_TO_HOST);
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

        conv1d(A_host, N, filter_host, F, P, S, B_expected);

        float sse;
        bsg_pr_test_info("(N, F, P, S, M) = (%d, %d, %d, %d, %d)\n", N, F, P, S, M);
        sse = matrix_sse(B_expected, B_result, 1, M);

        if(sse < .01)
        {
                bsg_pr_test_info(BSG_GREEN("Vectors match! (SSE: %f)\n"), sse);
                return HB_MC_SUCCESS;
        }
        bsg_pr_test_err(BSG_RED("Vectors don't match!\n"));
        return HB_MC_FAIL;
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
        int rc = kernel_conv1d(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char **argv)
{
        int rc = kernel_conv1d(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

