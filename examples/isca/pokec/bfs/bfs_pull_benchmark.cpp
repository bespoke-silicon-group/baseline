#include "bfs_pull_benchmark.hpp"

#define X 16 
#define Y 8
#define NUM_LOCKS 1024
#define VERIFY false

#define ROOT 0

GraphHB edges;
GlobalScalar<hb_mc_eva_t> parent_dev;
Vector<int32_t> frontier_dev;
Vector<int32_t> next_frontier_dev;

void pull_call(std::vector<int> &front, std::vector<int> &next, std::vector<int> &par) { 
  int num_items = std::count(front.begin(), front.end(), 1);
  auto g = edges.getHostGraph();
  int * in_neigh = g.in_neighbors_shared_.get();
  int ** in_index = g.in_index_shared_.get();
  for(int d = 0; d < edges.num_nodes(); d++) {
    if(par[d] == -1) {
      int ind = in_index[d] - in_neigh;
      int degree = g.in_degree(d);
      int * neighbors = &in_neigh[ind]; 
      for(int s = 0; s < degree; s++) {
        if(front[neighbors[s]]) {
          par[d] = neighbors[s];
          next[d] = 1;
        }
      } 
    }
  }
}

void host_bfs_pull(std::vector<int> & front, std::vector<int> & next, std::vector<int> & par, int iter) { 
  front[ROOT] = 1;
  par[ROOT] = ROOT;
  for(int i = 0; i < iter; i++) {
    pull_call(front, next, par);
    front = next;
    std::fill(next.begin(), next.end(), 0);
  }
}

void host_bfs_push(std::vector<int> & front, std::vector<int> & next, std::vector<int> & par, int iter) { 
  front[ROOT] = 1;
  par[ROOT] = ROOT;
  for(int i = 0; i < iter; i++) {
    pull_call(front, next, par);
    front = next;
    std::fill(next.begin(), next.end(), 0);
  }
}

int launch(int argc, char * argv[]){
  InputParser input(argc, argv);
  if(!input.cmdOptionExists("-g")) { 
  
    std::cerr << "no input args\n";
    for(auto i = 0; i < argc; i++) {
      std::cerr << argv[i] << " ";
    }
    std::cerr << std::endl;
    return 0;
  }
  std::string ucode_path = input.getRISCVFile();
  int iter = 0;
  std::string iterstrbase = "iteration-";
  auto pos = ucode_path.find(iterstrbase);
  auto iterstr = ucode_path.substr(pos + iterstrbase.size(), std::string::npos);
  std::stringstream ss(iterstr);
  ss >> iter;
  std::cerr << "iteration: " << iter << std::endl;
  int version = 0; //pull-block
  if(ucode_path.find("push-block") != std::string::npos) {
    version = 1;
  }
  else if(ucode_path.find("pull-vertex") != std::string::npos) {
    version = 2;
  }
  if(ucode_path.find("push-vertex") != std::string::npos) {
    version = 3;
  }
  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;

  std::string graph_f = input.getCmdOption("-g");
  edges = hammerblade::builtin_loadEdgesFromFileToHB (graph_f.c_str()); 
  std::cerr << "out deg of 0: " << edges.out_degree(0) << "num edges: " << edges.num_edges() << " num vert: " << edges.num_nodes() << std::endl;
  Device::Ptr device = Device::GetInstance();
  std::cerr << "init global arrays" << std::endl;
  frontier_dev = Vector<int32_t>(edges.num_nodes());
  next_frontier_dev = Vector<int32_t>(edges.num_nodes());

  parent_dev = GlobalScalar<hb_mc_eva_t>("parent");
  hammerblade::init_global_array<int>(edges.num_nodes(), parent_dev);
  
  std::cerr << "host side compute up to current iter: \n";
  std::vector<int> h_frontier(edges.num_nodes(), 0);
  std::vector<int> h_parent(edges.num_nodes(), -1);
  std::vector<int> h_next(edges.num_nodes(), 0);
  if(version == 0 || version == 2) {
     host_bfs_pull(h_frontier, h_next, h_parent, iter); 
  } else {
     host_bfs_push(h_frontier, h_next, h_parent, iter); 
  }
  int num_items = std::count(h_frontier.begin(), h_frontier.end(), 1);
  std::cerr << "elems in frontier: " << num_items << std::endl;
  int dir = calculate_direction(num_items, h_frontier, edges, edges.num_nodes(), edges.num_edges());
  if(dir){ 
    if(version == 1) {version = 0;}
    else if(version == 3) {version = 2;}
  } else {
    if(version == 0) {version = 1;}
    else if(version == 2) {version = 3;}
  }
  std::vector<int>().swap(h_next);
  std::vector<int> zeros(edges.num_nodes(), 0);
  next_frontier_dev.copyToDevice(zeros.data(), edges.num_nodes());
  hammerblade::write_global_buffer_dma<int>(h_parent.data(), parent_dev, edges.num_nodes()); 
  frontier_dev.copyToDevice(h_frontier.data(), edges.num_nodes());
  std::vector<int>().swap(zeros);
  std::vector<int>().swap(h_frontier);
  std::vector<int>().swap(h_parent);

  std::cerr << "init locks\n";
  GlobalScalar<hb_mc_eva_t> glbl_locks = GlobalScalar<hb_mc_eva_t>("locks");
  hammerblade::init_global_array<std::atomic<int>>(NUM_LOCKS, glbl_locks);
  std::atomic<int> tmp_a[NUM_LOCKS] = {};
  hammerblade::write_global_buffer_dma<std::atomic<int>>(tmp_a, glbl_locks, NUM_LOCKS);

  //parent_dev.insert(65535, 65535);
  //frontier_dev.insert(65535, 1);
  std::cerr << "doing batch dma write" << std::endl;
  device->freeze_cores();
  device->write_dma();
  device->unfreeze_cores();

  std::cerr << "starting while loop" << std::endl;
  switch(version){
    case 0: { // do dense pull bfs
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
	std::cerr << "doing dense pull bfs" << std::endl;
        device->enqueueJob("edgeset_apply_pull_parallel_from_vertexset_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getInVertexlistAddr(),
                         edges.getInNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "finished call" << std::endl;
    }
    break;
    }
  case 1: { //do sparse push blocked bfs
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
        device->enqueueJob("edgeset_apply_push_parallel_from_vertexset_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getOutVertexlistAddr(),
                         edges.getOutNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "finished push call" << std::endl;
    }
    break;
    } 
    case 2: { // do dense pull bfs
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
	std::cerr << "doing dense pull bfs" << std::endl;
        device->enqueueJob("edgeset_apply_pull_parallel_from_vertexset_to_filter_func_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getInIndicesAddr(),
                         edges.getInNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "finished call" << std::endl;
    }
    break;
    }
    case 3: { // do push bfs 
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
	std::cerr << "doing push bfs" << std::endl;
        device->enqueueJob("edgeset_apply_push_parallel_from_vertexset_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getOutIndicesAddr(),
                         edges.getOutNeighborsAddr(),
                         frontier_dev.getAddr(), next_frontier_dev.getAddr(),  
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "finished call" << std::endl;
    }
    break;
    }
  }
        
  std::cerr << "finished while loop" << std::endl;

  if(VERIFY) {
    int * host_next = new int[edges.num_nodes()];
    next_frontier_dev.copyToHost(host_next, edges.num_nodes());

    device->freeze_cores();
    device->read_dma();
    device->unfreeze_cores();

    ofstream file("./frontier_verify.txt");
    if(!file.is_open()) std::cerr <<"couldn't open file\n";
    for(int i = 0; i < edges.num_nodes(); i++) {
      if(host_next[i] == 1 && i % 50 == 0) std::cerr << i << std::endl;
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
