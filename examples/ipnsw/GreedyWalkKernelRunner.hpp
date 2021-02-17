#pragma once
#include "IPNSWKernelRunner.hpp"
#include "IPNSWRunner.hpp"

namespace ipnsw {
    class GreedyWalkKernelRunner : public IPNSWKernelRunner {
        std::string kernelName(const IPNSWRunner & runner) const {
            return "ipnsw_greedy_search";
        }

        std::vector<hb_mc_eva_t> argv(const IPNSWRunner & runner) const {
            std::vector<hb_mc_eva_t> argv = {
                runner.graph_metadata_dev(),
                runner.db_dev(),
                runner.query_dev(0),
                runner.seen_dev(0),
                runner.v_curr_dev(0),
                runner.d_curr_dev(0),
            };
            return argv;
        }

    };
}
