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

#include "hello_world.hpp"

int run_test(hb_mc_device_t &device, const char* kernel,
             const hb_mc_dimension_t &tg_dim,
             const hb_mc_dimension_t &grid_dim){
        int rc;

        /**********************************************************************
         * Prepare list of input arguments for kernel.
         **********************************************************************/
        uint32_t cuda_argv[1] = {0};
                                
        /**********************************************************************
         * Enquque grid of tile groups, pass in grid and tile group
         * dimensions, kernel name, number and list of input arguments
         **********************************************************************/
        rc = hb_mc_kernel_enqueue (&device, grid_dim, tg_dim,
                                   kernel, 1, cuda_argv);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize grid.\n");
                return rc;
        }


        /**********************************************************************
         * Launch and execute all tile groups on device and wait for
         * all to finish.
         **********************************************************************/
        rc = hb_mc_device_tile_groups_execute(&device);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to execute tile groups.\n");
                return rc;
        }
        return rc;
}


int kernel_hello_world (int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running CUDA Hello World. "
                         "Version %s\n", args.name);

        /**********************************************************************
         * Define tg_dim_x/y: number of tiles in each tile group
         * Calculate grid_dim_x/y: number of tile groups needed
         **********************************************************************/
        hb_mc_dimension_t tg_dim = { .x = 0, .y = 0 };
        hb_mc_dimension_t grid_dim = { .x = 0, .y = 0 };
        if (!strcmp("v0", test_name)){
                tg_dim = { .x = 1, .y = 1 };
                grid_dim = { .x = 1, .y = 1 };
        } else if (!strcmp("v1", test_name)){
                tg_dim = { .x = 2, .y = 2 };
                grid_dim = { .x = 1, .y = 1 };
        } else if (!strcmp("v2", test_name)){
                tg_dim = { .x = 4, .y = 4 };
                grid_dim = { .x = 1, .y = 1 };
        } else if (!strcmp("v3", test_name)){
                tg_dim = { .x = 2, .y = 2 };
                grid_dim = { .x = 2, .y = 2 };
        } else {
                bsg_pr_test_err("Invalid version provided!.\n");
                return HB_MC_INVALID;
        }

        /**********************************************************************
         * Define path to binary.
         * Initialize device, load binary and unfreeze tiles.
         **********************************************************************/
        hb_mc_device_t device;
        rc = hb_mc_device_init(&device, test_name, 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize device.\n");
                return rc;
        }


        rc = hb_mc_device_program_init(&device, bin_path, "default_allocator", 0);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("failed to initialize program.\n");
                return rc;
        }

        /**********************************************************************
         * Allocate memory on the device for A, B and C. Since
         * sizeof(float) == sizeof(int32_t) > sizeof(int16_t) >
         * sizeof(int8_t) we'll reuse the same buffers for each test
         **********************************************************************/

        rc = run_test(device, "kernel_hello_world", tg_dim, grid_dim);
        if (rc != HB_MC_SUCCESS) {
                bsg_pr_test_err("test failed\n");
                return rc;
        }
        bsg_pr_test_info("test passed!\n");


        /**********************************************************************
         * Freeze the tiles and memory manager cleanup.
         **********************************************************************/
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

#ifdef VCS
        svScope scope;
        scope = svGetScopeFromName("tb");
        svSetScope(scope);
#endif
        int rc = kernel_hello_world(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = kernel_hello_world(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif


