#include "pr_pull.hpp"

GraphHB edges;
Vector<double> old_rank_dev;
Vector<double> new_rank_dev;
Vector<int32_t> out_degree_dev;
Vector<double> contrib_dev;
Vector<double> error_dev;
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

  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;

  std::string graph_f = input.getCmdOption("-g");\
  edges = hammerblade::builtin_loadEdgesFromFileToHB (graph_f.c_str());


  old_rank_dev = Vector<double>(edges.num_nodes(), ((double) 1.0/edges.num_edges()));
  new_rank_dev = Vector<double>(edges.num_nodes(), 0.0);
  out_degree_dev = Vector<int32_t>(edges.num_nodes());
  contrib_dev = Vector<double>(edges.num_nodes(), 0.0);
  error_dev = Vector<double>(edges.num_nodes(), 0.0);
	
  damp_dev = GlobalScalar<float >("damp");
  beta_score_dev = GlobalScalar<float >("beta_score");

  Device::Ptr device = Device::GetInstance();
  float damp = ((float) 0.85) ;
  float beta_score = ((((float) 1)  - damp) / hammerblade::builtin_getVerticesHB(edges));
	damp_dev.set(damp);
	beta_score_dev.set(beta_score);

	//TODO: need to make sure we have this implemented in GraphHB and then we can copy this to device
  std::vector<int32_t> generated_tmp_vector_2 = edges.get_out_degrees(); 
  out_degree_dev.copyToDevice(generated_tmp_vector_2.data(), edges.num_nodes());

  for ( int i = (0) ; i < (1) ; i++ )
  {
    device->enqueueJob("computeContrib_kernel", hb_mc_dimension(4,4),{old_rank_dev.getAddr(), out_degree_dev.getAddr(), edges.num_nodes()});
    device->enqueueJob("edgeset_apply_pull_serial_call", hb_mc_dimension(4,4),{edges.getOutIndicesAddr() , edges.getOutNeighborsAddr(), new_rank_dev.getAddr(), contrib_dev.getAddr(), edges.num_nodes(), edges.num_edges()});
    device->enqueueJob("updateVertex_kernel", hb_mc_dimension(4,4),{old_rank_dev.getAddr(), new_rank_dev.getAddr(), error_dev.getAddr(), edges.num_nodes(), edges.num_edges()});
    device->runJobs();
  }
}
