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

#include "fast-memcpy.hpp"
#include <HammerBlade.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

using hammerblade::host::HammerBlade;

static constexpr int32_t LENGTH = 64 * 1024;
static constexpr int32_t BUFSZ  = LENGTH * sizeof(int32_t);

int fast_memcpy (int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        HammerBlade::Ptr hb = HammerBlade::Get();
        hb->load_application(bin_path);
        
        hb_mc_eva_t dst_dev, src_dev;
        dst_dev = hb->alloc(BUFSZ);
        src_dev = hb->alloc(BUFSZ);

        std::vector<int32_t> data(LENGTH);
        for (int & v : data)
                v = rand();
        
        hb->push_write(src_dev, &data[0], BUFSZ);
        hb->freeze_tiles();
        hb->sync_write();
        hb->unfreeze_tiles();
        hb->push_job("fast_memcpy", dst_dev, src_dev, LENGTH);
        hb->exec();

        std::vector<int32_t> result(LENGTH);
        hb->push_read(dst_dev, &result[0], BUFSZ);
        hb->freeze_tiles();
        hb->sync_read();
        hb->unfreeze_tiles();
        
        if (memcmp(&result[0], &data[0], BUFSZ) != 0) {
                std::cerr << "ERROR: DATA DOES NOT MATCH" << std::endl;
                return HB_MC_FAIL;
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
        int rc = fast_memcpy(argc, argv);
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


