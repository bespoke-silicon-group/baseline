#pragma once
#include <BFSVertexSet.hpp>
class BFSDenseVertexSet : public BFSVertexSet {
public:
    BFSDenseVertexSet(int N, const std::set<Graph::NodeID> &set):
        BFSVertexSet(N, set) {
        _vec.clear();
        _vec.resize(_N, 0);
    }
    void build() {
        for (int v : _set)
            _vec[v] = 1;
    }
};
