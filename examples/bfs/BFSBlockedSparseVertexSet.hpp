#pragma once
#include <BFSVertexSet.hpp>
#include <sstream>
#include <string>

template <int BLOCK_SIZE>
class BFSBlockedSparseVertexSet : public BFSVertexSet {
public:
    BFSBlockedSparseVertexSet(int N, const std::set<Graph::NodeID> &set) :
        BFSVertexSet(N, set),
        _block_pop((N/BLOCK_SIZE)+1, 0) {
        _vec.clear();
        _vec.resize(_N, -1);
    }

    void build () {
        for (int v : _set) {
            int b = block_of(v);
            _vec[b*BLOCK_SIZE + _block_pop[b]++] = v;
        }
        std::cout << string() << std::endl;
    }

protected:
    std::set<Graph::NodeID> set_from_vec() const {
        std::set<Graph::NodeID> rset;
        int nblocks = _N/BLOCK_SIZE + (_N%BLOCK_SIZE == 0 ? 0 : 1);
        for (int blk = 0; blk < nblocks; blk++) {
            int blk_off = blk * BLOCK_SIZE;
            for (int i = 0; i < BLOCK_SIZE; i++) {
                int v = vec()[i];
                if (v == -1)
                    break;
                rset.insert(static_cast<Graph::NodeID>(v));
            }
        }
        return rset;
    }

private:
    int block_of(int v) const {
        return v / BLOCK_SIZE;
    }

    std::string string() const {
        std::stringstream ss;
        ss <<  "{ " ;
        for (int i : _vec) ss << i << ", ";
        ss << "}";
        return ss.str();
    }

    std::vector<int> _block_pop;
};
