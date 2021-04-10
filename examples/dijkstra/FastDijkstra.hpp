#pragma once
#include <WGraph.hpp>
#include <queue>
#include <vector>
#include <string>
#include <iostream>

class FastDijkstra {
public:
    using WGraph = graph_tools::WGraph;
    FastDijkstra(const WGraph &wg, int root, int goal) :
        _wg(wg.transpose()),
        _root(root),
        _goal(goal),
        _traversed_edges(0),
        _fp_compares(0),
        _fp_adds(0) {}


    std::pair<std::vector<int>, std::vector<float>>
    run() {
        _distance.clear();
        _path.clear();
        _distance.resize(_wg.num_nodes(), INFINITY);
        _path.resize(_wg.num_nodes(),-1);

        std::vector<bool> changed(false);
        _distance[_root] = 0.0;
        _path[_root] = _root;
        _changed[_root] = true;
        
        
        auto cmp = [&](int lhs, int rhs){ return distance[lhs] > distance[rhs]; }
        std::priority_queue<int> queue;
        queue.push(root);

        while (!queue.empty()) {
            // approx. deletion with O(logN)
            _fp_compares += log2(queue.size());
            int src = queue.pop();
            if (src == _goal)
                break;

            auto wneib = _wg.wneighbors(src);
            for (auto &pair : wneib) {
                int dst = pair.first;
                float w = pair.second;
                if (_distance[src]+w < _distance[dst]) {
                    _path[dst] = src;
                    _distance[dst] = _distance[src]+w;
                    // approx. insertion with O(logN)
                    _fp_compares += log2(queue.size());
                }
                _fp_adds += 1;
                _fp_compares += 1;
                _traversed_edges += 1;
            }
        }

        // find a node with the greatest distance from the root that's not infinity
        int maxv = _root;        
        for (int v = 0; v < _wg.num_nodes(); v++) {
            if ((_distance[v] > _distance[maxv]) && !std::isinf(_distance[v])) {
#ifdef DEBUG_DIJKSTRA_HOST
                printf("distance[v]=%f,distance[maxv]=%f,isinf(%f)=%d\n",
                       _distance[v], _distance[maxv], _distance[maxv], std::isinf(_distance[v]));
#endif
                maxv = v;
            }
        }

        _goal = maxv;
        
        return {_path, _distance};
    }

    int goal() const { return _goal; }
    std::vector<float> & distance() { return _distance; }
    std::vector<int>   & path() { return _path; }
    std::vector<float> distance() const { return _distance; }
    std::vector<int>   path() const { return _path; }
        
    void stats(const std::string &fname) const {
        std::ofstream of(fname);
        of << "nodes:                 " << _wg.num_nodes() << "\n";
        of << "edges:                 " << _wg.num_edges() << "\n";
        of << "root:                  " << _root << "\n";
        of << "goal:                  " << _goal << "\n";
        of << "traversed edges:       " << _traversed_edges << "\n";
        of << "fp compares:           " << _fp_compares << "\n";
        of << "fp adds:               " << _fp_adds << "\n";
        of << "fp total:              " << _fp_compares+_fp_adds << "\n";
        of << "fp total analytical:   " << 2 * (_wg.num_nodes()-1) * _wg.num_edges() << "\n";
        of << "distance (root->goal): " << _distance[_goal] << "\n";
    }

private:
    WGraph _wg;
    int    _root;
    int    _goal;
    int    _traversed_edges;
    float  _fp_compares;
    float  _fp_adds;
    std::vector<float> _distance;
    std::vector<int>   _path;
};
