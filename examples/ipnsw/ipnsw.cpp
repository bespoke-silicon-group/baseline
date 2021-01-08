#include "ipnsw.hpp"
#include "HammerBlade.hpp"
#include "Graph500Data.hpp"
#include "Graph.hpp"
#include "IO.hpp"
#include "IPNSWGraph.hpp"
#include <iostream>

using namespace ipnsw;

using hammerblade::host::HammerBlade;
using hammerblade::host::Dim;

HammerBlade::Ptr hb;

constexpr int QUERY = 276; // fewest inner products in greedy walk

int Main(int argc, char *argv[])
{
    Parser args;
    args.parse(argc, argv);

    IO io(args);
    auto graphs = io.graphs();
    auto db = io.database<float,100>();
    auto queries = io.queries<float,100>();

    std::cout << "Read in " << db.size() << " vectors" << std::endl;
    std::cout << "Graph 0: " << graphs[0].num_nodes() << " nodes" << std::endl;
    std::cout << "Graph 0: " << graphs[0].num_edges() << " edges" << std::endl;

    std::vector<Graph> Gs = {
        Graph(std::move(graphs[3])),
        Graph(std::move(graphs[2])),
        Graph(std::move(graphs[1])),
        Graph(std::move(graphs[0]))
    };

#if 1
    hb = HammerBlade::Get();
    hb->load_application(args._ucode);

    std::cout << "Allocating database " << std::endl;
    hb_mc_eva_t db_dev = hb->alloc(db.size() * sizeof(db[0]));
    std::cout << "Allocating query "  << std::endl;
    hb_mc_eva_t q_dev  = hb->alloc(sizeof(queries[0]));
    std::cout << "Allocating seen set " << std::endl;
    hb_mc_eva_t seen_dev = hb->alloc(db.size() * sizeof(int));

    std::cout << "Pushing write jobs" << std::endl;
    hb->push_write(db_dev, &db[0], db.size() * sizeof(db[0]));
    hb->push_write(q_dev,  &queries[QUERY], sizeof(queries[0]));

    for (auto &g : Gs) g.initialize_on_device();
    // syncs
    hb_mc_eva_t graph_metadata_dev = Graph::InitializeMetadataOnDevice(Gs);

    std::cout << "Starting DMA" << std::endl;
    //hb->sync_write();
    std::cout << "Launching kernel" << std::endl;
    //hb->push_job(Dim(1,1), Dim(1,1), "inner_product_ubmk", db_dev, q_dev);
    hb->push_job(Dim(1,1), Dim(1,1), "ipnsw_greedy_search", graph_metadata_dev, db_dev, q_dev, seen_dev);
    //hb->push_job(Dim(1,1), Dim(1,1), "input_test", graph_metadata_dev, db_dev, q_dev, seen_dev);
    hb->exec();

    int result;
    hb->read(seen_dev, &result, sizeof(result));
    std::cout << "Result = " << result << std::endl;

#endif
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



