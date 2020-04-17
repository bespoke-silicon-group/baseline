#pragma once
#include <HammerBlade.hpp>
#include <Graph.hpp>
#include <BFSGraph.hpp>
#include <BFSCSRGraph.hpp>
#include <bfs-common.hpp>

template <int NODE_BLOCK_SIZE, int EDGE_BLOCK_SIZE, int PADDING=-1>
class BFSBlockedCSRGraph : public BFSCSRGraph<node_data_t> {
public:
    BFSBlockedCSRGraph(Graph &g) :
        BFSCSRGraph<node_data_t>(g) {
        _v_blocks
            = num_nodes()/NODE_BLOCK_SIZE
            + (num_nodes()%NODE_BLOCK_SIZE == 0 ? 0 : 1);
        _e_blocks
            = num_edges()/EDGE_BLOCK_SIZE
            + (num_edges()%EDGE_BLOCK_SIZE == 0 ? 0 : 1);
    }

protected:
    void build_nodes() {
        // we build the node data with the edge data
    }

    void build_edges() {
        for (Graph::NodeID v = 0; v < _g.num_nodes(); v++) {
            // we want the edges for each vertex block to be aligned
            // thought: maybe this only needs to be cache aligned?
            if (v % NODE_BLOCK_SIZE == 0)
                while (_ed.size() % EDGE_BLOCK_SIZE != 0)
                    _ed.push_back(PADDING);

            // push the offset
            node_data_t node = {
                .offset = static_cast<int>(_ed.size()),
                .degree = static_cast<int>(_g.degree(v))
            };
            _nd.push_back(node);

            // push back the neighbors of v
            for (Graph::NodeID dst : _g.neighbors(v))
                _ed.push_back(dst);
        }

    }
private:
    int _v_blocks;
    int _e_blocks;
};
