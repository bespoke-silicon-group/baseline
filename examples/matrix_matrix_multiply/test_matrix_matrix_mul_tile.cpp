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

#include "test_matrix_matrix_mul_tile.hpp"

#define ALLOC_NAME "default_allocator"
// Matrix sizes:
#define A_HEIGHT 8
#define A_WIDTH  8
#define B_HEIGHT A_WIDTH
#define B_WIDTH 8
#define C_HEIGHT A_HEIGHT
#define C_WIDTH B_WIDTH
#define NUM_ITER 4

/*!
 * Runs matrix-matrix multiplication on a single tile. This tests uses
 * the software/spmd/bsg_cuda_lite_runtime/matrix_matrix_mul_tile/ code in
 * the BSG Manycore git repository.
 */


/*!
 * Host Matrix multiplication code (to compare results)
 */
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

template <typename TA, typename TB, typename TC>
void matrix_mult_transpose (TA *A, TB *BT, TC *C, uint64_t M, uint64_t N, uint64_t P) {
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < P; x ++) {
                        TC res = 0.0f;
                        for (uint64_t k = 0; k < N; k++) {
                                res += A[y * N + k] * BT[x * N + k];
                        }
                        C[y * P + x] = res;
                }
        }
        return;
}

template <typename TA, typename TB, typename TC>
void matrix_mult_transpose_nomul (TA *A, TB *BT, TC *C, 
                                  uint64_t M, uint64_t N, uint64_t P) {
        TC sum;
        for (uint64_t y = 0, ayoff = 0, boff, coff = 0; y < M; y ++, ayoff += N) {
                boff = 0;
                for (uint64_t x = 0; x < P; x ++, coff++) {
                        sum = 0;
                        for (uint64_t aoff = ayoff; aoff < ayoff + N; aoff++, boff++) {
                                //printf("%d (%f) %d (%f)\n", aoff, A[aoff], boff, BT[boff]);
                                sum += A[aoff] * BT[boff];
                        }
                        C[coff] = sum;
                }
        }
        return;
}

template <uint8_t F, typename TA, typename TB, typename TC>
void matrix_mult_transpose_nomul_ll (TA *A, TB *BT, TC *C, uint64_t M, uint64_t N, uint64_t P) {
        for (uint64_t y = 0, ayoff = 0, boff, coff = 0; y < M; y ++, ayoff += N) {
                boff = 0;
                for (uint64_t x = 0; x < P; x +=F) {
                        TC sum[F] = {0};
                        for (uint64_t aoff = ayoff; aoff < ayoff + N; aoff++, boff++) {
                                sum[0] += A[aoff] * BT[boff + 0];
                                sum[1] += A[aoff] * BT[boff + N];
                        }
                        C[coff + 0] = sum[0];
                        C[coff + 1] = sum[1];
                        boff += N;
                        coff += F;
                }
        }
        return;
}

template <uint8_t F, typename TA, typename TB, typename TC>
void matrix_mult_transpose_nomul_unroll (TA *A, TB *BT, TC *C, uint64_t M, uint64_t N, uint64_t P) {
        uint64_t incr = N * (F-1);
        for (uint64_t y = 0, ayoff = 0, boff = 0, coff = 0; y < M; y ++, ayoff += N) {
                for (uint64_t x = 0; x < P; x += F) {
                        uint64_t bofff = 0;
                        TC sum[F] = {0};
                        for (uint64_t aoff = ayoff; aoff < ayoff + N; aoff++, ++boff) {
                                bofff = boff;
                                for (uint64_t f = 0; f < F; ++f, bofff += N){
                                        sum[f] += A[aoff] * BT[bofff];
                                        printf("%d: %d %d (%f * %f): %f\n", f, aoff, bofff, A[aoff], BT[bofff]);
                                }
                        }

                        for (uint64_t f = 0; f < F; f++){
                                printf("%d: %d, %f\n", f, coff + f, sum[f]);
                                C[coff + f] = sum[f];
                        }
                        printf("bofff %d\n", bofff);
                        boff += incr;
                        coff += F;
                }
        }
        return;
}
// Unroll second loop? FPU Pipeline depth?
// TODO: Dot Product, Int Reduce, Float Reduce
// Reduce

template <typename T>
void matrix_transpose (const T *A, T *B, uint64_t M, uint64_t N) {
        double sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        B[x * N + y] = A[y * M + x];
                }
        }
}


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

template <typename T>
void matrix_diff (T *A, T *B, T *D, uint64_t M, uint64_t N) {
        double sum = 0;
        for (uint64_t y = 0; y < M; y ++) {
                for (uint64_t x = 0; x < N; x ++) {
                        D[y * M + x] =  A[y * M + x] - B[y * M + x];
                }
        }
}

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

template<typename TA, typename TB, typename TC>
int run_test(hb_mc_device_t &device, const char* kernel,
             const TA *A, const TB *B, TC *C, const TC *gold,
             const eva_t &A_device,
             const eva_t &B_device,
             const eva_t &C_device,
             const hb_mc_dimension_t &tg_dim,
             const hb_mc_dimension_t &grid_dim,
             const unsigned int tag){
        int rc;

        /**********************************************************************
         * Copy A & B from host onto device DRAM.
         **********************************************************************/
        void *dst = (void *) ((intptr_t) A_device);
        void *src = (void *) &A[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (A_HEIGHT * A_WIDTH) * sizeof(TA),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to copy memory to device.\n");
                return rc;
        }


        dst = (void *) ((intptr_t) B_device);
        src = (void *) &B[0];
        rc = hb_mc_device_memcpy (&device, dst, src,
                                  (B_HEIGHT * B_WIDTH) * sizeof(TB),
                                  HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to copy memory to device.\n");
                return rc;
        }


        /**********************************************************************
         * Prepare list of input arguments for kernel.
         **********************************************************************/
        uint32_t cuda_argv[10] = {A_device, B_device, C_device,
                                 A_HEIGHT, A_WIDTH, B_WIDTH, tag, NUM_ITER};

        /**********************************************************************
         * Enquque grid of tile groups, pass in grid and tile group
         * dimensions, kernel name, number and list of input arguments
         **********************************************************************/
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim,
                                   kernel, 10, cuda_argv);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to initialize grid.\n");
                return rc;
        }


        /**********************************************************************
         * Launch and execute all tile groups on device and wait for
         * all to finish.
         **********************************************************************/
        rc = hb_mc_device_tile_groups_execute(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to execute tile groups.\n");
                return rc;
        }


        /**********************************************************************
         * Copy result matrix back from device DRAM into host memory.
         **********************************************************************/
        src = (void *) ((intptr_t) C_device);
        dst = (void *) &C[0];
        rc = hb_mc_device_memcpy (&device, (void *) dst, src,
                                  (C_HEIGHT * C_WIDTH) * sizeof(TC),
                                  HB_MC_MEMCPY_TO_HOST);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to copy memory from device.\n");
                return rc;
        }

        /**********************************************************************
         * Compare the known-correct matrix (gold) and the result matrix (C)
         **********************************************************************/
        float max = 0.1;
        double sse = matrix_sse(gold, C, C_HEIGHT, C_WIDTH);

        if (sse > max) {
                bsg_pr_err(BSG_RED("Matrix Mismatch. SSE: %f\n"), sse);
                return HB_MC_FAIL;
        }
        bsg_pr_test_info(BSG_GREEN("Matrix Match.\n"));
}


int kernel_matrix_matrix_mul_tile (int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running CUDA Matrix-Matrix Multiplication "
                         "on a single tile.\n");

        /**********************************************************************
         * Define tg_dim_x/y: number of tiles in each tile group
         * Calculate grid_dim_x/y: number of tile groups needed
         **********************************************************************/
        hb_mc_dimension_t tg_dim = { .x = 1, .y = 1 };
        hb_mc_dimension_t grid_dim = { .x = 1, .y = 1 };


        /**********************************************************************
         * Initialize the random number generators
         **********************************************************************/
        std::numeric_limits<int8_t> lim; // Used to get INT_MIN and INT_MAX in C++
        std::default_random_engine generator;
        generator.seed(42);
        std::uniform_real_distribution<float> distribution(lim.min(),lim.max());

        /**********************************************************************
         * Allocate random A & B on the host and initialize with random values.
         **********************************************************************/
        int32_t A_32[A_HEIGHT * A_WIDTH];
        int32_t B_32[B_HEIGHT * B_WIDTH], *B_32p;
        int32_t BT_32[B_HEIGHT * B_WIDTH];
        int32_t C_32[C_HEIGHT * C_WIDTH];
        int32_t R_32[C_HEIGHT * C_WIDTH];

        int16_t A_16[A_HEIGHT * A_WIDTH];
        int16_t B_16[B_HEIGHT * B_WIDTH], *B_16p;
        int16_t BT_16[B_HEIGHT * B_WIDTH];
        int16_t C_16[C_HEIGHT * C_WIDTH];
        int16_t R_16[C_HEIGHT * C_WIDTH];

        int8_t A_8[A_HEIGHT * A_WIDTH];
        int8_t B_8[B_HEIGHT * B_WIDTH];
        int8_t BT_8[B_HEIGHT * B_WIDTH], *B_8p;
        int8_t C_8[C_HEIGHT * C_WIDTH];
        int8_t R_8[C_HEIGHT * C_WIDTH];

        float A_f[A_HEIGHT * A_WIDTH];
        float B_f[B_HEIGHT * B_WIDTH];
        float BT_f[B_HEIGHT * B_WIDTH], *B_fp;
        float C_f[C_HEIGHT * C_WIDTH];
        float R_f[C_HEIGHT * C_WIDTH];
        float R_fprime[C_HEIGHT * C_WIDTH] = {0.0};

        void * B_actual;

        if(!strcmp("v1", test_name) || !strcmp("v2", test_name)){
                B_32p = B_32; B_16p = B_16; B_8p = B_8; B_fp = B_f;
        } else {
                B_32p = BT_32; B_16p = BT_16; B_8p = BT_8; B_fp = BT_f;
        }

                
                
        auto res = distribution(generator);

        for (uint64_t i = 0; i < A_HEIGHT * A_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                A_32[i] = static_cast<int32_t>(res);
                A_16[i] = static_cast<int16_t>(res);
                A_8[i] = static_cast<int8_t>(res);
                A_f[i] = static_cast<float>(res);
        }

        for (uint64_t i = 0; i < B_HEIGHT * B_WIDTH; i++) {
                do{
                        res = distribution(generator);
                }while(!std::isnormal(res) ||
                       !std::isfinite(res) ||
                       std::isnan(res));

                B_32[i] = static_cast<int32_t>(res);
                B_16[i] = static_cast<int16_t>(res);
                B_8[i] = static_cast<int8_t>(res);
                B_f[i] = static_cast<float>(res);
        }

        matrix_mult (A_32, B_32, R_32, A_HEIGHT, A_WIDTH, B_WIDTH);
        matrix_mult (A_16, B_16, R_16, A_HEIGHT, A_WIDTH, B_WIDTH);
        matrix_mult (A_8, B_8, R_8, A_HEIGHT, A_WIDTH, B_WIDTH);
        matrix_mult (A_f, B_f, R_f, A_HEIGHT, A_WIDTH, B_WIDTH);

        matrix_transpose(B_32, BT_32, B_HEIGHT, B_WIDTH);
        matrix_transpose(B_16, BT_16, B_HEIGHT, B_WIDTH);
        matrix_transpose(B_8, BT_8, B_HEIGHT, B_WIDTH);
        matrix_transpose(B_f, BT_f, B_HEIGHT, B_WIDTH);

        /**********************************************************************
         * Define path to binary.
         * Initialize device, load binary and unfreeze tiles.
         **********************************************************************/
        hb_mc_device_t device;
        rc = hb_mc_device_init(&device, test_name, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to initialize device.\n");
                return rc;
        }


        rc = hb_mc_device_program_init(&device, bin_path, ALLOC_NAME, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to initialize program.\n");
                return rc;
        }

        /**********************************************************************
         * Allocate memory on the device for A, B and C. Since
         * sizeof(float) == sizeof(int32_t) > sizeof(int16_t) >
         * sizeof(int8_t) we'll reuse the same buffers for each test
         **********************************************************************/

        eva_t A_device, B_device, C_device;
        // Allocate A[A_HEIGHT][A_WIDTH] on the device
        rc = hb_mc_device_malloc(&device,
                                 A_HEIGHT * A_WIDTH * sizeof(uint32_t),
                                 &A_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate B[B_HEIGHT][B_WIDTH] on the device
        rc = hb_mc_device_malloc(&device,
                                 B_HEIGHT * B_WIDTH * sizeof(uint32_t),
                                 &B_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to allocate memory on device.\n");
                return rc;
        }

        // Allocate C[C_HEIGHT][C_WIDTH] on the device
        rc = hb_mc_device_malloc(&device,
                                 C_HEIGHT * C_WIDTH * sizeof(uint32_t),
                                 &C_device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to allocate memory on device.\n");
                return rc;
        }
        rc = run_test(device, "kernel_matrix_multiply_int",
                      A_32, B_32p, C_32, R_32,
                      A_device, B_device, C_device,
                      tg_dim, grid_dim, 1);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("int32_t test failed\n");
                return rc;
        }
        bsg_pr_test_info("int32_t test passed!\n");

        rc = run_test(device, "kernel_matrix_multiply_int16",
                      A_16, B_16p, C_16, R_16,
                      A_device, B_device, C_device,
                      tg_dim, grid_dim, 2);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("int16_t test failed\n");
                return rc;
        }
        bsg_pr_test_info("int16_t test passed!\n");

        rc = run_test(device, "kernel_matrix_multiply_int8",
                      A_8, B_8p, C_8, R_8,
                      A_device, B_device, C_device,
                      tg_dim, grid_dim, 3);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("int8_t test failed\n");
                return rc;
        }
        bsg_pr_test_info("int8_t test passed!\n");

        rc = run_test(device, "kernel_matrix_multiply_float",
                      A_f, B_fp, C_f, R_f,
                      A_device, B_device, C_device,
                      tg_dim, grid_dim, 4);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("float test failed\n");
                return rc;
        }
        bsg_pr_test_info("float test passed!\n");

        /**********************************************************************
         * Freeze the tiles and memory manager cleanup.
         **********************************************************************/
        rc = hb_mc_device_finish(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_err("failed to de-initialize device.\n");
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

#ifdef VCS
        svScope scope;
        scope = svGetScopeFromName("tb");
        svSetScope(scope);
#endif
        bsg_pr_test_info("test_matrix_mul_tile Regression Test (COSIMULATION)\n");
        int rc = kernel_matrix_matrix_mul_tile(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        bsg_pr_test_info("test_matrix_mul_tile Regression Test (F1)\n");
        int rc = kernel_matrix_matrix_mul_tile(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif


