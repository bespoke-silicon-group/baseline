#pragma once
#include <HammerBlade.hpp>
#include <Graph.hpp>
#include <BFSGraph.hpp>
#include <BFSVertexSet.hpp>

class BFSApp {
public:
    using HammerBlade = hammerblade::host::HammerBlade;
    using Graph = graph_tools::Graph;
    using BFS = graph_tools::BFS;

    BFSApp(const char *binpath) :
        _hb(HammerBlade::Get()) {
        _hb->load_application(binpath);
    }

    BFSGraph::Ptr & graph() { return _bfs_g; }
    BFSVertexSet::Ptr &active_i() { return _active_i; }
    BFSVertexSet::Ptr &active_o() { return _active_o; }
    BFSVertexSet::Ptr &visited_io() { return _visited_io; }
    std::string & kernel_name() { return _kernel_name; }

    void run() {
        _hb->freeze_tiles();
        _hb->sync_write();
        _hb->unfreeze_tiles();

        std::cout << kernel_name() << "("
                  << graph()->num_nodes() << ","
                  << graph()->num_edges() << ","
                  << std::hex << graph()->nodes_dev() << ","
                  << std::hex << graph()->edges_dev() << ","
                  << std::hex << _active_i->dev() << ","
                  << std::hex << _active_o->dev() << ","
                  << std::hex << _visited_io->dev() << ")"
                  << std::dec << std::endl;

        _hb->push_job(kernel_name(),
                      graph()->num_nodes(),
                      graph()->num_edges(),
                      graph()->nodes_dev(),
                      graph()->edges_dev(),
                      _active_i->dev(),
                      _active_o->dev(),
                      _visited_io->dev());
        _hb->exec();
    }

    void build(){
        _bfs_g->build();
        _active_i->build();
        _active_o->build();
        _visited_io->build();
    }

    void write() {
        _bfs_g->write();
        _active_i->write();
        _visited_io->write();
    }

    void alloc() {
        _bfs_g->alloc();
        _active_i->alloc();
        _active_o->alloc();
        _visited_io->alloc();
    }

    void read() {
        _active_o->read();
        _visited_io->read();
    }

    void init() {
        build();
        alloc();
        write();
    }

    void finish() {
        read();
        _hb->freeze_tiles();
        _hb->sync_read();
        _hb->unfreeze_tiles();

        for (int i = 0; i < _bfs_g->num_nodes(); i++) {
            std::cout << "active_o[" << i << "] = " << _active_o->vec()[i] << std::endl;
        }
        for (int i = 0; i < _bfs_g->num_nodes(); i++) {
            std::cout << "visited[" << i << "] = " << _visited_io->vec()[i] << std::endl;
        }
    }

private:
    BFSGraph::Ptr _bfs_g;
    BFSVertexSet::Ptr _active_i;
    BFSVertexSet::Ptr _active_o;
    BFSVertexSet::Ptr _visited_io;
    HammerBlade::Ptr  _hb;
    std::string _kernel_name;
};
