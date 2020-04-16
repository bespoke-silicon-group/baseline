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

protected:
    std::set<Graph::NodeID> set_from_vec() const {
        std::set<Graph::NodeID> rset;
        for (int i = 0; i < vec().size(); i++) {
            if (vec()[i] == 1)
                rset.insert(static_cast<Graph::NodeID>(i));
        }
        return rset;
    }
};
