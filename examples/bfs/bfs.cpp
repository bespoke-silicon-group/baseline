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
        Graph g, t;
        std::vector<int> offsets;
        std::vector<int> edges;
        std::vector<int> roffsets;
        std::vector<int> redges;
        hb_mc_eva_t offsets_dev = 0, edges_dev = 0;
        hb_mc_eva_t roffsets_dev = 0, redges_dev = 0;
        int iterations = 1;

        void generate_graph_vectors(bool forward = true, bool transpose = true)
        {
                HammerBlade::Ptr hb = HammerBlade::Get();

                g = Graph::Tiny();
                t = g.transpose();

                if (forward) {
                        // init graph vectors
                        offsets.clear();
                        edges.clear();

                        for (int v = 0; v < g.num_nodes(); v++) {
                                offsets.push_back(static_cast<int>(g.get_offsets()[v]));
                        }
                        for (int e = 0; e < g.num_edges(); e++) {
                                edges.push_back(static_cast<int>(g.get_neighbors()[e]));
                        }

                        // allocate
                        offsets_dev    = hb->alloc(sizeof(int) * offsets.size());
                        edges_dev      = hb->alloc(sizeof(int) * edges.size());

                        // write
                        hb->push_write(offsets_dev,    &offsets[0],    sizeof(int) * offsets.size());
                        hb->push_write(edges_dev,      &edges[0],      sizeof(int) * edges.size());
                }

                if (transpose) {
                        roffsets.clear();
                        redges.clear();

                        for (int v = 0; v < t.num_nodes(); v++)
                                roffsets.push_back(static_cast<int>(t.get_offsets()[v]));

                        for (int e = 0; e < t.num_edges(); e++)
                                redges.push_back(static_cast<int>(t.get_neighbors()[e]));

                        // allocate
                        roffsets_dev = hb->alloc(sizeof(int) * roffsets.size());
                        redges_dev   = hb->alloc(sizeof(int) * redges.size());

                        // write
                        hb->push_write(roffsets_dev, &roffsets[0], sizeof(int) * roffsets.size());
                        hb->push_write(redges_dev,   &redges[0],   sizeof(int) * redges.size());
                }
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

namespace bfs_dense_i_dense_o {
        std::vector<int> dense_i, dense_o, visited_io;
        hb_mc_eva_t dense_i_dev, dense_o_dev, visited_io_dev;
        int traversed = 0;

        void generate()
        {
                dense_i_dev = dense_o_dev = visited_io_dev = 0;

                BFS bfs;
                bfs.graph() = &g;

                bfs.run(g.node_with_max_degree(), iterations+1, false);
                traversed = static_cast<int>(bfs.traversed());

                bfs.run(g.node_with_max_degree(), iterations, false);
                traversed -= static_cast<int>(bfs.traversed());

                dense_i.resize(g.num_nodes(), 0);
                dense_o.resize(g.num_nodes(), 0);
                visited_io.resize(g.num_nodes(), 0);

                for (Graph::NodeID v : bfs.active())
                        dense_i[v] = 1;

                for (Graph::NodeID v : bfs.visited())
                        visited_io[v] = 1;
        }

        void run()
        {
                HammerBlade::Ptr hb = HammerBlade::Get();

                // allocation
                dense_i_dev    = hb->alloc(sizeof(int32_t) * dense_i.size());
                dense_o_dev    = hb->alloc(sizeof(int32_t) * dense_o.size());
                visited_io_dev = hb->alloc(sizeof(int32_t) * visited_io.size());

                hb->push_write(dense_i_dev, &dense_i[0], sizeof(int32_t) * dense_i.size());
                hb->push_write(visited_io_dev, &visited_io[0], sizeof(int32_t) * visited_io.size());

                hb->sync_write();
                hb->push_job("bfs_dense_in_dense_out",
                             static_cast<int>(g.num_nodes()), static_cast<int>(g.num_edges()),
                             roffsets_dev, redges_dev,
                             dense_i_dev, dense_o_dev, visited_io_dev);
                hb->exec();

                hb->push_read(dense_o_dev,    &dense_o[0],    sizeof(int32_t)*dense_o.size());
                hb->push_read(visited_io_dev, &visited_io[0], sizeof(int32_t)*visited_io.size());

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

        std::cout << "test_name = " << std::string(test_name) << std::endl;

        HammerBlade::Ptr hb = HammerBlade::Get();
        hb->load_application(args.path);

        if (strncmp(test_name, "sparse_i_dense_o", strlen("sparse_i_dense_o"))==0) {
                generate_graph_vectors(true, false);
                bfs_sparse_i_dense_o::generate();
                bfs_sparse_i_dense_o::run();
        } else if (strncmp(test_name, "dense_i_dense_o", strlen("dense_i_dense_o"))==0) {
                generate_graph_vectors(false, true);
                bfs_dense_i_dense_o::generate();
                bfs_dense_i_dense_o::run();
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


