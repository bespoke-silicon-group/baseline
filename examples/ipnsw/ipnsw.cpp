#include "ipnsw.hpp"
#include "HammerBlade.hpp"

using hammerblade::host::HammerBlade;
using hammerblade::host::Dim;

HammerBlade::Ptr hb;

int Main(int argc, char *argv[])
{
    const char *app, *ucode, *version;
    app = argv[0];
    ucode = argv[1];
    version = argv[2];

    hb = HammerBlade::Get();
    hb->load_application(ucode);
    hb->push_job(Dim(1,1), Dim(1,1), "ipnsw_greedy_search", 1);
    hb->exec();

    delete hb;
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



