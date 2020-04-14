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
#include "bfs.hpp"

using namespace hammerblade::host;
using namespace graph_tools;

namespace {
        Graph g;
        std::vector<int> offsets;
        std::vector<int> edges;
        hb_mc_eva_t offsets_dev = 0, edges_dev = 0;

        void generate_graph_vectors(void)
        {
                g = Graph::Tiny();

                // init graph vectors
                offsets.clear();
                edges.clear();

                for (int v = 0; v < g.num_nodes(); v++) {
                        offsets.push_back(static_cast<int>(g.get_offsets()[v]));
                }
                for (int e = 0; e < g.num_edges(); e++) {
                        edges.push_back(static_cast<int>(g.get_neighbors()[e]));
                }

                HammerBlade::Ptr hb = HammerBlade::Get();

                // allocate
                offsets_dev    = hb->alloc(sizeof(int) * offsets.size());
                edges_dev      = hb->alloc(sizeof(int) * edges.size());

                // write
                hb->push_write(offsets_dev,    &offsets[0],    sizeof(int) * offsets.size());
                hb->push_write(edges_dev,      &edges[0],      sizeof(int) * edges.size());
        }
}

namespace bfs_sparse_i_dense_o {
        std::vector<int> sparse_i;
        std::vector<int> dense_o;
        std::vector<int> visited_io;
        int traversed = 0;


        void generate(void)
        {
                // init algorithm vectors
                // run bfs from a hub node
                int iterations = 1;
                BFS bfs;
                bfs.graph() = &g;
                bfs.run(g.node_with_max_degree(), iterations+1);
                traversed = static_cast<int>(bfs.traversed());

                bfs.run(g.node_with_max_degree(), iterations);

                auto & active = bfs.active();
                auto & visited = bfs.visited();

                traversed -= static_cast<int>(bfs.traversed());

                visited_io.clear();
                dense_o.clear();
                sparse_i.clear();

                sparse_i.resize(g.num_nodes(), -1);
                dense_o.resize(g.num_nodes(), 0);
                visited_io.resize(g.num_nodes(), 0);

                int i = 0;
                for (Graph::NodeID v : active) {
                        sparse_i[i++] = static_cast<int>(v);
                }

                for (Graph::NodeID v : visited) {
                        visited_io[v] = 1;
                }
        }

        void run(void)
        {
                HammerBlade::Ptr hb = HammerBlade::Get();
                hb_mc_eva_t sparse_i_dev = 0, dense_o_dev = 0, visited_io_dev = 0;


                sparse_i_dev   = hb->alloc(sizeof(int) * sparse_i.size());
                dense_o_dev    = hb->alloc(sizeof(int) * dense_o.size());
                visited_io_dev = hb->alloc(sizeof(int) * visited_io.size());

                hb->push_write(sparse_i_dev,   &sparse_i[0],   sizeof(int) * sparse_i.size());
                hb->push_write(visited_io_dev, &visited_io[0], sizeof(int) * visited_io.size());
                hb->sync_write();

                hb->push_job("bfs_sparse_in_dense_out",
                             offsets.size(), edges.size(), offsets_dev, edges_dev,
                             sparse_i_dev,
                             dense_o_dev,
                             visited_io_dev);
                hb->exec();

                hb->push_read(dense_o_dev,    &dense_o[0],    sizeof(int) * dense_o.size());
                hb->push_read(visited_io_dev, &visited_io[0], sizeof(int) * visited_io.size());
                hb->sync_read();

                std::cout << "traversed " << traversed << " edges" << std::endl;

                for (int v = 0; v < visited_io.size(); v++) {
                        std::cout << "visited[" << v << "] = " << visited_io[v] << std::endl;
                }

                for (int v = 0; v < visited_io.size(); v++) {
                        std::cout << "dense[" << v << "] = " << dense_o[v] << std::endl;
                }
        }
}


int kernel_run (int argc, char **argv) {
        int rc;
        char *bin_path, *test_name;
        struct arguments_path args = {NULL, NULL};

        argp_parse (&argp_path, argc, argv, 0, 0, &args);
        bin_path = args.path;
        test_name = args.name;

        HammerBlade::Ptr hb = HammerBlade::Get();
        hb->load_application(args.path);
        generate_graph_vectors();
        bfs_sparse_i_dense_o::generate();
        bfs_sparse_i_dense_o::run();

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


