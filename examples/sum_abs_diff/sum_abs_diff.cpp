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


/******************************************************************************/
/* Runs the sum ob absolute differences kernel between a reference and a      */
/* frame image (represented by 3D RGB pixel matrixes)                         */
/******************************************************************************/


// Reference and Frame sizes:
// V0
// Single work per tile
#define REF_HEIGHT_V0   5
#define REF_WIDTH_V0    5
#define FRAME_HEIGHT_V0 2
#define FRAME_WIDTH_V0  2
#define RES_HEIGHT_V0   (REF_HEIGHT_V0 - FRAME_HEIGHT_V0 + 1)
#define RES_WIDTH_V0    (REF_WIDTH_V0 - FRAME_WIDTH_V0 + 1)

// V1
// Multiple work per tile
#define REF_HEIGHT_V1   19
#define REF_WIDTH_V1    19
#define FRAME_HEIGHT_V1 4
#define FRAME_WIDTH_V1  4
#define RES_HEIGHT_V1   (REF_HEIGHT_V1 - FRAME_HEIGHT_V1 + 1)
#define RES_WIDTH_V1    (REF_WIDTH_V1 - FRAME_WIDTH_V1 + 1)

// V2
// Template kernel for frame dimensions
#define REF_HEIGHT_V2   19
#define REF_WIDTH_V2    19
#define FRAME_HEIGHT_V2 4
#define FRAME_WIDTH_V2  4
#define RES_HEIGHT_V2   (REF_HEIGHT_V2 - FRAME_HEIGHT_V2 + 1)
#define RES_WIDTH_V2    (REF_WIDTH_V2 - FRAME_WIDTH_V2 + 1)

// V3
// Frame dimensions fixed to 4x4
#define REF_HEIGHT_V3   19
#define REF_WIDTH_V3    19
#define FRAME_HEIGHT_V3 4
#define FRAME_WIDTH_V3  4
#define RES_HEIGHT_V3   (REF_HEIGHT_V3 - FRAME_HEIGHT_V3 + 1)
#define RES_WIDTH_V3    (REF_WIDTH_V3 - FRAME_WIDTH_V3 + 1)





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



void host_sum_abs_diff (int *REF, int *FRAME, int *RES,
                        uint32_t ref_height, uint32_t ref_width,
                        uint32_t frame_height, uint32_t frame_width,
                        uint32_t res_height, uint32_t res_width) {

        for (int y = 0; y < res_height; y ++) {
                for (int x = 0; x < res_width; x ++) {

                        int sad = 0;
                        int start_y = y;
                        int end_y = start_y + frame_height;
                        int start_x = x;
                        int end_x = start_x + frame_width;

                        for (int iter_y = start_y; iter_y < end_y; iter_y ++) {
                                for (int iter_x = start_x; iter_x < end_x; iter_x ++) {
                                        sad += abs ( REF[iter_y * ref_width + iter_x] - FRAME[(iter_y - start_y) * frame_width + (iter_x - start_x)] );
                                }
                        }

                        RES[y * res_width + x] = sad;
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

        bsg_pr_test_info("Running the CUDA Sum of Absolute Differences"
                         "Kernel.\n\n");

        // Define block_size_x/y: amount of work for each tile group
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size_x/y
        uint32_t block_size_x = 0;
        uint32_t block_size_y = 0;
        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        hb_mc_dimension_t grid_dim = { .x = 0, .y = 0 };

        uint32_t ref_height = 0;
        uint32_t ref_width = 0;
        uint32_t frame_height = 0;
        uint32_t frame_width = 0;
        uint32_t res_height = 0;
        uint32_t res_width = 0;


        if(!strcmp("v0", test_name)){
                ref_height = REF_HEIGHT_V0;
                ref_width = REF_WIDTH_V0;
                frame_height = FRAME_HEIGHT_V0;
                frame_width = FRAME_WIDTH_V0;
                res_height = RES_HEIGHT_V0;
                res_width = RES_WIDTH_V0;

                block_size_x = 4;
                block_size_y = 4;
                tg_dim = { .x = 4, .y = 4 };
                grid_dim = { .x = res_width / block_size_x,
                             .y = res_height / block_size_y };
        } else if (!strcmp("v1", test_name)) {
                ref_height = REF_HEIGHT_V1;
                ref_width = REF_WIDTH_V1;
                frame_height = FRAME_HEIGHT_V1;
                frame_width = FRAME_WIDTH_V1;
                res_height = RES_HEIGHT_V1;
                res_width = RES_WIDTH_V1;

                block_size_x = 16;
                block_size_y = 16;
                tg_dim = { .x = 4, .y = 4 };
                grid_dim = { .x = res_width / block_size_x,
                             .y = res_height / block_size_y };
        } else if (!strcmp("v2", test_name)) {
                ref_height = REF_HEIGHT_V2;
                ref_width = REF_WIDTH_V2;
                frame_height = FRAME_HEIGHT_V2;
                frame_width = FRAME_WIDTH_V2;
                res_height = RES_HEIGHT_V2;
                res_width = RES_WIDTH_V2;

                block_size_x = 16;
                block_size_y = 16;
                tg_dim = { .x = 4, .y = 4 };
                grid_dim = { .x = res_width / block_size_x,
                             .y = res_height / block_size_y };
        } else if (!strcmp("v3", test_name)) {
                ref_height = REF_HEIGHT_V3;
                ref_width = REF_WIDTH_V3;
                frame_height = FRAME_HEIGHT_V3;
                frame_width = FRAME_WIDTH_V3;
                res_height = RES_HEIGHT_V3;
                res_width = RES_WIDTH_V3;

                block_size_x = 16;
                block_size_y = 16;
                tg_dim = { .x = 4, .y = 4 };
                grid_dim = { .x = res_width / block_size_x,
                             .y = res_height / block_size_y };

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

        // Allocate REF, FRAME, RES, and RES_host on the host
        int FRAME[frame_width * frame_height];
        int REF  [ref_width * ref_height];
        int RES  [res_width * res_height];
        int RES_host [res_width * res_height];

        // Generate random numbers. Since the Manycore can't handle infinities,
        // subnormal numbers, or NANs, filter those out.
        auto res = distribution(generator);

        for (uint64_t i = 0; i < ref_width * ref_height; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                REF[i] = static_cast<int>(res);
        }

        for (uint64_t i = 0; i < frame_width * frame_height; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                FRAME[i] = static_cast<int>(res);
        }

        // Generate the known-correct results on the host
        host_sum_abs_diff (REF, FRAME, RES_host, 
                           ref_height, ref_width,
                           frame_height, frame_width, 
                           res_height, res_width);

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


        // Allocate memory on the device for REF, FRAME, and RES Since sizeof(float) ==
        // sizeof(int32_t) > sizeof(int16_t) > sizeof(int8_t) we'll reuse the
        // same buffers for each test (if multiple tests are conducted)
        eva_t REF_device, FRAME_device, RES_device;

        // Allocate REF on the device
        rc = hb_mc_device_malloc(&device, ref_height * ref_width * sizeof(float), &REF_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate FRAME on the device
        rc = hb_mc_device_malloc(&device, frame_height * frame_width * sizeof(float), &FRAME_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate RES on the device
        rc = hb_mc_device_malloc(&device, res_height * res_width * sizeof(float), &RES_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Copy FRAME & REF from host onto device DRAM.
        void *dst = (void *) ((intptr_t) REF_device);
        void *src = (void *) &REF[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (ref_height * ref_width) * sizeof(REF[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }


        dst = (void *) ((intptr_t) FRAME_device);
        src = (void *) &FRAME[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (frame_height * frame_width) * sizeof(FRAME[0]),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory to device.\n");
                return rc;
        }

        // Prepare list of input arguments for kernel.
        uint32_t cuda_argv[11] = {REF_device, FRAME_device, RES_device,
                                 ref_height, ref_width,
                                 frame_height, frame_width,
                                 res_height, res_width,
                                 block_size_y, block_size_x};

        // Enquque grid of tile groups, pass in grid and tile group dimensions,
        // kernel name, number and list of input arguments
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_sum_abs_diff", 11, cuda_argv);
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

        // Copy result matrix RES back from device DRAM into host memory.
        src = (void *) ((intptr_t) RES_device);
        dst = (void *) &RES[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (res_height * res_width) * sizeof(float),
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
        // matrix_print(RES, res_height, res_width);


        // Compare the known-correct matrix (R) and the result matrix (C)

        float max = 0.1;
        double sse = matrix_sse(RES, RES_host, res_height, res_width);

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
        int rc = kernel_sum_abs_diff(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif

