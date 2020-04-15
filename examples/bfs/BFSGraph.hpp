#pragma once
#include <HammerBlade.hpp>
#include <Graph.hpp>

class BFSGraph {
public:
    using HammerBlade = hammerblade::host::HammerBlade;
    using Graph = graph_tools::Graph;

    using Ptr = BFSGraph*;
    using CPtr = const BFSGraph*;
public:
    BFSGraph(Graph &g) : _hb(HammerBlade::Get()), _g(g) {}

public:
    virtual void build() = 0;
    virtual void alloc() = 0;
    virtual void write() = 0;

    hb_mc_eva_t edges_dev() const { return _edge_dev; }
    hb_mc_eva_t nodes_dev() const { return _node_dev; }

    int num_nodes() const { return static_cast<int>(_g.num_nodes()); }
    int num_edges() const { return static_cast<int>(_g.num_edges()); }

protected:
    HammerBlade::Ptr _hb;
    hb_mc_eva_t _edge_dev;
    hb_mc_eva_t _node_dev;
    Graph & _g;
};
