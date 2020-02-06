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

#include "group_matrix_matrix_multiply.hpp"

/*
 * Runs the matrix multiplication on a grid of tile groups. A[M][N] * B[N][P] --> C[M][P]
 * Grid dimensions are determined by how much of a load we want for each tile group (block_size_y/x)
 */

// Matrix sizes:
#define A_HEIGHT 32
#define A_WIDTH  64
#define B_HEIGHT A_WIDTH
#define B_WIDTH  16
#define C_HEIGHT A_HEIGHT
#define C_WIDTH  B_WIDTH
#define NUM_ITER 4

// Host Matrix multiplication code (to compare results)
template <typename TA, typename TB, typename TC>
void matrix_mult (TA *A, TB *B, TC *C, uint64_t M, uint64_t N, uint64_t P) {
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < P; x ++) {
                        TC res = 0.0f;
                        for (uint64_t k = 0; k < N; k++) {
                                res += A[y * N + k] * B[k * P + x];
                        }
                        C[y * P + x] = res;
                }
        }
        return;
}

// Compute the sum of squared error between matricies A and B (M x N)
template <typename T>
double matrix_sse (const T *A, const T *B, uint64_t M, uint64_t N) {
        double sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        T diff = A[y * N + x] - B[y * N + x];
                        printf("%d %d %f %f %f\n",y, x, A[y * N + x], B[y * N + x], diff);
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

int kernel_matrix_matrix_multiply (int argc, char **argv) {

        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running the CUDA Tile-Group Matrix-Matrix "
                         "Multiplication Kernel.\n\n");

        // Define block_size_x/y: amount of work for each tile group
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size_x/y
        uint32_t block_size_x = 0;
        uint32_t block_size_y = 0;
        hb_mc_dimension_t tg_dim = { .x = 2, .y = 2 };
        if(!strcmp("v0", test_name)){
                block_size_x = 4;
                block_size_y = 4;
                tg_dim = { .x = 2, .y = 2 };
        } else {
                bsg_pr_test_err("Invalid version provided!.\n");
                return HB_MC_INVALID;
        }
        hb_mc_dimension_t grid_dim = { .x = B_WIDTH / block_size_x,
                                       .y = A_HEIGHT / block_size_y };

        // Initialize the random number generators
        std::numeric_limits<int8_t> lim; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_real_distribution<float> distribution(lim.min(),lim.max());

        // Allocate A, B, BT, C and R (result) on the host
        float A[A_HEIGHT * A_WIDTH];
        float B[B_HEIGHT * B_WIDTH];
        float C[C_HEIGHT * C_WIDTH];
        float R[C_HEIGHT * C_WIDTH];

        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        for (uint64_t i = 0; i < A_HEIGHT * A_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                A[i] = static_cast<float>(res);
        }

        for (uint64_t i = 0; i < B_HEIGHT * B_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                B[i] = static_cast<float>(res);
        }

        // Generate the known-correct results on the host
        matrix_mult (A, B, R, A_HEIGHT, A_WIDTH, B_WIDTH);

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


        // Allocate memory on the device for A, B and C. Since sizeof(float) ==
        // sizeof(int32_t) > sizeof(int16_t) > sizeof(int8_t) we'll reuse the
        // same buffers for each test (if multiple tests are conducted)
        eva_t A_device, B_device, C_device;

        // Allocate A on the device
        rc = hb_mc_device_malloc(&device, A_HEIGHT * A_WIDTH * sizeof(float), &A_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate B on the device
        rc = hb_mc_device_malloc(&device, B_HEIGHT * B_WIDTH * sizeof(float), &B_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate C on the device
        rc = hb_mc_device_malloc(&device, C_HEIGHT * C_WIDTH * sizeof(float), &C_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Copy A & B from host onto device DRAM.
        void *dst = (void *) ((intptr_t) A_device);
        void *src = (void *) &A[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (A_HEIGHT * A_WIDTH) * sizeof(A[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }


        dst = (void *) ((intptr_t) B_device);
        src = (void *) &B[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (B_HEIGHT * B_WIDTH) * sizeof(B[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[8] = {A_device, B_device, C_device,
                                 A_HEIGHT, A_WIDTH, B_WIDTH,
                                 block_size_y, block_size_x};


        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_matrix_multiply", 8, cuda_argv);
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


        // Copy result matrix back from device DRAM into host memory.
        src = (void *) ((intptr_t) C_device);
        dst = (void *) &C[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (C_HEIGHT * C_WIDTH) * sizeof(float),
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

        // Compare the known-correct matrix (R) and the result matrix (C)
        float max = 0.1;
        double sse = matrix_sse(R, C, C_HEIGHT, C_WIDTH);

        if (sse > max) {
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
        int rc = kernel_matrix_matrix_multiply(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_matrix_mul(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

