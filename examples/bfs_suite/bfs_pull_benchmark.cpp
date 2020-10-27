#include "bfs_pull_benchmark.hpp"

#define X 4 
#define Y 4
#define PARTITIONS 2
#define NUM_LOCKS 1024 //width of manycore * 64
GraphHB edges;
Vector<int32_t> parent_dev;
Vector<int32_t> frontier_dev;
Vector<int32_t> next_frontier_dev;

int launch(int argc, char * argv[]){
  InputParser input(argc, argv);
  if(!input.cmdOptionExists("-g") || !input.cmdOptionExists("-f") || !input.cmdOptionExists("-p")){
  
    std::cerr << "no input args\n";
    for(auto i = 0; i < argc; i++) {
      std::cerr << argv[i] << " ";
    }
    std::cerr << std::endl;
    return 0;
  }
  std::string ucode_path = input.getRISCVFile();

  int version = 0;
  if(ucode_path.find("push") != std::string::npos) {
    version = 1;
  }
  else if(ucode_path.find("beamer") != std::string::npos) {
    version = 2;
  }
  else if (ucode_path.find("blocked") != std::string::npos) {
    version = 3;
  }
  else if (ucode_path.find("part") != std::string::npos) {
    version = 4;
  }
  else if (ucode_path.find("atomics") != std::string::npos) {
    version = 5;
  }
  else if (ucode_path.find("atomic-pull") != std::string::npos) {
    version = 6;
  }
  else if (ucode_path.find("atomic-push") != std::string::npos) {
    version = 7;
  }
  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;

  std::string graph_f = input.getCmdOption("-g");
  std::string frontier_f = input.getCmdOption("-f");
  std::string parent_f = input.getCmdOption("-p");
  edges = hammerblade::builtin_loadEdgesFromFileToHB (graph_f.c_str()); 
  std::cerr << "out deg of 0: " << edges.out_degree(0) << "num edges: " << edges.num_edges() << std::endl;
  //edges = hammerblade::builtin_loadEdgesFromFileToHB ( "/mnt/users/ssd0/homes/eafurst/graphit/test/graphs/graph500.16.16.el") ;
  Device::Ptr device = Device::GetInstance();
  std::cerr << "init global arrays" << std::endl;
  parent_dev = Vector<int32_t>(edges.num_nodes());
  frontier_dev = Vector<int32_t>(edges.num_nodes());
  next_frontier_dev = Vector<int32_t>(edges.num_nodes());

  //std::vector<int32_t> zeros(edges.num_nodes(), 0);
  //next_frontier_dev.copyToDevice(zeros.data(), zeros.size());
  //frontier_dev.copyToDevice(zeros.data(), zeros.size());

  std::cerr << "Try to insert val to parent" << std::endl;
  int * file_frontier = hammerblade::builtin_loadFrontierFromFile(frontier_f.c_str());
  int * file_parent = hammerblade::builtin_loadFrontierFromFile(parent_f.c_str());
  std::cerr << "done with file read" << std::endl;

  parent_dev.copyToDevice(file_parent, edges.num_nodes());
  frontier_dev.copyToDevice(file_frontier, edges.num_nodes());
  //parent_dev.insert(65535, 65535);
  //frontier_dev.insert(65535, 1);
  //parent_dev.insert(0,0);
  //frontier_dev.insert(0,1);
  std::cerr << "doing batch dma write" << std::endl;
  device->freeze_cores();
  device->write_dma();
  device->unfreeze_cores();

  int * hostf = new int[edges.num_nodes()];
  std::cerr << "starting while loop" << std::endl;
  switch(version){
    case 0: // do dense pull bfs
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
	std::cerr << "doing dense pull bfs" << std::endl;
        device->enqueueJob("edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call",
                         hb_mc_dimension(X,Y),
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
    break;
  case 1: //do sparse push bfs
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
        device->enqueueJob("edgeset_apply_push_serial_from_vertexset_to_filter_func_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getOutIndicesAddr(),
                         edges.getOutNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  parent_dev.getAddr(),
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "finished push call" << std::endl;
        //hammerblade::swap_global_arrays<int32_t>(next_frontier_dev, frontier_dev);
        //hammerblade::assign_val_dma(0, hammerblade::builtin_getVerticesHB(edges), 0, next_frontier_dev);
        //device->write_dma();
    }
    break; 
  case 2: // do beamer's alg bfs
      for(int i = 0; i < 6; i++) //just doing one large iteration
      {
        device->enqueueJob("edgeset_apply_hybrid_parallel_call",
                         hb_mc_dimension(X,Y),
                        {edges.getOutIndicesAddr(),
                         edges.getOutNeighborsAddr(),
                         edges.getInIndicesAddr(),
                         edges.getInNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  parent_dev.getAddr(),
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes(), i});
        device->runJobs();
        std::cerr << "finished call" << std::endl;
        //hammerblade::swap_global_arrays<int32_t>(next_frontier_dev, frontier_dev);
        //hammerblade::assign_val_dma(0, hammerblade::builtin_getVerticesHB(edges), 0, next_frontier_dev);
        next_frontier_dev.copyToHost(hostf, edges.num_nodes());
        device->read_dma();
        frontier_dev.copyToDevice(hostf, edges.num_nodes());
        next_frontier_dev.assign(0,edges.num_nodes(), 0); 
        device->write_dma();
    }
    break;
  case 3: //do blocked dense pull bfs
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
        device->enqueueJob("edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getInVertexlistAddr(),
                         edges.getInNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  parent_dev.getAddr(),
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes(), i});
        device->runJobs();
      }
      break;
  case 4:
      for(int i = 0; i < PARTITIONS; i++) 
			{
        device->enqueueJob("edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call",
											 hb_mc_dimension(X,Y),
											{edges.getInVertexlistAddr(),
											 edges.getInNeighborsAddr(),
											 frontier_dev.getAddr(), next_frontier_dev.getAddr(),  parent_dev.getAddr(),
											 edges.num_nodes(),
											 edges.num_edges(),
											 edges.num_nodes()});
        device->runJobs();
        std::cerr << "finished call" << std::endl;
      }
      break;
  }
        
  std::cerr << "finished while loop" << std::endl;
  bool verify = true;

  if(verify) {
    int * host_next = new int[edges.num_nodes()];
    next_frontier_dev.copyToHost(host_next, edges.num_nodes());

    device->freeze_cores();
    device->read_dma();
    device->unfreeze_cores();

    ofstream file("./frontier_verify.txt");
    if(!file.is_open()) std::cerr <<"couldn't open file\n";
    for(int i = 0; i < edges.num_nodes(); i++) {
      file << host_next[i] << std::endl;
    }
    file.close();
  }
  return 0;
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
