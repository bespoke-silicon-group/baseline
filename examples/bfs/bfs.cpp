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
#include <BFSBlockedCSRGraph.hpp>
#include <BFSApp.hpp>
#include <BFSDenseVertexSet.hpp>
#include <BFSSparseVertexSet.hpp>
#include <BFSBlockedSparseVertexSet.hpp>
#include <algorithm>
#include "bfs.hpp"
#include "bfs-common.hpp"

using namespace hammerblade::host;
using namespace graph_tools;

namespace {
    std::set<Graph::NodeID> visited_correct;
    std::set<Graph::NodeID> active_o_correct;
}

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
        if (strncmp(test_name, "dense", strlen("dense")) == 0
            || strncmp(test_name, "blocked_dense", strlen("blocked_dense")) == 0
            || strncmp(test_name, "blocked_edge_dense", strlen("blocked_edge_dense")) == 0) {
                std::cout << "revserse graph" << std::endl;
                forward = false;
        }

        int traversed  = 0;
        int iterations = 1; // test on the second iteration

        bfs.run(g.node_with_max_degree(), iterations+1, forward);
        // get the correct answer
        visited_correct = bfs.visited();
        active_o_correct = bfs.active();

        // we diff the number of traversed edges to count teps for one iteration
        traversed = static_cast<int>(bfs.traversed());
        bfs.run(g.node_with_max_degree(), iterations, forward);
        traversed -= static_cast<int>(bfs.traversed());

        std::cout << "traversing " << traversed << " edges" << std::endl;

        // setup the components of the application
        BFSGraph::Ptr bfsg_ptr; //...
        BFSVertexSet::Ptr active_i_ptr, active_o_ptr, visited_io_ptr;
        std::string kernel_name = "bfs_";

        if (strcmp(test_name, "sparse_i_dense_o") == 0 ||
            strcmp(test_name, "sparse_i_dense_o_rmw_coalesce") == 0) {
                bfsg_ptr = new BFSCSRGraph<int>(g);
                active_i_ptr = new BFSSparseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "sparse_i_dense_o";

        } else if (strcmp(test_name, "sparse_i_dense_o_precompute_degree_colocated") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(g);
                active_i_ptr = new BFSSparseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "sparse_i_dense_o";

        } else if (strcmp(test_name, "dense_i_dense_o") == 0) {
                bfsg_ptr = new BFSCSRGraph<int>(t);
                active_i_ptr = new BFSDenseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "dense_i_dense_o";

        } else if (strcmp(test_name, "dense_i_dense_o_precompute_degree_colocated") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(t);
                active_i_ptr = new BFSDenseVertexSet(g.num_nodes(), bfs.active());
                kernel_name += "dense_i_dense_o";

        } else if (strcmp(test_name, "blocked_sparse_i_dense_o_vbsize8") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<8> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_sparse_i_dense_o_vbsize16") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<16> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_sparse_i_dense_o_vbsize32") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<32> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_edge_sparse_i_dense_o_vbsize16_ebsize16") == 0) {
                bfsg_ptr = new BFSBlockedCSRGraph<16,16>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<16> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_edge_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_edge_sparse_i_dense_o_vbsize16_ebsize32") == 0) {
                bfsg_ptr = new BFSBlockedCSRGraph<16,32>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<16> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_edge_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_edge_sparse_i_dense_o_vbsize16_ebsize64") == 0) {
                bfsg_ptr = new BFSBlockedCSRGraph<16,64>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<16> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_edge_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_edge_sparse_i_dense_o_vbsize32_ebsize64") == 0 ||
                   strcmp(test_name, "blocked_edge_sparse_i_dense_o_prefetch_vbsize32_ebsize64") == 0 ||
                   strcmp(test_name, "blocked_edge_sparse_i_dense_o_prefetch_rmw_coalesce_vbsize32_ebsize64") == 0) {
                bfsg_ptr = new BFSBlockedCSRGraph<32,64>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<32> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_edge_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_edge_sparse_i_dense_o_vbsize64_ebsize128") == 0) {
                bfsg_ptr = new BFSBlockedCSRGraph<64,128>(g);
                active_i_ptr =
                        new BFSBlockedSparseVertexSet<64> (g.num_nodes(), bfs.active());
                kernel_name += "blocked_edge_sparse_i_dense_o";

        } else if (strcmp(test_name, "blocked_dense_i_dense_o_vbsize16") == 0 ||
                   strcmp(test_name, "blocked_dense_i_dense_o_vbsize32") == 0 ||
                   strcmp(test_name, "blocked_dense_i_dense_o_vbsize64") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(t);
                active_i_ptr =
                        new BFSDenseVertexSet (g.num_nodes(), bfs.active());
                kernel_name += "blocked_dense_i_dense_o";

        } else if (strcmp(test_name, "blocked_edge_dense_i_dense_o_vbsize16_ebsize16") == 0) {
                bfsg_ptr = new BFSBlockedCSRGraph<16,16>(t);
                active_i_ptr =
                        new BFSDenseVertexSet (g.num_nodes(), bfs.active());
                kernel_name += "blocked_edge_dense_i_dense_o";

        } else if (strcmp(test_name, "blocked_dense_i_dense_o_coalesce_dense_o_vbsize16") == 0 ||
                   strcmp(test_name, "blocked_dense_i_dense_o_coalesce_dense_o_vbsize32") == 0) {
                bfsg_ptr = new BFSCSRGraph<node_data_t>(t);
                active_i_ptr =
                        new BFSDenseVertexSet (g.num_nodes(), bfs.active());
                kernel_name += "blocked_dense_i_dense_o_coalesce_dense_o";
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

        // validate the results
        int r = HB_MC_SUCCESS;
        auto active_o_answer = active_o_ptr->set();
        if (active_o_correct != active_o_answer) {
            std::set<Graph::NodeID> cda, adc;

            for (auto v : active_o_correct) {
                if (active_o_answer.find(v) == active_o_answer.end())
                    cda.insert(v);
            }

            for (auto v : active_o_answer) {
                if (active_o_correct.find(v) == active_o_correct.end())
                    adc.insert(v);
            }

            std::cout << "Error: output frontier not equal" << std::endl;
            std::cout << "Correct - Answer: {";
            for (auto v : cda)
                std::cout << v << ", ";
            std::cout << "}" << std::endl;

            std::cout << "Answer - Correct: {";
            for (auto v : adc)
                std::cout << v << ", ";
            std::cout << "}" << std::endl;

            r = HB_MC_FAIL;
        }
        auto visited_answer = visited_io_ptr->set();
        if (visited_correct != visited_answer) {
            std::cerr << "Error: output visited set not equal" << std::endl;
            std::set<Graph::NodeID> cda, adc;

            for (auto v : visited_correct) {
                if (visited_answer.find(v) == visited_answer.end())
                    cda.insert(v);
            }

            for (auto v : visited_answer) {
                if (visited_correct.find(v) == visited_correct.end())
                    adc.insert(v);
            }

            std::cout << "Error: visited set not equal" << std::endl;
            std::cout << "Correct - Answer: {";
            for (auto v : cda)
                std::cout << v << ", ";
            std::cout << "}" << std::endl;

            std::cout << "Answer - Correct: {";
            for (auto v : adc)
                std::cout << v << ", ";
            std::cout << "}" << std::endl;

            r = HB_MC_FAIL;
        }

        return r;
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


