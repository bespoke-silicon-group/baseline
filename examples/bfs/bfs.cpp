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
#include <RuntimeError.hpp>
#include <HammerBlade.hpp>
#include <Graph.hpp>
#include <BFS.hpp>
#include <RuntimeError.hpp>
#include <HammerBlade.hpp>
#include <Graph.hpp>
#include <BFSCSRGraph.hpp>
#include <BFSApp.hpp>
#include <BFSDenseVertexSet.hpp>
#include <BFSSparseVertexSet.hpp>
#include <BFSBlockedSparseVertexSet.hpp>
#include "bfs.hpp"
#include "bfs-common.hpp"

using namespace hammerblade::host;
using namespace graph_tools;


int kernel_run (int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        std::cout << "test_name = " << std::string(test_name) << std::endl;

        // the app
        BFSApp app(args.path);

        // graph generation
        Graph g = Graph::Tiny();
        Graph t = g.transpose();

        // frontier/visited generation
        BFS bfs;
        bfs.graph() = &g;

        bool forward = true;
        if (strncmp(test_name, "dense", strlen("dense")) == 0) {
                std::cout << "revserse graph" << std::endl;
                forward = false;
        }

        int traversed  = 0;
        int iterations = 1; // test on the second iteration
        bfs.run(g.node_with_max_degree(), iterations+1, forward);
        traversed = static_cast<int>(bfs.traversed());
        bfs.run(g.node_with_max_degree(), iterations, forward);
        traversed -= static_cast<int>(bfs.traversed());

        std::cout << "traversing " << traversed << " edges" << std::endl;

        // setup the components of the application
        BFSGraph::Ptr bfsg_ptr; //...
        BFSVertexSet::Ptr active_i_ptr, active_o_ptr, visited_io_ptr;
        std::string kernel_name = "bfs_";

        if (strcmp(test_name, "sparse_i_dense_o_v0") == 0) {
                bfsg_ptr = new BFSCSRGraph<int>(g);
                active_i_ptr = new BFSSparseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "sparse_i_dense_o";
        } else if (strcmp(test_name, "sparse_i_dense_o_v1") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(g);
                active_i_ptr = new BFSSparseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "sparse_i_dense_o";
        } else if (strcmp(test_name, "dense_i_dense_o_v0") == 0) {
                bfsg_ptr = new BFSCSRGraph<int>(t);
                active_i_ptr = new BFSDenseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "dense_i_dense_o";
        } else if (strcmp(test_name, "dense_i_dense_o_v1") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(t);
                active_i_ptr = new BFSDenseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "dense_i_dense_o";
        } else if (strcmp(test_name, "blocked_sparse_i_dense_o_v0") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<8> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_sparse_i_dense_o";
        }

        active_o_ptr = new BFSDenseVertexSet(g.num_nodes(), {});
        visited_io_ptr = new BFSDenseVertexSet(g.num_nodes(), bfs.visited());

        app.kernel_name() = kernel_name;
        app.graph() = bfsg_ptr;
        app.active_i() = active_i_ptr;
        app.active_o() = active_o_ptr;
        app.visited_io() = visited_io_ptr;

        // run the app
        app.init();
        app.run();
        app.finish();

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
        int rc = kernel_run(argc, argv);
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


