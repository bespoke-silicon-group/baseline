#include <cstring>
#include <cstdlib>
#include <random>
#include <limits>
#include <iostream>
#include <typeinfo>
#include <bsg_manycore_errno.h>
#include <bsg_manycore_cuda.h>
#include "../../common.h"
#include <graph_generation/graph.hpp>
#include <graph_generation/csr_blob.hpp>

using namespace formats;
using namespace graph_generation;

csr_blob_header_t * GRAPH = nullptr;

int kernel_bfs(int argc, char *argv[])
{
    GRAPH = make_csr_blob(10, 1);
    printf("generated a graph with %d nodes and %d edges\n",
	   GRAPH->n_nodes, GRAPH->n_edges);
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
    int rc = kernel_bfs(argc, argv);
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
