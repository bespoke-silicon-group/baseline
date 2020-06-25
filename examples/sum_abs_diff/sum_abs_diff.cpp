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

#include "sum_abs_diff.hpp"

// This test performs paralle sum of absolute differences and tests
// the performance of multiple optimization techniques, including
// using software and hardware tile group shared memory,
// templatization, and loop unrolling with different stripe sizes.

// Reference and Frame sizes:
#define REF_HEIGHT   64
#define REF_WIDTH    64
#define FRAME_HEIGHT 32
#define FRAME_WIDTH  32
#define RES_HEIGHT   (REF_HEIGHT - FRAME_HEIGHT + 1)
#define RES_WIDTH    (REF_WIDTH - FRAME_WIDTH + 1)


// Host Sum of Absolute Differences code (to compare results)
template<typename T>
void host_sum_abs_diff (T *ref, T *frame, T *res,
                        uint32_t ref_height, uint32_t ref_width,
                        uint32_t frame_height, uint32_t frame_width,
                        uint32_t res_height, uint32_t res_width) {

        for (int y = 0; y < res_height; y ++) {
                for (int x = 0; x < res_width; x ++) {

                        T sad = 0;
                        int start_y = y;
                        int end_y = start_y + frame_height;
                        int start_x = x;
                        int end_x = start_x + frame_width;

                        for (int iter_y = start_y; iter_y < end_y; iter_y ++) {
                                for (int iter_x = start_x; iter_x < end_x; iter_x ++) {
                                        sad += fabs ( ref[iter_y * ref_width + iter_x] - frame[(iter_y - start_y) * frame_width + (iter_x - start_x)] );
                                }
                        }

                        res[y * res_width + x] = sad;
                }
        }
};


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


int kernel_sum_abs_diff (int argc, char **argv) {

        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running the CUDA Sum of Absolute "
                         "Differences Kernel.\n\n");

        // Define block_size_x/y: amount of work for each tile group
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size_x/y
        uint32_t block_size_x = 0;
        uint32_t block_size_y = 0;
        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        if(!strcmp("v0", test_name) || !strcmp("v1", test_name) || 
           !strcmp("v2", test_name) || !strcmp("v3", test_name) ||
           !strcmp("v4", test_name) || !strcmp("v5", test_name)) { 
                block_size_x = RES_WIDTH;
                block_size_y = RES_HEIGHT;
                tg_dim = { .x = 4, .y = 4 };
        } else {
                bsg_pr_test_err("Invalid version provided!.\n");
                return HB_MC_INVALID;
        }
        hb_mc_dimension_t grid_dim = {.x = 1, .y = 1};

        // Initialize the random number generators
        std::numeric_limits<int8_t> lim; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_real_distribution<float> distribution(lim.min(),lim.max());

        // Allocate REF, FRAME, RES, and RES_host on the host
        constexpr size_t REF_SIZE = REF_HEIGHT * REF_WIDTH * sizeof(float);
        constexpr size_t FRAME_SIZE = FRAME_HEIGHT * FRAME_WIDTH * sizeof(float);
        constexpr size_t RES_SIZE = RES_HEIGHT * RES_WIDTH * sizeof(float);

        float frame[FRAME_SIZE];
        float ref  [REF_SIZE];
        float res  [RES_SIZE];
        float res_host [RES_SIZE];


        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto rnd = distribution(generator);

        for (uint64_t i = 0; i < REF_SIZE; i++) {
                do{
                        rnd = distribution(generator);
                }while(!std::isnormal(rnd) ||
                       !std::isfinite(rnd) ||
                       std::isnan(rnd));

                ref[i] = static_cast<float>(rnd);
        }

        for (uint64_t i = 0; i < FRAME_SIZE; i++) {
                do{
                        rnd = distribution(generator);
                }while(!std::isnormal(rnd) ||
                       !std::isfinite(rnd) ||
                       std::isnan(rnd));

                frame[i] = static_cast<float>(rnd);
        }

        // Generate the known-correct results on the host
        host_sum_abs_diff (ref, frame, res_host, 
                           REF_HEIGHT, REF_WIDTH,
                           FRAME_HEIGHT, FRAME_WIDTH, 
                           RES_HEIGHT, RES_WIDTH);


        // Initialize device, load binary and unfreeze tiles.
        hb_mc_device_t device;
        BSG_CUDA_CALL(hb_mc_device_init_custom_dimensions(&device, test_name, 0, tg_dim));

        // if DMA is not supported just return SUCCESS 
        if (!hb_mc_manycore_supports_dma_write(device.mc)
            || !hb_mc_manycore_supports_dma_read(device.mc)) {
                bsg_pr_test_info("DMA not supported for this machine: returning fail.\n");
                return HB_MC_FAIL;
        }

        BSG_CUDA_CALL(hb_mc_device_program_init(&device, bin_path, "default_allocator", 0));



        // Allocate memory on the device for REF, FRAME, and RES Since sizeof(float) ==
        // sizeof(int32_t) > sizeof(int16_t) > sizeof(int8_t) we'll reuse the
        // same buffers for each test (if multiple tests are conducted)
        hb_mc_eva_t ref_device, frame_device, res_device;


        // Allocate REF on the device
        BSG_CUDA_CALL(hb_mc_device_malloc(&device, REF_SIZE * sizeof(float), &ref_device));

        // Allocate FRAME on the device
        BSG_CUDA_CALL(hb_mc_device_malloc(&device, FRAME_SIZE * sizeof(float), &frame_device));

        // Allocate RES on the device
        BSG_CUDA_CALL(hb_mc_device_malloc(&device, RES_SIZE * sizeof(float), &res_device));


        // Copy REF & FRAME from host onto device DRAM.
        hb_mc_dma_htod_t htod_jobs [] = {
                {
                        .d_addr = ref_device,
                        .h_addr = ref,
                        .size   = REF_SIZE
                },
                {
                        .d_addr = frame_device,
                        .h_addr = frame,
                        .size   = FRAME_SIZE
                }
        };

        BSG_CUDA_CALL(hb_mc_device_dma_to_device(&device, htod_jobs, 2));

        // void *dst = (void *) ((intptr_t) ref_device);
        // void *src = (void *) &ref[0];
        // BSG_CUDA_CALL(hb_mc_device_memcpy (&device, dst, src,
        //                                    REF_SIZE * sizeof(REF[0]),
        //                                    HB_MC_MEMCPY_TO_DEVICE));

        // dst = (void *) ((intptr_t) frame_device);
        // src = (void *) &frame[0];
        // BSG_CUDA_CALL(hb_mc_device_memcpy (&device, dst, src,
        //                                    FRAME_SIZE * sizeof(FRAME[0]),
        //                                    HB_MC_MEMCPY_TO_DEVICE));


        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[11] = {ref_device, frame_device, res_device,
                                  REF_HEIGHT, REF_WIDTH,
                                  FRAME_HEIGHT, FRAME_WIDTH,
                                  RES_HEIGHT, RES_WIDTH,
                                  block_size_y, block_size_x};

        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        BSG_CUDA_CALL(hb_mc_kernel_enqueue (&device, grid_dim, tg_dim,
                                            "kernel_sum_abs_diff", 11, cuda_argv))

        // Launch and execute all tile groups on device and wait for all to finish.
        BSG_CUDA_CALL(hb_mc_device_tile_groups_execute(&device));

        // Copy result matrix back from device DRAM into host memory.
        hb_mc_dma_dtoh_t dtoh_job = {
                .d_addr = res_device,
                .h_addr = res,
                .size   = RES_SIZE 
        };

        BSG_CUDA_CALL(hb_mc_device_dma_to_host(&device, &dtoh_job, 1));

        // src = (void *) ((intptr_t) res_device);
        // dst = (void *) &res[0];
        // BSG_CUDA_CALL(hb_mc_device_memcpy (&device, dst, src,
        //                                    RES_SIZE * sizeof(float),
        //                                    HB_MC_MEMCPY_TO_HOST));


        // Freeze the tiles and memory manager cleanup.
        BSG_CUDA_CALL(hb_mc_device_finish(&device));

        // Compare the known-correct matrix (R) and the result matrix (C)
        float max = 1.0;
        double sse = matrix_sse(res, res_host, RES_HEIGHT, RES_WIDTH);

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
        int rc = kernel_sum_abs_diff(argc, argv);
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

