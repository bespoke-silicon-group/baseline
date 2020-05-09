#include "sssp_pull.hpp"

WGraphHB edges;
Vector<int32_t> SP_dev;



int launch(int argc, char * argv[]){
	InputParser input(argc, argv);
	if(!input.cmdOptionExists("-g")) {
		std::cerr << "no input args\n";
		return 0;
	}

	std::cerr << "load microcode\n";
	std::string ucode_path = input.getRISCVFile();
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);

  int version = 0; 
  if(ucode_path.find("iteration-0") != std::string::npos) {
    version = 0;
  } if(ucode_path.find("iteration-1") != std::string::npos) {
    version = 1;
  } if(ucode_path.find("iteration-2") != std::string::npos) {
    version = 2;
  }
  std::cerr << "version : " << version << std::endl; 

  std::cerr << "load graph\n";
	std::string graph_f = input.getCmdOption("-g");
  edges = hammerblade::builtin_loadWeightedEdgesFromFileToHB ( graph_f.c_str()) ;


  std::string frontier_f = input.getCmdOption("-f");
  std::string frontier_v = frontier_f + "." + std::to_string(version);
  int * frontier_h = hammerblade::builtin_loadFrontierFromFile(frontier_v.c_str());

  std::string state_f = input.getCmdOption("-s");
  std::string state_v = state_f + "." + std::to_string(version);
  int * sp_h = hammerblade::builtin_loadFrontierFromFile(state_v.c_str());

  Device::Ptr device = Device::GetInstance();

  int n = edges.num_nodes(); 
  std::vector<int32_t> zeros(n, 0);
  //std::vector<int32_t> max(n, INT_MAX);

  Vector<int32_t> frontier = Vector<int32_t>(edges.num_nodes());
	Vector<int32_t> next_frontier =Vector<int32_t>(edges.num_nodes());
	SP_dev = Vector<int32_t>(edges.num_nodes());

  //frontier.copyToDevice(zeros.data(), zeros.size());
  next_frontier.copyToDevice(zeros.data(), zeros.size());
  //SP_dev.copyToDevice(max.data(), max.size());
  frontier.copyToDevice(frontier_h,n);
  SP_dev.copyToDevice(sp_h, n);

  //hammerblade::builtin_addVertexHB(frontier, (14) );
	//SP_dev.insert(14, 14);

	std::cerr << "doing batch dma write\n";
	device->freeze_cores();
	device->write_dma();
	device->unfreeze_cores();

	std::cerr << "starting while loop\n";
  int rounds = (0) ;
  //while ( (hammerblade::builtin_getVertexSetSizeHB(frontier, edges.num_nodes()) ) != ((0) ))
	for(int i = 0; i < 1; i++)
  {
    device->enqueueJob("edgeset_apply_pull_serial_weighted_deduplicatied_from_vertexset_with_frontier_call", 
												hb_mc_dimension(16,8),
												{edges.getInIndicesAddr() , edges.getInNeighborsAddr(), frontier.getAddr(), next_frontier.getAddr(), SP_dev.getAddr(), edges.num_nodes(), edges.num_edges(),edges.num_nodes()});
    device->runJobs();

    //frontier = next_frontier;
    //next_frontier.assign(0, edges.num_nodes(), 0);
    rounds = (rounds + (1) );
    if ((rounds) == (n))
     {
      std::cout << "negative cycle"<< std::endl;
      break;
     }
  }
  std::cerr << "exit of program\n" << std::endl;
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

