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

    void alloc() {
        _edge_dev = _hb->alloc(edge_bytes());
        _node_dev = _hb->alloc(node_bytes());
    }
    void write() {
        _hb->push_write(_edge_dev, &_ed[0], edge_bytes());
        _hb->push_write(_node_dev, &_nd[0], node_bytes());
    }

    size_t node_bytes() const { return sizeof(_nd[0]) * _nd.size(); }
    size_t edge_bytes() const { return sizeof(_ed[0]) * _ed.size(); }
private:
    std::vector<NodeData> _nd;
    std::vector<int> _ed;
};
