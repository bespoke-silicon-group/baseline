//function to compute pr-nibble on host up to current iter

inline void host_pr_calc(std::vector<double> & p, std::vector<double> & old_rank, std::vector<double> & new_rank, std::vector<int> & frontier, int iter) {
    double alpha = 0.15;
    double epsilon = 1e-06;
    auto g = edges.getHostGraph();
    int * in_neigh = g.in_neighbors_shared_.get();
    int ** in_index = g.in_index_shared_.get();
    for(int i = 0; i < iter; i++) {
        //std::memcpy(new_rank, old_rank, sizeof(double)*edges.num_nodes());
	    new_rank = old_rank;
        //print out iteration and size:
        int num_items = std::count(frontier.begin(), frontier.end(), 1);
        std::cerr << "on iteration: " << i << " with frontier size: " << num_items << std::endl;
        //update_self
        for(int v = 0; v < g.num_nodes(); v++) {
            p[v] = (p[v] + ((((2)  * alpha) / ((1)  + alpha)) * old_rank[v]));
    new_rank[v] = (0) ;
        }
        //update edges
        for(int d = 0; d < g.num_nodes(); d++) {
            int ind = in_index[d] - in_neigh;
            int degree = g.in_degree(d);
            int * neighbors = &in_neigh[ind];
            for(int s = 0; s < degree; s++){
                auto src = neighbors[s];
                if(frontier[src]){
                    new_rank[d] = (new_rank[d] + (((((1)  - alpha) / ((1)  + alpha)) * old_rank[src]) / g.out_degree(src)));
                }
            }
        }
        //old_rank.swap(new_rank);
        //std::memcpy(old_rank, new_rank, sizeof(double)*edges.num_nodes());
        old_rank = new_rank;
        //update frontier
        for(int v = 0; v < g.num_nodes(); v++) {
            frontier[v] = 0;
            if(g.out_degree(v) > 0 && old_rank[v] > (g.out_degree(v) * epsilon)) {
                frontier[v] = 1;
            }
        }
    }
    int num_items = std::count(frontier.begin(), frontier.end(), 1);
    std::cerr << "returning with frontier size: " << num_items << std::endl;
}
