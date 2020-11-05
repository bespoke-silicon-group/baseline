#include "bc.hpp"

#define X 16 
#define Y 8

#define VERIFY true

#define ROOT 0

GraphHB edges; 
GlobalScalar<hb_mc_eva_t> num_paths_dev;
GlobalScalar<hb_mc_eva_t> dependences_dev;
GlobalScalar<hb_mc_eva_t> visited_dev;
Vector<int32_t> frontier;
Vector<int32_t> next_frontier_dev;

void forward_call(std::vector<int> &front, std::vector<int> &next, std::vector<float> &paths, std::vector<int> visited) {
 auto g = edges.getHostGraph();
 int * in_neigh = g.in_neighbors_shared_.get();
 int ** in_index = g.in_index_shared_.get();
 for(int d = 0; d < edges.num_nodes(); d++) {
   if(visited[d] == 0) {
     int degree = g.in_degree(d);
     int ind = in_index[d] - in_neigh;
     int * neighbors = &in_neigh[ind];
     for(int s = 0; s < degree; s++) {
       if(front[neighbors[s]]) {
         paths[d] += paths[neighbors[s]];
         next[d] = 1;
       } 
     }  
   }
 }
}

void backward_call(std::vector<int> & front, std::vector<float> deps, std::vector<int> visited) {
 auto g = edges.getHostGraph();
 int * out_neigh = g.out_neighbors_shared_.get();
 int ** out_index = g.out_index_shared_.get();
 for(int s = 0; s < g.num_nodes(); s++) {
   if(front[s]) {
     int degree = g.in_degree(s);
     int ind = out_index[s] - out_neigh;
     int * neighbors = &out_neigh[ind];
     for(int d = 0; d < degree; d++) {
       if(visited[neighbors[d]] == 0){
         deps[neighbors[d]] += deps[s];
       }
     }
   }
 }
}

void visited_call(std::vector<int> &output, std::vector<int> &visited) {
  for(int i = 0; i < edges.num_nodes(); i++) {
    if(output[i]) visited[i] = 1;
  }
}

void back_vertex_call(std::vector<int> front, std::vector<float> deps, std::vector<float> paths, std::vector<int> visited) {
  for(int i = 0; i < edges.num_nodes(); i++) {
    if(front[i]) {
      visited[i] = 1;
      deps[i] += (1 / paths[i]);
    }
  }
}

void host_bc_forward(std::vector<int> & front, std::vector<int> & next, std::vector<float> &paths, std::vector<int> &visited, int iter) {
  front[ROOT] = 1;
  visited[ROOT] = 1;
  paths[ROOT] = 1.0;
  for(int i = 0; i < iter; i++) {
    forward_call(front, next, paths, visited);
    visited_call(next, visited);
    front = next;
    std::fill(next.begin(), next.end(), 0); 
  }
}

void host_bc_forward_back(std::vector<int> &front, std::vector<int> &next, std::vector<float> &paths, std::vector<float> &deps, std::vector<int> &visited, int iter) {
  front[ROOT] = 1;
  visited[ROOT] = 1;
  paths[ROOT] = 1.0;
  //not fully impl yet
  std::vector<std::vector<int>> front_list;
  while(std::count(front.begin(), front.end(), 1) > 0) {
     int num_items = std::count(front.begin(), front.end(), 1);
     std::cout << "elems in front: " << num_items << std::endl; 
     forward_call(front, next, paths, visited);
     visited_call(next, visited);
     front_list.push_back(front);
     front = next;
     std::fill(next.begin(), next.end(), 0);
  }
  //intermediate steps:
  //transpose
  std::fill(visited.begin(), visited.end(), 0);
  front = front_list.back();
  front_list.pop_back();
    int num_items = std::count(front.begin(), front.end(), 1);
    std::cout << "elems in front: " << num_items << std::endl; 
  back_vertex_call(front, deps, paths, visited); 
  for(int j = 0; j < iter; j++) {
    int num_items = std::count(front.begin(), front.end(), 1);
    std::cout << "elems in front: " << num_items << " iter " << j << std::endl;
    backward_call(front, deps, visited);
    front = front_list.back();
    front_list.pop_back();
    back_vertex_call(front, deps, paths, visited); 
  }
  
  return;
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
  int version = 0; //pull-vertex-forward
  if(ucode_path.find("pull-vertex-backward") != std::string::npos) {
    version = 1;
  }
  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;

  std::string graph_f = input.getCmdOption("-g");
  //std::string frontier_f = input.getCmdOption("-f");
  edges = hammerblade::builtin_loadEdgesFromFileToHB (graph_f.c_str());
  std::cerr << "in deg of 0: " << edges.in_degree(0) << "out deg of 0: " << edges.out_degree(0) << " num verts: " << edges.num_nodes() <<  std::endl; 
  Device::Ptr device = Device::GetInstance();
  num_paths_dev = GlobalScalar<hb_mc_eva_t>("num_paths");
  hammerblade::init_global_array<float>(hammerblade::builtin_getVerticesHB(edges), num_paths_dev);
  //hammerblade::assign_val_dma<float>(0, hammerblade::builtin_getVerticesHB(edges), (0) , num_paths_dev);
  dependences_dev = GlobalScalar<hb_mc_eva_t>("dependences");
  hammerblade::init_global_array<float>(hammerblade::builtin_getVerticesHB(edges), dependences_dev);
  //hammerblade::assign_val_dma<float>(0, hammerblade::builtin_getVerticesHB(edges), (0) , dependences_dev);
  visited_dev = GlobalScalar<hb_mc_eva_t>("visited");
  hammerblade::init_global_array<int>(hammerblade::builtin_getVerticesHB(edges), visited_dev);
  //hammerblade::assign_val_dma<int>(0, hammerblade::builtin_getVerticesHB(edges),  0, visited_dev);
  
  std::cerr << "host side compute up to current iter: \n";
  std::vector<float> h_paths(edges.num_nodes(), 0);
  std::vector<float> h_dependences(edges.num_nodes(), 0);
  std::vector<int> h_visited(edges.num_nodes(), 0);
  std::vector<int> h_frontier(edges.num_nodes(), 0);
  std::vector<int> h_next(edges.num_nodes(), 0);
  if(version == 0) {
    host_bc_forward(h_frontier, h_next, h_paths, h_visited, iter);
  } else {
    host_bc_forward_back(h_frontier, h_next, h_paths, h_dependences, h_visited, iter);
  }

  int num_items = std::count(h_frontier.begin(), h_frontier.end(), 1);
  std::cerr << "elems in frontier: " << num_items << std::endl;
  std::cerr << "dependences of 0: " << h_dependences[0] << std::endl;
  frontier = Vector<int32_t> (edges.num_nodes());
  next_frontier_dev = Vector<int32_t> (edges.num_nodes());
  std::vector<int>().swap(h_next);
  std::vector<int> zeros(edges.num_nodes(), 0);
  next_frontier_dev.copyToDevice(zeros.data(), edges.num_nodes());
  frontier.copyToDevice(h_frontier.data(), edges.num_nodes());

  hammerblade::write_global_buffer_dma<int>(h_visited.data(), visited_dev, edges.num_nodes());
  hammerblade::write_global_buffer_dma<float>(h_dependences.data(), dependences_dev, edges.num_nodes());
  hammerblade::write_global_buffer_dma<float>(h_paths.data(), num_paths_dev, edges.num_nodes());
  std::cerr << "batch dma write\n";
  device->freeze_cores();
  device->write_dma();
  device->unfreeze_cores();

  switch(version){
    case 0: { // forward pull
    device->enqueueJob("edgeset_apply_pull_parallel_deduplicated_from_vertexset_to_filter_func_with_frontier_call", hb_mc_dimension(X,Y),{edges.getInIndicesAddr() , edges.getInNeighborsAddr(), frontier.getAddr(), next_frontier_dev.getAddr(), edges.num_nodes(), edges.num_edges(), edges.num_nodes()}); 
    device->runJobs();
    device->enqueueJob("mark_visited_kernel",hb_mc_dimension(X,Y),{next_frontier_dev.getAddr(), edges.num_nodes()});
    device->runJobs();
    break;
    }
    case 1: { // backward pull
  
    device->enqueueJob("edgeset_apply_push_parallel_from_vertexset_to_filter_func_call", hb_mc_dimension(X,Y),{edges.getOutIndicesAddr() , edges.getOutNeighborsAddr(), frontier.getAddr(), edges.num_nodes(), edges.num_edges(), edges.num_nodes()}); 
    device->runJobs();
    device->enqueueJob("backward_vertex_f_kernel",hb_mc_dimension(X,Y),{frontier.getAddr(), edges.num_nodes()});
    device->runJobs();
    if(iter == 10) {
      device->enqueueJob("final_vertex_f_kernel",hb_mc_dimension(X,Y),{hammerblade::builtin_getVerticesHB(edges)});
      device->runJobs();
    }
    break;
    }
  }
  if(VERIFY) {
    std::vector<int> host_next(edges.num_nodes(), 0);
    next_frontier_dev.copyToHost(host_next.data(), edges.num_nodes());
    device->freeze_cores();
    device->read_dma();
    device->unfreeze_cores();
    ofstream file("./front_verify.txt");
    if(!file.is_open()) return 0;
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
