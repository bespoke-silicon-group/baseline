#include <BFSCSRGraph.hpp>
#include <bfs-common.hpp>

template <>
void BFSCSRGraph<int>::build_nodes()
{
    for (Graph::NodeID v = 0; v < _g.num_nodes(); v++) {
        _nd.push_back(static_cast<int>(_g.offset(v)));
    }
}

template <>
void BFSCSRGraph<node_data_t>::build_nodes()
{
    for (Graph::NodeID v = 0; v < _g.num_nodes(); v++) {
        node_data_t data = {
            .offset = static_cast<int>(_g.offset(v)),
            .degree = static_cast<int>(_g.degree(v)),
        };
        _nd.push_back(data);
    }
}
