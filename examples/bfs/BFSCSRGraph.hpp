#pragma once
#include <HammerBlade.hpp>
#include <Graph.hpp>
#include <BFSGraph.hpp>

template <typename NodeData>
class BFSCSRGraph : public BFSGraph {
public:
    BFSCSRGraph(Graph &g) : BFSGraph(g) {}

private:
    void build_edges() {
        for (Graph::NodeID e = 0; e < _g.num_edges(); e++)
            _ed.push_back(static_cast<int>(_g.get_neighbors()[e]));
    }
    void build_nodes();

public:
    void build() {
        build_nodes();
        build_edges();
    }

private:
public:
    void alloc() {
        _edge_dev = _hb->alloc(sizeof(_ed[0]) * _ed.size());
        _node_dev = _hb->alloc(sizeof(_nd[0]) * _nd.size());
    }
    void write() {
        _hb->push_write(_edge_dev, &_ed[0], sizeof(_ed[0]) * _ed.size());
        _hb->push_write(_node_dev, &_nd[0], sizeof(_nd[0]) * _nd.size());
    }

private:
    std::vector<NodeData> _nd;
    std::vector<int> _ed;
};
