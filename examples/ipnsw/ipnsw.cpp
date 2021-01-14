#include "ipnsw.hpp"
#include "HammerBlade.hpp"
#include "Graph500Data.hpp"
#include "Graph.hpp"
#include "IO.hpp"
#include "IPNSWGraph.hpp"
#include "IPNSWRunner.hpp"
#include "IProductUBmkKernelRunner.hpp"
#include "IProductUBmkResultReader.hpp"
#include "BeamSearchKernelRunner.hpp"
#include "GreedyWalkKernelRunner.hpp"
#include "GreedyWalkResultReader.hpp"
#include "GreedyWalkResults.hpp"
#include <iostream>
#include <memory>

#include "GreedyWalkResults.cpp"

using namespace ipnsw;

int Main(int argc, char *argv[])
{
    Parser args;
    args.parse(argc, argv);

    std::unique_ptr<IPNSWRunner> runner;
    std::unique_ptr<IPNSWKernelRunner> kr;
    std::unique_ptr<IPNSWResultReader> rr;

    if (args._version == "greedy_walk") {
        kr = std::unique_ptr<IPNSWKernelRunner>(new GreedyWalkKernelRunner);
        rr = std::unique_ptr<IPNSWResultReader>(new GreedyWalkResultReader);
    } else if (args._version == "beam_search") {
        kr = std::unique_ptr<IPNSWKernelRunner>(new BeamSearchKernelRunner);
        rr = std::unique_ptr<IPNSWResultReader>(new IPNSWResultReader);
    } else if (args._version == "iproduct_ubmk") {
        kr = std::unique_ptr<IPNSWKernelRunner>(new IProductUBmkKernelRunner(500));
        rr = std::unique_ptr<IPNSWResultReader>(new IPNSWResultReader);
    } else {
        return 0;
    }

    runner = std::unique_ptr<IPNSWRunner>(new IPNSWRunner(args, kr, rr));
    runner->run();

    return 0;
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
    int rc = Main(argc, argv);
    *exit_code = rc;
    return;
}
#else
int main(int argc, char ** argv) {
    return Main(argc, argv);
}
#endif
