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

#include "tile_group_shared_mem.hpp"

/*
 * Runs the tile group shared memory load store test.
 */

// Matrix sizes:
#define WIDTH    1024
#define NUM_ITER 1

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

int kernel_tile_group_shared_mem (int argc, char **argv) {

        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running the CUDA Hardware Tile-Group Shared "
                         "Memory Kernel.\n\n");

        // Define block_size_x/y: amount of work for each tile group
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size_x/y
        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        if (!strcmp("v0", test_name) || !strcmp("v1", test_name)) { 
                tg_dim = { .x = 4, .y = 4 };
        } else {
                bsg_pr_test_err("Invalid version provided!.\n");
                return HB_MC_INVALID;
        }
        hb_mc_dimension_t grid_dim = { .x = 1, .y = 1}; 

        // Initialize the random number generators
        std::numeric_limits<int8_t> lim; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_real_distribution<float> distribution(lim.min(),lim.max());

        // Allocate A and R (result) on the host
        float A[WIDTH];
        float R[WIDTH];

        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        for (uint64_t i = 0; i < WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                A[i] = static_cast<float>(res);
                R[i] = 0;
        }


        // Initialize device, load binary and unfreeze tiles.
        hb_mc_device_t device;
        hb_mc_device_init_custom_dimensions(&device, test_name, 0, tg_dim);

        hb_mc_device_program_init(&device, bin_path, "default_allocator", 0);


        // Allocate memory on the device for A and R. Since sizeof(float) ==
        // sizeof(int32_t) > sizeof(int16_t) > sizeof(int8_t) we'll reuse the
        // same buffers for each test (if multiple tests are conducted)
        eva_t A_device, R_device;

        // Allocate A & R on the device
        hb_mc_device_malloc(&device, WIDTH * sizeof(float), &A_device);
        hb_mc_device_malloc(&device, WIDTH * sizeof(float), &R_device);


        // Copy A from host onto device DRAM.
        void *dst = (void *) ((intptr_t) A_device);
        void *src = (void *) &A[0];
        hb_mc_device_memcpy (&device, dst, src,
                                  WIDTH * sizeof(A[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);


        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[3] = {A_device, R_device};

        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_tile_group_shared_mem", 2, cuda_argv);

        // Launch and execute all tile groups on device and wait for all to finish.
        hb_mc_device_tile_groups_execute(&device);

        // Copy result matrix back from device DRAM into host memory.
        src = (void *) ((intptr_t) R_device);
        dst = (void *) &R[0];
        hb_mc_device_memcpy (&device, dst, src,
                                  WIDTH * sizeof(float),
                                  HB_MC_MEMCPY_TO_HOST);


        // Free device memory
        hb_mc_device_free(&device, A_device);
        hb_mc_device_free(&device, R_device);


        // Freeze the tiles and memory manager cleanup.
        hb_mc_device_finish(&device);


        // Compare the known-correct matrix (R) and the result matrix (C)
        float max = 0.1;
        double sse = vector_sse(A, R, WIDTH);

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
        int rc = kernel_tile_group_shared_mem(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_tile_group_shared_mem(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif
