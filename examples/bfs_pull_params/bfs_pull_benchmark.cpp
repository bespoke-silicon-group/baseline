#include "bfs_pull_benchmark.hpp"

GraphHB edges;
Vector<int32_t> parent_dev;
Vector<int32_t> frontier_dev;
Vector<int32_t> next_frontier_dev;

int launch(int argc, char * argv[]){
  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;
  edges = hammerblade::builtin_loadEdgesFromFileToHB ( "/mnt/users/ssd0/homes/eafurst/graphit/test/graphs/graph500.20.16.el") ;
  Device::Ptr device = Device::GetInstance();
  std::cerr << "init global arrays" << std::endl; 
  parent_dev = Vector<int32_t>(edges.num_nodes());
  frontier_dev = Vector<int32_t>(edges.num_nodes());
  next_frontier_dev = Vector<int32_t>(edges.num_nodes());
 
  std::vector<int32_t> zeros(edges.num_nodes(), 0);
  next_frontier_dev.copyToDevice(zeros.data(), zeros.size());
  
  std::cerr << "Try to insert val to parent" << std::endl;
  int * file_frontier = hammerblade::builtin_loadFrontierFromFile("/mnt/users/ssd0/homes/eafurst/graphit/test/graphs/frontier_dense_graph500.20.16.txt");
  int * file_parent = hammerblade::builtin_loadFrontierFromFile("/mnt/users/ssd0/homes/eafurst/graphit/test/graphs/parent_dense_graph500.20.16.txt");
  std::cerr << "done with file read" << std::endl;

  parent_dev.copyToDevice(file_parent, edges.num_nodes());
  frontier_dev.copyToDevice(file_frontier, edges.num_nodes());
  std::cerr << "doing batch dma write" << std::endl;
  device->write_dma(); 
 

  //int host_parent[edges.num_nodes()];
  //int host_frontier[edges.num_nodes()];
  std::cerr << "starting while loop" << std::endl;
  for(int i = 0; i < 1; i++) //just doing one large iteration 
  {
      device->enqueueJob("edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call",
                        {edges.getInIndicesAddr(),
                         edges.getInNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  parent_dev.getAddr(),
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
      device->runJobs();
      std::cerr << "finished call" << std::endl;
      //hammerblade::swap_global_arrays<int32_t>(next_frontier_dev, frontier_dev);
      //hammerblade::assign_val_dma(0, hammerblade::builtin_getVerticesHB(edges), 0, next_frontier_dev);
      //device->write_dma();
  }
  std::cerr << "finished while loop" << std::endl;
  return 0;
  //hammerblade::read_global_buffer<int32_t>(host_parent, parent_dev, edges.num_nodes());
  //std::cerr << "Results of BFS" << std::endl;
  //for(auto i : host_parent) {
  //    std::cerr << i << std::endl;
  //}
}
#ifdef COSIM
void cosim_main(uint32_t *exit_code, char * args) {
    int argc = get_argc(args);
    char *argv[argc];
    get_argv(args, argc, argv);
#ifdef VCS
    svScope scope;
    scope = svGetScopeFromName("tb");
    svSetScope(scope);
#endif
    bsg_pr_test_info("Unified Main Regression Test (COSIMULATION)\n");
    int rc = launch(argc,argv);
    *exit_code = rc;
    bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
    return;
}
#else
int main(int argc, char ** argv) {
    bsg_pr_test_info("Unified Main CUDA Regression Test (F1)\n");
    int rc = launch(argc,argv);
    bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
    return rc;
}
#endif

