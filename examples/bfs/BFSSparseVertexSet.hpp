#pragma once
#include <BFSVertexSet.hpp>
#include <sstream>

class BFSSparseVertexSet : public BFSVertexSet {
public:
    BFSSparseVertexSet(int N, const std::set<Graph::NodeID> &set) :
        BFSVertexSet(N, set) {
        _vec.clear();
        _vec.resize(_N, -1);
    }

    void build () {
        int i = 0;
        for (int v : _set) {
            _vec[i++] = v;
        }
    }

    std::string string() const {
        std::stringstream ss;
        ss <<  "{ " ;
        for (int i : _vec) ss << i << ", ";
        ss << "}";
        return ss.str();
    }

protected:
    std::set<Graph::NodeID> set_from_vec() const {
        std::set<Graph::NodeID> rset;
        for (int i = 0; i < vec().size(); i++) {
            int v = vec()[i];
            if (v == -1) break;
            rset.insert(static_cast<Graph::NodeID>(v));
        }
        return rset;
    }
};
