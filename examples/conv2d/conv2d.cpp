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

#include "conv2d.hpp"
#include <array>

#define C_F_ROWS 4
#define C_F_COLS 4
#define C_A_ROWS 16
#define C_A_COLS 16
#define C_PAD 8
#define C_STEP_X 2
#define C_STEP_Y 2

// Compute the sum of squared error between matricies A and B (M x N)
template <typename T>
double matrix_sse (const T *A, const T *B, uint64_t M, uint64_t N) {
        double sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        T diff = A[y * M + x] - B[y * M + x];
                        sum += diff * diff;
                }
        }
        return sum;
}

constexpr uint32_t output_dim(uint32_t N, uint32_t F, uint32_t P, uint32_t S)
{
        return 1 + (N - F + 2 * P) / S;
}

// Takes an MxN matrix A and a FyxFx filter, a padding P,
// a vertical stride Sy and a horizontal Sx, and outputs
// the result of a 2D convolution into B. B must be of size
// output_dim(M, Fy, P, Sy) x output_dim(N, W, P, Sx)
template <typename TA, typename TF, typename TB>
void conv2d(const TA *A,
            const int M,
            const int N,
            const TF *filter,
            const int Fy,
            const int Fx,
            const int P,
            TB *B,
            const int Sy,
            const int Sx)
{
        int result_h = output_dim(M, Fy, P, Sy);
        int result_w = output_dim(N, Fx, P, Sx);
        for(int by = 0; by < result_h; by++)
                for(int bx = 0; bx < result_w; bx++)
                {
                        int window_y = by * Sy;
                        int window_x = bx * Sx;
                        
                        TB res = 0;
                        for(int fy = 0; fy < Fy; fy++)
                                for(int fx = 0; fx < Fx; fx++)
                                {
                                        int ay = window_y - P + fy;
                                        int ax = window_x - P + fx;
                                        TB a = 0;
                                        
                                        if((0 <= ay && ay < M) &&
                                           (0 <= ax && ax < N))
                                                a = A[ay * N + ax];
                                        res += static_cast<TB>(filter[fy * Fx + fx]) * static_cast<TB>(a);
                                 }
                        B[by * result_w + bx] = res;
                }
}


int kernel_conv2d(int argc, char **argv)
{       
        bsg_pr_test_info("Running CUDA Conv2D Kernel on a 2x2 tile group.\n\n");
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
        
        // N: Number of rows in the 2-D input matrix, A
        constexpr uint32_t N = C_A_ROWS;
        // M: Number of columns in the 2-D input matrix, A
        constexpr uint32_t M = C_A_COLS;
        // Fy: Number of rows in 2-D filter, F
        constexpr uint32_t Fy = C_F_ROWS;
        // Fx: Number of columns in 2-D filter, F
        constexpr uint32_t Fx = C_F_COLS;
        // P: Padding (symmetric, number of elements on both side of the input)
        constexpr uint32_t P = C_PAD;
        // Sx: Step size of convolution in horizontal direction
        constexpr uint32_t Sx = C_STEP_X;
        // Sy: Step size of convolution in vertical direction
        constexpr uint32_t Sy = C_STEP_Y;
        // By: Rows in output matrix B
        constexpr uint32_t By = output_dim(M, Fy, P, Sy);
        // Bx: Columns in output matrix B
        constexpr uint32_t Bx = output_dim(N, Fx, P, Sx);


        std::array<float, M * N> A_host;
        std::array<float, Fy * Fx> filter_host;
        std::array<float, By * Bx> B_expected, B_result;

        eva_t A_device, B_device, filter_device;
        rc = hb_mc_device_malloc(mc, sizeof(A_host), &A_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate A on the manycore.\n");
                return rc;
        }

        rc = hb_mc_device_malloc(mc, sizeof(filter_host), &filter_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate F on the manycore.\n");
                return rc;
        }
        
        rc = hb_mc_device_malloc(mc, sizeof(B_expected), &B_device);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to allocate B on the manycore.\n");
                return rc;
        }

        for(int i = 0; i < A_host.size(); i++)
        {
                A_host[i] = data_distribution(generator);
                bsg_pr_test_info("A_host[%d] = %.9f \n",
                                 i, A_host[i]);
        }

        for(int i = 0; i < filter_host.size(); i++)
        {
                filter_host[i] = filter_distribution(generator);
                bsg_pr_test_info("filter_host[%d] = %.9f \n",
                                 i, filter_host[i]);
        }
        
        rc = hb_mc_device_memcpy(mc, 
                                 reinterpret_cast<void *>(static_cast<intptr_t>(A_device)),
                                 reinterpret_cast<void *>(A_host.data()),
                                 sizeof(A_host), HB_MC_MEMCPY_TO_DEVICE);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to copy A to the manycore.\n");
                return rc;
        }
        
        rc = hb_mc_device_memcpy(mc, reinterpret_cast<void *>(static_cast<intptr_t>(filter_device)),
                                 reinterpret_cast<void *>(filter_host.data()),
                                 sizeof(filter_host), HB_MC_MEMCPY_TO_DEVICE);
        if(rc != HB_MC_SUCCESS)
        {
                bsg_pr_test_err("Failed to copy F to the manycore.\n");
                return rc;
        }

        uint32_t block_size_y = By;
        uint32_t block_size_x = Bx;

        hb_mc_dimension_t tilegroup_dim = { .x = 2, .y = 2 };
        hb_mc_dimension_t grid_dim = { .x = 1, .y = 1 };

        uint32_t cuda_argv[] = {
                A_device, M, N,
                filter_device, Fy, Fx,
                P,
                B_device,
                Sy, Sx,
                block_size_y, block_size_x
        };
        size_t cuda_argc = sizeof(cuda_argv) / sizeof(cuda_argv[0]);
        rc = hb_mc_kernel_enqueue(mc, grid_dim, tilegroup_dim, "kernel_conv2d", cuda_argc, cuda_argv);
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

        rc = hb_mc_device_memcpy(mc, reinterpret_cast<void *>(B_result.data()),
                                 reinterpret_cast<void *>(static_cast<intptr_t>(B_device)),
                                 sizeof(B_result), HB_MC_MEMCPY_TO_HOST);
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

        conv2d(A_host.data(), M, N,
               filter_host.data(), Fy, Fx,
               P,
               B_expected.data(),
               Sy, Sx);

        float sse;
        sse = matrix_sse(B_expected.data(), B_result.data(), By, Bx);

        if(sse < .01)
        {
                bsg_pr_test_info(BSG_GREEN("Vectors match! (SSE: %f)\n"), sse);
                return HB_MC_SUCCESS;
        }
        bsg_pr_test_err(BSG_RED("Vectors don't match! (SSE: %f)\n\n"), sse);
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
        int rc = kernel_conv2d(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char **argv)
{
        int rc = kernel_conv2d(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

