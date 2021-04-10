#pragma once
#include <HammerBlade.hpp>

struct graph {
    int V;
    int E;
    hb_mc_eva_t offsets;
    hb_mc_eva_t neighbors;
    hb_mc_eva_t weights;
};

class DijkstraGraph {
public:
    hb_mc_eva_t MetaData() const { return _meta_data; }
    hb_mc_eva_t& MetaData() { return _meta_data; }
    hb_mc_eva_t Offsets() const  { return _md.offsets; }
    hb_mc_eva_t& Offsets()  { return _md.offsets; }
    hb_mc_eva_t Neighbors() const { return _md.neighbors; }
    hb_mc_eva_t& Neighbors() { return _md.neighbors; }
    hb_mc_eva_t Weights() const { return _md.weights; }
    hb_mc_eva_t& Weights() { return _md.weights; }
    int V() const { return _md.V; }
    int& V(){ return _md.V; }
    int E() const { return _md.E; }
    int& E() { return _md.E; }

    DijkstraGraph(){}

    void InitializeWithWGraph(const graph_tools::WGraph &g) {
        using hammerblade::host::HammerBlade;
        
        HammerBlade::Ptr hb = HammerBlade::Get();
        _g = g;

        Offsets() = hb->alloc(_g.num_nodes() * sizeof(int));
        hb->push_write(Offsets(), &_g.get_offsets()[0], _g.num_nodes() * sizeof(int));

        Neighbors() = hb->alloc(_g.num_edges() * sizeof(int));
        hb->push_write(Neighbors(), &_g.get_neighbors()[0], _g.num_edges() * sizeof(int));

        Weights() = hb->alloc(_g.num_edges() * sizeof(float));
        hb->push_write(Weights(), &_g.get_weights()[0], _g.num_edges() * sizeof(float));

        V() = _g.num_nodes();
        E() = _g.num_edges();        
        MetaData() = hb->alloc(sizeof(struct graph));
        hb->push_write(MetaData(), &_md, sizeof(struct graph));
    }
    
private:
    hb_mc_eva_t _meta_data;
    struct graph _md;
    graph_tools::WGraph _g;
};
