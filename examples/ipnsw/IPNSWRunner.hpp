#pragma once
#include "IO.hpp"
#include "HammerBlade.hpp"
#include "IPNSWGraph.hpp"
#include <memory>

namespace ipnsw {

    class IPNSWRunner {
    public:
        static constexpr int QUERY = 276;
        using HammerBlade = hammerblade::host::HammerBlade;
        using Dim = hammerblade::host::Dim;

        IPNSWRunner(const Parser &p, std::unique_ptr<IPNSWKernelRunner> & kr):
            _kernel_runner(std::move(kr)) {
            _io = std::unique_ptr<IO>(new IO(p));
            _hb = HammerBlade::Get();
        }

        virtual ~IPNSWRunner() { delete _hb; }

        void readInput() {
            auto graphs   = _io->graphs();
            _graphs = {
                Graph(std::move(graphs[3])),
                Graph(std::move(graphs[2])),
                Graph(std::move(graphs[1])),
                Graph(std::move(graphs[0]))
            };

            _db       = _io->database<float,100>();
            _queries  = _io->queries<float,100>();
        }

        void loadProgram() {
            _hb->load_application(ucodePath());
        }

        void initializeDeviceMemoryDB() {
            std::cout << "Initializing database " << std::endl;
            _db_dev = _hb->alloc(_db.size() * sizeof(_db[0]));
            _hb->push_write(_db_dev, &_db[0], _db.size() * sizeof(_db[0]));
        }

        void initializeDeviceMemoryQuery() {
            std::cout << "Initializing query "  << std::endl;
            _query_dev = _hb->alloc(sizeof(_queries[QUERY]));
            _hb->push_write(_query_dev, &_queries[QUERY], sizeof(_queries[QUERY]));
        }

        void initializeDeviceMemorySeen() {
            std::cout << "Initializing seen set " << std::endl;
            _seen_dev = _hb->alloc(sizeof(_db.size() * sizeof(int)));
        }

        void initializeDeviceMemoryGraphs() {
            for (auto & graph : _graphs)
                graph.initialize_on_device();

            _graph_metadata_dev = Graph::InitializeMetadataOnDevice(_graphs);
        }

        void initializeDeviceVCurr() {
            _v_curr_dev = _hb->alloc(sizeof(int));
        }
        void initializeDeviceDCurr() {
            _d_curr_dev = _hb->alloc(sizeof(float));
        }

        void initializeDeviceMemory() {
            initializeDeviceMemoryDB();
            initializeDeviceMemoryQuery();
            initializeDeviceMemorySeen();
            initializeDeviceMemoryGraphs();
            initializeDeviceVCurr();
            initializeDeviceDCurr();
            // sync
            std::cout << "Starting DMA" << std::endl;
            _hb->sync_rw();
        }

        void runKernel() {
            std::cout << "Launching kernel" << std::endl;
            _kernel_runner->runKernel(*this);
        }

        void reportResults() {
            int v_curr;
            float d_curr;

            _hb->read(_v_curr_dev, &v_curr, sizeof(int));
            _hb->read(_d_curr_dev, &d_curr, sizeof(float));

            std::cout << "Greedy walk (v_curr,d_curr) = "
                      << "(" << v_curr << "," << d_curr << ")"
                      << std::endl;
        }

        void run() {
            readInput();
            loadProgram();
            initializeDeviceMemory();
            runKernel();
            reportResults();
        }

        /////////////
        // Getters //
        /////////////
        std::string ucodePath() const {
            return _io->ucode();
        }

        hb_mc_eva_t db_dev() const { return _db_dev; }
        hb_mc_eva_t query_dev() const { return _query_dev; }
        hb_mc_eva_t seen_dev() const { return _seen_dev; }
        hb_mc_eva_t v_curr_dev() const { return _v_curr_dev; }
        hb_mc_eva_t d_curr_dev() const { return _d_curr_dev; }
        hb_mc_eva_t graph_metadata_dev() const { return _graph_metadata_dev; }


        /////////////
        // Setters //
        /////////////

    private:
        std::unique_ptr<IO>                  _io;
        std::vector<Graph>                   _graphs;
        std::vector<std::array<float, 100>>  _db;
        std::vector<std::array<float, 100>>  _queries;
        HammerBlade::Ptr                     _hb;

        // device pointers
        hb_mc_eva_t _db_dev;
        hb_mc_eva_t _query_dev;
        hb_mc_eva_t _seen_dev;
        hb_mc_eva_t _v_curr_dev;
        hb_mc_eva_t _d_curr_dev;
        hb_mc_eva_t _graph_metadata_dev;

        // composites
        std::unique_ptr<IPNSWKernelRunner> _kernel_runner;
    };


    class GreedyWalkKernelRunner : public IPNSWKernelRunner {
        std::string kernelName(const IPNSWRunner & runner) const {
            return "ipnsw_greedy_search";
        }

        std::vector<hb_mc_eva_t> argv(const IPNSWRunner & runner) const {
            std::vector<hb_mc_eva_t> argv = {
                runner.graph_metadata_dev(),
                runner.db_dev(),
                runner.query_dev(),
                runner.seen_dev(),
                runner.v_curr_dev(),
                runner.d_curr_dev(),
            };
            return argv;
        };
        Dim gd(const IPNSWRunner &runner) const {return Dim(1,1);}
        Dim tgd(const IPNSWRunner &runner) const {return Dim(1,1);}
    };

    class IProductUBmkKernelRunner : public IPNSWKernelRunner {
        IProductUBmkKernelRunner(int iterations) :
            IPNSWKernelRunner(),
            _iterations(iterations) {
        }

        std::string kernelName(const IPNSWRunner & runner, int iterations=100) const {
            return "inner_product_ubmk";
        }

        std::vector<hb_mc_eva_t> argv(const IPNSWRunner & runner) const {
            std::vector<hb_mc_eva_t> argv = {
                runner.db_dev(), // database
                runner.query_dev(), // query
                100, // number of inner products
            };
            return argv;
        };
        Dim gd(const IPNSWRunner &runner) const {return Dim(1,1);}
        Dim tgd(const IPNSWRunner &runner) const {return Dim(1,1);}

        int _iterations;
    };
}
