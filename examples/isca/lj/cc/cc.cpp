#include "cc.hpp"

#define X 16 
#define Y 8
#define PARTITIONS 2
#define NUM_LOCKS 1024
#define VERIFY true 

GraphHB edges;
GlobalScalar<hb_mc_eva_t> IDs_dev; 
GlobalScalar<hb_mc_eva_t> update_dev; 
Vector<int32_t> frontier_dev;
Vector<int32_t> next_frontier_dev;

bool apply_func(int s, int d, std::vector<int> & ids) {
  bool output = false;
  if(ids[d] != ids[s]) {
    if(ids[d] > ids[s]) {
      ids[s] = ids[s];
      output = true;
    }
  }
  return output;
}

void pull_call(std::vector<int> & front, std::vector<int> & next, std::vector<int> & ids) {
  auto g = edges.getHostGraph();
  int * in_neigh = g.in_neighbors_shared_.get();
  int ** in_index = g.in_index_shared_.get();
  for(auto d = 0; d < front.size(); d++) {
    int degree = g.in_degree(d);
    int ind = in_index[d] - in_neigh;
    int * neighbors = &in_neigh[ind];
    for(int s = 0; s < degree; s++) {
      if(apply_func(neighbors[s], d, ids)) {
        next[d] = 1;
      }
    }
  }
}

void pjump(std::vector<int> & ids, std::vector<int> & upd) {
  for(auto i = 0; i < ids.size(); i++) {
    int y = ids[i];
    int x = ids[y];
    if(x != y) {
      ids[i] = x;
      upd[0] = 1;
    }
  }
}

void host_cc_push(std::vector<int> & front, std::vector<int> & next, std::vector<int> ids, std::vector<int> upd, int iter) {
  for(int i = 0; i < iter; i++) {
    pull_call(front, next, ids);
    front = next;
    while (upd[0] != 0){
      upd[0] = 0;
      pjump(ids, upd);
    }
    std::fill(next.begin(), next.end(), 0);
  }

}
void host_cc_pull(std::vector<int> & front, std::vector<int> & next, std::vector<int> ids, std::vector<int> upd, int iter) {
  
  for(int i = 0; i < iter; i++) {
    pull_call(front, next, ids);
    front = next;
    while (upd[0] != 0){
      upd[0] = 0;
      pjump(ids, upd);
    }
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

  int version = 0; //pull-vertex
  if(ucode_path.find("push-vertex") != std::string::npos) {
    version = 1;
  }
  std::cerr << "load microcode" << std::endl;
  hammerblade::builtin_loadMicroCodeFromFile(ucode_path);
  std::cerr << "load graph" << std::endl;

  std::string graph_f = input.getCmdOption("-g");
  //std::string frontier_f = input.getCmdOption("-f");
  edges = hammerblade::builtin_loadEdgesFromFileToHB (graph_f.c_str()); 
  std::cerr << "out deg of 0: " << edges.out_degree(0) << "num edges: " << edges.num_edges() << std::endl;
  Device::Ptr device = Device::GetInstance();
  std::cerr << "init global arrays" << std::endl;
  frontier_dev = Vector<int32_t>(edges.num_nodes(),1);
  next_frontier_dev = Vector<int32_t>(edges.num_nodes(),0);
  IDs_dev = GlobalScalar<hb_mc_eva_t>("IDs"); 
  update_dev = GlobalScalar<hb_mc_eva_t>("update"); 
  hammerblade::init_global_array<int>(edges.num_nodes(), IDs_dev);
  hammerblade::init_global_array<int>(1, update_dev);
  //for(int i = 0; i < edges.num_nodes(); i++) {
  //  hammerblade::insert_val(i, i, IDs_dev);
  //}
  //hammerblade::assign_val(0, 1, 0, update_dev); 

  std::cerr << "host side compute up to current iter: \n";
  std::vector<int32_t> h_ids(edges.num_nodes());
  for(auto i = 0; i < edges.num_nodes(); i++) {
    h_ids[i] = i;
  }
  std::vector<int32_t> h_update(1, 0);
  std::vector<int32_t> h_frontier(edges.num_nodes(), 1);
  std::vector<int32_t> h_next(edges.num_nodes(), 0);
  if(version == 1) {
    host_cc_pull(h_frontier, h_next, h_ids, h_update, iter);
  } else {
    host_cc_push(h_frontier, h_next, h_ids, h_update, iter);
  }
  int num_items = std::count(h_frontier.begin(), h_frontier.end(), 1);
  std::cerr << "num elems in frontier after host compute: " << num_items << std::endl;
  std::vector<int>().swap(h_next);
  std::vector<int> zeros(edges.num_nodes(), 0);
  next_frontier_dev.copyToDevice(zeros.data(), edges.num_nodes());
  frontier_dev.copyToDevice(h_frontier.data(), edges.num_nodes());
  hammerblade::write_global_buffer_dma(h_ids.data(), IDs_dev, edges.num_nodes());
  hammerblade::write_global_buffer_dma(h_update.data(), update_dev, 1);
 
  std::cerr << "init locks\n";
  GlobalScalar<hb_mc_eva_t> glbl_locks = GlobalScalar<hb_mc_eva_t>("locks");
  hammerblade::init_global_array<std::atomic<int>>(NUM_LOCKS, glbl_locks);
  std::atomic<int> tmp_array[NUM_LOCKS] = {};
  hammerblade::write_global_buffer_dma<std::atomic<int>>(tmp_array, glbl_locks, NUM_LOCKS);
 
  std::cerr << "doing batch dma write" << std::endl;
  device->freeze_cores();
  device->write_dma();
  device->unfreeze_cores();

  std::vector<int>().swap(zeros);
  std::vector<int>().swap(h_frontier);
  std::vector<int>().swap(h_ids);
  std::vector<int>().swap(h_update); 

  std::cerr << "starting while loop" << std::endl;
  switch(version){
    case 0: { // do dense pull bfs
      std::cerr << "initialize IDs\n"; 
      //device->enqueueJob("init_kernel", hb_mc_dimension(X,Y), {edges.num_nodes()});
      //device->runJobs();
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
	std::cerr << "doing CC kernel" << std::endl;
        device->enqueueJob("edgeset_apply_pull_parallel_deduplicated_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getInIndicesAddr(),
                         edges.getInNeighborsAddr(),
                         next_frontier_dev.getAddr(),  
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "doing pointer jumping\n";
        int h_upd[1] = {0};
        hammerblade::read_global_buffer(h_upd, update_dev, 1);
        int tag = 1;
        while(h_upd[0] != 0) {
          hammerblade::insert_val(0, 0, update_dev);
          device->enqueueJob("pjump_kernel", hb_mc_dimension(X,Y), {edges.num_nodes(), tag});
          device->runJobs();
          hammerblade::read_global_buffer(h_upd, update_dev, 1);
          std::cerr << "finished round, h: " << h_upd[0] << std::endl;
          tag++;
        }
        std::cerr << "finished call" << std::endl;
    }
    break;
    }
    case 1: { //do sparse push blocked bfs
      std::cerr << "initialize IDs\n"; 
      //device->enqueueJob("init_kernel", hb_mc_dimension(X,Y), {edges.num_nodes()});
      //device->runJobs();
      for(int i = 0; i < 1; i++) //just doing one large iteration
      {
	std::cerr << "doing CC kernel" << std::endl;
        device->enqueueJob("edgeset_apply_push_parallel_deduplicated_with_frontier_call",
                         hb_mc_dimension(X,Y),
                        {edges.getOutIndicesAddr(),
                         edges.getOutNeighborsAddr(),
                         next_frontier_dev.getAddr(),  
                         edges.num_nodes(),
                         edges.num_edges(),
                         edges.num_nodes()});
        device->runJobs();
        std::cerr << "doing pointer jumping\n";
        int h_upd[1] = {0};
        hammerblade::read_global_buffer(h_upd, update_dev, 1);
        int tag = 1;
        while(h_upd[0] != 0) {
          hammerblade::insert_val(0, 0, update_dev);
          device->enqueueJob("pjump_kernel", hb_mc_dimension(X,Y), {edges.num_nodes(), tag});
          device->runJobs();
          hammerblade::read_global_buffer(h_upd, update_dev, 1);
          std::cerr << "finished round, h: " << h_upd[0] << std::endl;
          tag++;
        }
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
