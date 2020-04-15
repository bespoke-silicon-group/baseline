#pragma once
#include <HammerBlade.hpp>
#include <Graph.hpp>
#include <set>
class BFSVertexSet {
public:
    using HammerBlade = hammerblade::host::HammerBlade;
    using Graph = graph_tools::Graph;
    using Ptr = BFSVertexSet*;
    using CPtr = const BFSVertexSet*;

public:
    BFSVertexSet(int N, const std::set<Graph::NodeID> &set) :
        _hb(HammerBlade::Get()),
        _N(N),
        _set(set),
        _vec(N) {}

    virtual void build() = 0;
    void alloc() {
        _dev = _hb->alloc(bytes());
    }
    void write() {
        _hb->push_write(_dev, &_vec[0], bytes());
    }
    void read() {
        _hb->push_read(_dev, &_vec[0], bytes());
    }

    size_t bytes() const { return sizeof(_vec[0]) * _N; }
    hb_mc_eva_t dev() const { return _dev; }

    std::vector<int> & vec() { return _vec; }

protected:
    HammerBlade::Ptr _hb;
    hb_mc_eva_t _dev;
    int _N;
    std::set<Graph::NodeID> _set;
    std::vector<int> _vec;
};
