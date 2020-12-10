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

#include "spmd_addmv.hpp"
#define BLOCK_DIM_Y 8
#define BLOCK_DIM_X 16
#define ALLOC_NAME "default_allocator"

void host_addmv(hb_mc_host_tensor_t<float> *result,
                hb_mc_host_tensor_t<float> *input,
                hb_mc_host_tensor_t<float> *mat,
                hb_mc_host_tensor_t<float> *vec,
                float beta,
                float alpha) {

        for (int y = 0; y < result->sizes[0]; ++y) {
                float res = 0;
                for (int x = 0; x < vec->sizes[0]; ++x) {
                        res += mat->data[mat->strides[0] * y + x] * vec->data[x];
                }
                
                result->data[y] = alpha * res + beta *input->data[y];
        }
        return;
}

int kernel(int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        //
        // Define path to binary.
        // Initialize device, load binary and unfreeze tiles.
        //
        hb_mc_device_t device;
        rc = hb_mc_device_init(&device, test_name, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to initialize device.\n");
                return rc;
        }


        rc = hb_mc_device_program_init(&device, bin_path, ALLOC_NAME, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to initialize program.\n");
                return rc;
        }

        //************************************************************
        // Define tg_dim_x/y: number of tiles in each tile group
        // Calculate grid_dim_x/y: number of tile groups needed based on block_size_x/y
        //************************************************************
        hb_mc_dimension_t dev_dim = hb_mc_config_get_dimension_vcore(hb_mc_manycore_get_config(device.mc));

        hb_mc_dimension_t tg_dim = { .x = dev_dim.x, .y = dev_dim.y };

        hb_mc_dimension_t grid_dim = { .x = 1, .y = 1};


        //************************************************************
        // Allocate memory on the device for mat, vec, and out
        //************************************************************
        hb_mc_host_tensor_t<float> Hmat, Hvec, Hinput, Hout, Hresult;

        uint32_t M = BLOCK_DIM_Y * dev_dim.y * dev_dim.x;
        uint32_t N = BLOCK_DIM_X * 32;

        bsg_pr_test_info("Matrix Dimensions: %d x %d \n", M, N);

        eva_t _mat, _vec, _input, _out, _alpha, _beta;
        hb_mc_device_tensor_t mat, vec, input, out;
        float alpha[1], beta[1];
        size_t s;
        // Set up Tensor Metadata (Host and Device)
        // N = Number of Elements, dims = number of dimensions
        Hmat.N = mat.N = M * N;
        Hmat.dims = mat.dims = 2;

        Hvec.N = vec.N = N;
        Hvec.dims = vec.dims = 1;

        Hresult.N = Hout.N = out.N = Hinput.N = input.N = M;
        Hresult.dims = Hout.dims = out.dims = Hinput.dims = input.dims = 1;

        // Construct mat
        rc = hb_mc_device_malloc(&device, sizeof(hb_mc_device_tensor_t), &_mat);
        rc |= hb_mc_device_malloc(&device, mat.dims * sizeof(uint32_t), &mat.strides);
        rc |= hb_mc_device_malloc(&device, mat.dims * sizeof(uint32_t), &mat.sizes);
        // Allocate twice the size for alignment
        s = (mat.N    * sizeof(*Hmat.data));
        rc |= hb_mc_device_malloc(&device, 2 * s, &mat.data);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to allocate mat on device.\n");
                return rc;
        }

        // Align mat to itself
        mat.data = (s - (mat.data % s)) + mat.data;

        // Construct vec
        rc = hb_mc_device_malloc(&device, sizeof(hb_mc_device_tensor_t), &_vec);
        rc |= hb_mc_device_malloc(&device, vec.dims * sizeof(uint32_t), &vec.strides);
        rc |= hb_mc_device_malloc(&device, vec.dims * sizeof(uint32_t), &vec.sizes);
        // Allocate twice the size for alignment
        s = (vec.N    * sizeof(*Hvec.data));
        rc |= hb_mc_device_malloc(&device, 2 * s, &vec.data);

        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to allocate vec on device.\n");
                return rc;
        }

        // Align vec to itself
        vec.data = (s - (vec.data % s)) + vec.data;

        // Construct input
        rc = hb_mc_device_malloc(&device, sizeof(hb_mc_device_tensor_t), &_input);
        rc |= hb_mc_device_malloc(&device, input.dims * sizeof(uint32_t), &input.strides);
        rc |= hb_mc_device_malloc(&device, input.dims * sizeof(uint32_t), &input.sizes);
        // Allocate twice the size for alignment
        s = (input.N    * sizeof(*Hinput.data));
        rc |= hb_mc_device_malloc(&device, 2 * s, &input.data);

        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to allocate input on device.\n");
                return rc;
        }

        // Align input to itself
        input.data = (s - (input.data % s)) + input.data;

        // Construct out
        rc = hb_mc_device_malloc(&device, sizeof(hb_mc_device_tensor_t), &_out);
        rc |= hb_mc_device_malloc(&device, out.dims * sizeof(uint32_t), &out.strides);
        rc |= hb_mc_device_malloc(&device, out.dims * sizeof(uint32_t), &out.sizes);
        // Allocate twice the size for alignment
        s = (out.N    * sizeof(*Hout.data));
        rc |= hb_mc_device_malloc(&device, 2 * s, &out.data);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to allocate out on device.\n");
                return rc;
        }

        // Align out to itself
        out.data = (s - (out.data % s)) + out.data;

        // Construct alpha & beta
        rc = hb_mc_device_malloc(&device, sizeof(*alpha), &_alpha);
        rc = hb_mc_device_malloc(&device, sizeof(*beta), &_beta);

        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to allocate alpha and beta on device.\n");
                return rc;
        }


        // Initialize RNG
        // Initialize the random number generators
        std::numeric_limits<float> lim;

        std::mt19937 generator;
        generator.seed(42);
        std::uniform_real_distribution<float> distribution(-1,1);

        //************************************************************
        // Allocate memory on the host for mat, vec, and result
        // and initialize the first three with random values.
        //************************************************************
        Hmat.data = new float[Hmat.N];
        Hmat.sizes = new uint32_t[Hmat.dims];
        Hmat.sizes[0] = M;
        Hmat.sizes[1] = N;
        Hmat.strides = new uint32_t[Hmat.dims];
        Hmat.strides[0] = Hmat.sizes[1];
        Hmat.strides[1] = 1;
        for (uint64_t i = 0; i < Hmat.N; ++i) {
                Hmat.data[i] = distribution(generator);
        }

        Hvec.data = new float[Hvec.N];
        Hvec.sizes = new uint32_t[Hvec.dims];
        Hvec.sizes[0] = N;
        Hvec.strides = new uint32_t[Hvec.dims];
        Hvec.strides[0] = 1;
        for (uint64_t i = 0; i < Hvec.N; ++i) {
                Hvec.data[i] = distribution(generator);
        }

        Hinput.data = new float[Hinput.N];
        Hinput.sizes = new uint32_t[Hinput.dims];
        Hinput.sizes[0] = M;
        Hinput.strides = new uint32_t[Hinput.dims];
        Hinput.strides[0] = 1;
        for (uint64_t i = 0; i < Hinput.N; ++i) {
                Hinput.data[i] = distribution(generator);
        }

        Hout.data = new float[Hout.N];
        Hout.sizes = new uint32_t[Hout.dims];
        Hout.sizes[0] = M;
        Hout.strides = new uint32_t[Hout.dims];
        Hout.strides[0] = 1;

        alpha[0] = distribution(generator);
        beta[0] = distribution(generator);

        Hresult.data = new float[Hresult.N];
        Hresult.sizes = new uint32_t[Hresult.dims];
        Hresult.sizes[0] = M;
        Hresult.strides = new uint32_t[Hresult.dims];
        Hresult.strides[0] = 1;

        //************************************************************
        // Copy mat, vec, and input, from host onto device
        //************************************************************
        void *dst, *src;

        // Copy mat
        bsg_pr_test_info("Copying mat\n");
        dst = (void *) ((intptr_t) _mat);
        src = (void *) &mat;
        rc = hb_mc_device_memcpy (&device, dst, src, sizeof(mat), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy mat to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) mat.strides);
        src = (void *) Hmat.strides;
        rc = hb_mc_device_memcpy (&device, dst, src, Hmat.dims * sizeof(*Hmat.strides), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy mat.strides to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) mat.sizes);
        src = (void *) Hmat.sizes;
        rc = hb_mc_device_memcpy (&device, dst, src, Hmat.dims * sizeof(*Hmat.sizes), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy mat.sizes to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) mat.data);
        src = (void *) Hmat.data;
        rc = hb_mc_device_memcpy (&device, dst, src, Hmat.N * sizeof(*Hmat.data), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy mat.data to device.\n");
                return rc;
        }


        // Copy vec
        bsg_pr_test_info("Copying vec\n");
        dst = (void *) ((intptr_t) _vec);
        src = (void *) &vec;
        rc = hb_mc_device_memcpy (&device, dst, src, sizeof(vec), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy _vec to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) vec.strides);
        src = (void *) Hvec.strides;
        rc = hb_mc_device_memcpy (&device, dst, src, Hvec.dims * sizeof(*Hvec.strides), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy vec.strides to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) vec.sizes);
        src = (void *) Hvec.sizes;
        rc = hb_mc_device_memcpy (&device, dst, src, Hvec.dims * sizeof(*Hvec.sizes), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy vec.sizes to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) vec.data);
        src = (void *) Hvec.data;
        rc = hb_mc_device_memcpy (&device, dst, src, Hvec.N * sizeof(*Hvec.data), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy vec.data to device.\n");
                return rc;
        }

        // Copy input
        bsg_pr_test_info("Copying input\n");
        dst = (void *) ((intptr_t) _input);
        src = (void *) &input;
        rc = hb_mc_device_memcpy (&device, dst, src, sizeof(input), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy _input to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) input.strides);
        src = (void *) Hinput.strides;
        rc = hb_mc_device_memcpy (&device, dst, src, Hinput.dims * sizeof(*Hinput.strides), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy input.strides to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) input.sizes);
        src = (void *) Hinput.sizes;
        rc = hb_mc_device_memcpy (&device, dst, src, Hinput.dims * sizeof(*Hinput.sizes), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy input.sizes to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) input.data);
        src = (void *) Hinput.data;
        rc = hb_mc_device_memcpy (&device, dst, src, Hinput.N * sizeof(*Hinput.data), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy input.data to device.\n");
                return rc;
        }


        // Copy out
        bsg_pr_test_info("Copying out\n");
        dst = (void *) ((intptr_t) _out);
        src = (void *) &out;
        rc = hb_mc_device_memcpy (&device, dst, src, sizeof(out), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy _out to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) out.strides);
        src = (void *) Hout.strides;
        rc = hb_mc_device_memcpy (&device, dst, src, Hout.dims * sizeof(*Hout.strides), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy out.strides to device.\n");
                return rc;
        }

        dst = (void *) ((intptr_t) out.sizes);
        src = (void *) Hout.sizes;
        rc = hb_mc_device_memcpy (&device, dst, src, Hout.dims * sizeof(*Hout.sizes), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy out.sizes to device.\n");
                return rc;
        }


        bsg_pr_test_info("Copying alpha and beta\n");
        dst = (void *) ((intptr_t) _alpha);
        src = (void *) &alpha;
        rc = hb_mc_device_memcpy (&device, dst, src, sizeof(alpha), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy _alpha to device.\n");
                return rc;
        }
        dst = (void *) ((intptr_t) _beta);
        src = (void *) &beta;
        rc = hb_mc_device_memcpy (&device, dst, src, sizeof(beta), HB_MC_MEMCPY_TO_DEVICE);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("Failed to copy _beta to device.\n");
                return rc;
        }


        // Copying data is not necessary
        /*
          dst = (void *) ((intptr_t) out.data);
          src = (void *) Hout.data;
          rc = hb_mc_device_memcpy (&device, dst, src, Hout.N * sizeof(*Hout.data), HB_MC_MEMCPY_TO_DEVICE);
          if (rc != HB_MC_SUCCESS) {
          bsg_pr_test_err("Failed to copy out.data to device.\n");
          return rc;
          }
        */

        //************************************************************
        // Prepare list of mat arguments for kernel.
        //************************************************************
        uint32_t cuda_argv[6] = {_out, _input, _mat, _vec, _beta, _alpha};

        //************************************************************
        // Enquque grid of tile groups, pass in grid and tile group
        // dimensions, kernel name, number and list of mat arguments
        //************************************************************
        bsg_pr_test_info("Enqueue Kernel\n");
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim, "kernel_addmv", sizeof(cuda_argv)/sizeof(cuda_argv[0]), cuda_argv);
        if (rc != HB_MC_SUCCESS) { 
                bsg_pr_test_err("failed to initialize grid.\n");
                return rc;
        }

        //************************************************************
        // Launch and execute all tile groups on device and wait for all to finish.
        //************************************************************
        bsg_pr_test_info("Execute Kernel\n");

        int instr_start, fops_start;
        int instr_end, fops_end;
        uint64_t cycle_start, cycle_end;
        hb_mc_manycore_get_icount((&device)->mc, e_instr_float, &fops_start);
        hb_mc_manycore_get_icount((&device)->mc, e_instr_all, &instr_start);
        hb_mc_manycore_get_cycle((&device)->mc, &cycle_start);

        rc = hb_mc_device_tile_groups_execute(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to execute tile groups.\n");
                return rc;
        }

        hb_mc_manycore_get_cycle((&device)->mc, &cycle_end);
        hb_mc_manycore_get_icount((&device)->mc, e_instr_float, &fops_end);
        hb_mc_manycore_get_icount((&device)->mc, e_instr_all, &instr_end);

        //************************************************************
        // Copy result matrix back from device DRAM into host memory.
        //************************************************************
        bsg_pr_test_info("Copying result back\n");
        src = (void *) ((intptr_t) out.data);
        dst = (void *) Hout.data;
        rc = hb_mc_device_memcpy (&device, dst, src, Hout.N * sizeof(*Hout.data), HB_MC_MEMCPY_TO_HOST);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to copy memory from device.\n");
                return rc;
        }


        //************************************************************
        // Freeze the tiles and memory manager cleanup.
        //************************************************************
        rc = hb_mc_device_finish(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to de-initialize device.\n");
                return rc;
        }


        //************************************************************
        // Calculate the expected result matrix using host code and
        // compare the results.
        // ************************************************************
        host_addmv(&Hresult, &Hinput, &Hmat, &Hvec, beta[0], alpha[0]);

        double sse = 0;
        for(int i = 0; i < Hresult.N; ++i){
                sse += (Hresult.data[i] - Hout.data[i]) * (Hresult.data[i] - Hout.data[i]);
        }

        if (sse >= .01) {
                bsg_pr_test_err(BSG_RED("Matrix Mismatch.(SSE: %f)\n"), sse);
                return HB_MC_FAIL;
        }
        bsg_pr_test_info(BSG_GREEN("Matrix Match. (SSE: %f)\n"), sse);

        bsg_pr_test_info("\n\n====== EXECUTION STATISTICS ====== \n");
        bsg_pr_test_info("Cycles: %d\n", cycle_end-cycle_start);
        bsg_pr_test_info("Instrs: %d, Flop Count: %d\n", instr_end-instr_start, fops_end-fops_start);
        bsg_pr_test_info("Flop Rate: %3.2f\%\n", 100.0f  * static_cast<float>(fops_end-fops_start) / static_cast<float>(instr_end-instr_start));
        bsg_pr_test_info("IPC: %.2f\%\n", static_cast<float>(instr_end-instr_start) / static_cast<float>(cycle_end-cycle_start));
        bsg_pr_test_info("====== END EXECUTION STATISTICS ====== \n\n\n");

        return HB_MC_SUCCESS;
}

#ifdef VCS
int vcs_main(int argc, char ** argv) {
#else
        int main(int argc, char ** argv) {
#endif
                bsg_pr_test_info("test_matrix_mul Regression Test\n");
                int rc = kernel(argc, argv);
                bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
                return rc;
        }


