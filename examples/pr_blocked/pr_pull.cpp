#include "pr_pull.hpp"

GraphHB edges;
Vector<float> old_rank_dev;
Vector<float> new_rank_dev;
Vector<int32_t> out_degree_dev;
Vector<float> contrib_dev;
Vector<float> error_dev;
//these are consts
GlobalScalar<float > damp_dev;
GlobalScalar<float > beta_score_dev;

int launch(int argc, char * argv[]){
	InputParser input(argc, argv);
  if(!input.cmdOptionExists("-g")){
    std::cerr << "no input args\n";
    return 0;
  }
  std::string ucode_path = input.getRISCVFile();

  bool push = false;
  if(ucode_path.find("push") != std::string::npos) push = true;

  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;

  std::string graph_f = input.getCmdOption("-g");\
  edges = hammerblade::builtin_loadEdgesFromFileToHB (graph_f.c_str());

  float tmp_rank_val = (float) 1 / edges.num_edges();
  std::vector<float> zerosf(edges.num_nodes(), 0.0);
  std::vector<int32_t> zeros(edges.num_nodes(), 0);
  std::vector<float> rank(edges.num_nodes(), tmp_rank_val);
  
  std::cerr << "load and init vectors " << tmp_rank_val << "\n";
  old_rank_dev = Vector<float>(edges.num_nodes());
  new_rank_dev = Vector<float>(edges.num_nodes());
  out_degree_dev = Vector<int32_t>(edges.num_nodes());
  contrib_dev = Vector<float>(edges.num_nodes());
  error_dev = Vector<float>(edges.num_nodes());
	std::cerr << "load global scalars\n";
  damp_dev = GlobalScalar<float >("damp");
  beta_score_dev = GlobalScalar<float >("beta_score");


  Device::Ptr device = Device::GetInstance();
  float damp = ((float) 0.85) ;
  float beta_score = ((((float) 1)  - damp) / hammerblade::builtin_getVerticesHB(edges));
	damp_dev.set(damp);
	beta_score_dev.set(beta_score);

  std::cerr << "load out degrees to vector\n";
	//TODO: need to make sure we have this implemented in GraphHB and then we can copy this to device
  std::vector<int32_t> generated_tmp_vector_2 = edges.get_in_degrees(); 
  out_degree_dev.copyToDevice(generated_tmp_vector_2.data(), edges.num_nodes());
  old_rank_dev.copyToDevice(rank.data(), rank.size());
  new_rank_dev.copyToDevice(zerosf.data(), zerosf.size());
  contrib_dev.copyToDevice(zerosf.data(), zerosf.size());
  error_dev.copyToDevice(zerosf.data(), zerosf.size());

  std::cerr << "batch dma write" << std::endl;
  device->freeze_cores();
  device->write_dma();
  device->unfreeze_cores();

  for ( int i = (0) ; i < (1) ; i++ )
  {
    device->enqueueJob("computeContrib_kernel", hb_mc_dimension(16,8),{contrib_dev.getAddr(), old_rank_dev.getAddr(), out_degree_dev.getAddr(), edges.num_nodes()});
    device->runJobs();
    if(push) {
      device->enqueueJob("edgeset_apply_push_serial_call", hb_mc_dimension(16,8),{edges.getOutVertexlistAddr() , edges.getOutNeighborsAddr(), new_rank_dev.getAddr(), contrib_dev.getAddr(), edges.num_nodes(), edges.num_edges()});
    } else {
      device->enqueueJob("edgeset_apply_pull_serial_call", hb_mc_dimension(16,8),{edges.getInVertexlistAddr() , edges.getInNeighborsAddr(), new_rank_dev.getAddr(), contrib_dev.getAddr(), edges.num_nodes(), edges.num_edges()});
    }
    device->runJobs();
    device->enqueueJob("updateVertex_kernel", hb_mc_dimension(16,8),{old_rank_dev.getAddr(), new_rank_dev.getAddr(), error_dev.getAddr(), edges.num_nodes(), edges.num_edges()});
    device->runJobs();
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
  int rc = launch(argc, argv);
  *exit_code = rc;
  bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
  return;
}
#else
int main(int argc, char ** argv) {
  bsg_pr_test_info("Unified Main CUDA Regression Test (F1)\n");
  int rc = launch(argc, argv);
  bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
  return rc;
}
#endif
