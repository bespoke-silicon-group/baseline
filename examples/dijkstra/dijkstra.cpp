#include <cstdint>
#include <HammerBlade.hpp>
#include <WGraph.hpp>
#include <string>
#include <cstdlib>
#include <DijkstraGraph.hpp>
#include <Dijkstra.hpp>
#include <FastDijkstra.hpp>
#include <cmath>
#include "../common.h"

using namespace hammerblade::host;
using namespace graph_tools;
HammerBlade::Ptr hb;

int dijkstra_main (int argc, char **argv) {
        int rc;
        
        char *bin_path, *test_name;
        std::string graph_type;
        std::string bin_path_string;        
        int graph_nodes, graph_edges;
        int graph_max_hops;
        
        bin_path = argv[1];
        test_name = argv[2];
        bin_path_string = std::string(bin_path);
        graph_type = std::string(argv[3]);
        graph_nodes = atoi(argv[4]);
        graph_edges = atoi(argv[5]);
        graph_max_hops = atoi(argv[6]);
        
        printf("graph_type=%s\n", graph_type.c_str());
        printf("graph_nodes=%d\n", graph_nodes);
        printf("graph_edges=%d\n", graph_edges);

        int root, goal;
        WGraph wg;

        if (graph_type == "list") {
            wg = WGraph::List(graph_nodes, graph_edges);
            root = 0;
        } else if (graph_type == "graph500") {
            wg = WGraph::Generate(graph_nodes == 0 ? 0 : ceil(log2(graph_nodes)), graph_edges);
            root = wg.node_with_max_degree();
        } else if (graph_type == "tree") {
            wg = WGraph::BalancedTree(ceil(log2(graph_nodes)), graph_edges);
            root = 0;
        } else if (graph_type == "uniform") {
            wg = WGraph::Uniform(graph_nodes, graph_edges);
            root = 0;
        } else {
            printf("[ERROR]: bad graph_type=%s\n", graph_type.c_str());
            return 1;
        }

        Dijkstra dijkstra(wg, root);
        dijkstra.run();
        dijkstra.stats("dijkstra_stats.txt");

        FastDijkstra fdijkstra(wg, root, dijkstra.goal(graph_max_hops));
        fdijkstra.run();
        fdijkstra.stats("fast_dijkstra_stats.txt");

        goal = dijkstra.goal();


        hb = HammerBlade::Get();
        hb->load_application(bin_path);

        DijkstraGraph g;
        if (bin_path_string.find("tree_dijkstra") != std::string::npos) {
            printf("initializing reverse graph for binary '%s'\n", bin_path_string.c_str());
            g.InitializeWithWGraph(wg.transpose());
        } else {
            g.InitializeWithWGraph(wg);
        }

        hb_mc_eva_t distance = hb->alloc(sizeof(float) * g.V());
        hb_mc_eva_t path   = hb->alloc(sizeof(int) * g.V());
        hb_mc_eva_t queue = hb->alloc(sizeof(int) * g.V());
        std::vector<int> queue_host;
        if (bin_path_string.find("dijkstra-set") != std::string::npos) {
            queue_host.resize(g.V(), 0xffffffff);
            hb->push_write(queue, &queue_host[0], sizeof(int)*g.V());
        }

        std::vector<float> distance_init(g.V(), INFINITY);
        std::vector<int>   path_init(g.V(), -1);

        hb->push_write(distance, &distance_init[0], sizeof(float) * g.V());
        hb->push_write(path, &path_init[0], sizeof(int) * g.V());
        printf("Starting DMA\n");
        hb->sync_rw();

        printf("Launching kernel\n");
        hb->push_job(Dim(1,1), Dim(1,1), "dijkstra", g.MetaData(), root, goal, distance, path, queue);
        hb->exec();
        printf("Done!\n");

        hb->push_read(distance, &distance_init[0], sizeof(float) * g.V());
        hb->push_read(path,     &path_init[0],     sizeof(int) * g.V());
        hb->sync_rw();

        // prime cache if graph is small?
        
        printf("Dijkstra: distance (root(%d) -> goal(%d)) = %f\n",
               root, goal,
               dijkstra.distance()[goal]);
        
        printf("Device:   distance (root(%d) -> goal(%d)) = %f\n", root, goal, distance_init[goal]);

        if (!std::isinf(distance_init[goal])) {
            int v = goal;
            do {
                printf("%d <- ", v);
                v = path_init[v];
            } while (v != root);
            printf("%d\n", v);
        }
        
        delete hb;        
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
        int rc = dijkstra_main(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char ** argv) {
        int rc = dijkstra_main(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif


