#include "ipnsw.hpp"
#include "HammerBlade.hpp"
#include "Graph500Data.hpp"
#include "Graph.hpp"
#include "IO.hpp"
#include "IPNSWGraph.hpp"
#include "IPNSWRunner.hpp"
#include <iostream>
#include <memory>
using namespace ipnsw;

int Main(int argc, char *argv[])
{
    Parser args;
    args.parse(argc, argv);

    std::unique_ptr<IPNSWRunner> runner;
    std::unique_ptr<IPNSWKernelRunner> kr;
    //kr = std::unique_ptr<IPNSWKernelRunner>(new GreedyWalkKernelRunner);
    kr = std::unique_ptr<IPNSWKernelRunner>(new IProductUBmkKernelRunner);
    runner = std::unique_ptr<IPNSWRunner>(new IPNSWRunner(args, kr));
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



