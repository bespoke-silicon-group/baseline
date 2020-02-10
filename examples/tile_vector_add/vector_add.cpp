// Copyright (c) 2020, University of Washington All rights reserved.
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

// Vector-Vector Addition (A + B = C).

// A,B, and C's sizes are WIDTH.
// Each time the kernel is called, it is run for (NUM_ITER + 1)
// iterations and the first iteration is discarded.
// 
// NOTE: 3 * WIDTH <= 4KB, the size of DMEM on the tile.

#include "vector_add.hpp"

// Matrix sizes:
#define A_WIDTH  128
#define B_WIDTH  A_WIDTH
#define C_WIDTH  A_WIDTH
#define NUM_ITER 1
#define FLOAT_TAG 1

// Host Vector Addition code (to compare results)
template <typename TA, typename TB, typename TC>
void vector_add (TA *A, TB *B, TC *C, uint64_t N) {
        for (uint64_t x = 0; x < N; x ++) {
                C[x] = A[x] + B[x];
        }
        return;
}

// Compute the sum of squared error between vectors A and B (M x N)
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

// Run a Vector Addition test on the Manycore, and compare the result.
// A and B are the input vectors, C is the destination, and gold is
// the known-good result computed by the host.
template<typename TA, typename TB, typename TC>
int run_test(hb_mc_device_t &device, const char* kernel,
             const TA *A, const TB *B, TC *C, const TC *gold,
             const eva_t &A_device,
             const eva_t &B_device,
             const eva_t &C_device,
             const hb_mc_dimension_t &tg_dim,
             const hb_mc_dimension_t &grid_dim,
             const hb_mc_dimension_t block_size,
             const unsigned int tag){
        int rc;

        // Copy A & B from host onto device DRAM.
        void *dst = (void *) ((intptr_t) A_device);
        void *src = (void *) &A[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (A_WIDTH) * sizeof(TA),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }


        dst = (void *) ((intptr_t) B_device);
        src = (void *) &B[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  B_WIDTH * sizeof(TB),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }


        // Prepare list of input arguments for kernel. See the kernel source
        // file for the argument uses.
        uint32_t cuda_argv[8] = {A_device, B_device, C_device,
                                 A_WIDTH, block_size.y, block_size.x,
                                 tag};

        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim,
                                   kernel, 8, cuda_argv);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize grid.\n");
                return rc;
        }


        // Launch and execute all tile groups on device and wait for all to
        // finish.
        rc = hb_mc_device_tile_groups_execute(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to execute tile groups.\n");
                return rc;
        }


        // Copy result vector back from device DRAM into host memory.
        src = (void *) ((intptr_t) C_device);
        dst = (void *) &C[0];
        rc = hb_mc_device_memcpy (&device, (void *) dst, src,
                                  C_WIDTH * sizeof(TC),
                                  HB_MC_MEMCPY_TO_HOST);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory from device.\n");
                return rc;
        }

        // Compare the known-correct vector (gold) and the result vector (C)
        float max = 0.1;
        double sse = vector_sse(gold, C, C_WIDTH);

        if (sse > max) {
                bsg_pr_test_err(BSG_RED("Vector Mismatch. SSE: %f\n"), sse);
                return HB_MC_FAIL;
        }
        bsg_pr_test_info(BSG_GREEN("Vector Match.\n"));
}

// Run a series of Vector Addition tests on the Manycore device
int kernel_vector_add (int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running CUDA Single-tile Vector Addition.\n");

        // Define tg_dim_x/y: number of tiles in each tile group
        // Define block_size_x/y: amount of work each tile group should do
        // Calculate grid_dim_x/y: number of tile groups you want to launch as:
        //   Entire work (WIDTH) / (grid_dim_x/y)

        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        hb_mc_dimension_t grid_dim = { .x = 0, .y = 0 };
        hb_mc_dimension_t block_size = { .x = 0, .y = 0 };
        tg_dim = { .x = 1, .y = 1 };
        grid_dim = { .x = 1, .y = 1};


        // Initialize the random number generators
        std::numeric_limits<int8_t> lim; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_real_distribution<float> distribution(lim.min(),lim.max());

        // Allocate A, B, C and R (result) on the host for each datatype.
        float A[A_WIDTH];
        float B[B_WIDTH];
        float C[C_WIDTH];
        float R[C_WIDTH];
        
        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        for (uint64_t i = 0; i < A_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                A[i] = static_cast<float>(res);
        }

        for (uint64_t i = 0; i < B_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                B[i] = static_cast<float>(res);
        }

        // Generate the known-correct results on the host
        vector_add (A, B, R, A_WIDTH);

        // Initialize device, load binary and unfreeze tiles.
        hb_mc_device_t device;
        rc = hb_mc_device_init(&device, test_name, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize device.\n");
                return rc;
        }

        // Initialize the device with a kernel file
        rc = hb_mc_device_program_init(&device, bin_path, "default_allocator", 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize program.\n");
                return rc;
        }

        // Allocate memory on the device for A, B and C.
        eva_t A_device, B_device, C_device;

        // Allocate A on the device
        rc = hb_mc_device_malloc(&device,
                                 A_WIDTH * sizeof(float),
                                 &A_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate B on the device
        rc = hb_mc_device_malloc(&device,
                                 B_WIDTH * sizeof(float),
                                 &B_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate C on the device
        rc = hb_mc_device_malloc(&device,
                                 C_WIDTH * sizeof(float),
                                 &C_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Run the 32-bit floating-point test and check the result
        rc = run_test(device, "kernel_vector_add_float",
                      A, B, C, R,
                      A_device, B_device, C_device,
                      tg_dim, grid_dim, block_size, FLOAT_TAG);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("float test failed\n");
                return rc;
        }
        bsg_pr_test_info("float test passed!\n");

        // Freeze the tiles and memory manager cleanup.
        rc = hb_mc_device_finish(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to de-initialize device.\n");
                return rc;
        }

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

        svScope scope;
        scope = svGetScopeFromName("tb");
        svSetScope(scope);

        int rc = kernel_vector_add(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_vector_add(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif
