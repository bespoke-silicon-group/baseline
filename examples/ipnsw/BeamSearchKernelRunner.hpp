#pragma once
#include "IPNSWKernelRunner.hpp"
#include "IPNSWRunner.hpp"
#include "GreedyWalkResults.hpp"

namespace ipnsw {
    class BeamSearchKernelRunner : public IPNSWKernelRunner {
        std::string kernelName(const IPNSWRunner & runner) const {
            return "ipnsw_beam_search";
        }

        std::vector<hb_mc_eva_t> argv(const IPNSWRunner & runner) const {
            int v_curr;
            float d_curr;
            v_curr = std::get<GWR_VERT>(GREEDY_WALK_RESULTS[IPNSWRunner::QUERY]);
            d_curr = std::get<GWR_DIST>(GREEDY_WALK_RESULTS[IPNSWRunner::QUERY]);

            HammerBlade::Ptr hb = HammerBlade::Get();
            hb->write(runner.v_curr_dev(0), &v_curr, sizeof(v_curr));
            hb->write(runner.d_curr_dev(0), &d_curr, sizeof(d_curr));

            std::vector<hb_mc_eva_t> argv = {
                runner.graph_metadata_dev(),
                runner.db_dev(),
                runner.query_dev(0),
                runner.seen_dev(0),
                runner.v_curr_dev(0),
                runner.d_curr_dev(0),
                runner.candidates_dev(0),
                runner.results_dev(0),
                runner.n_results_dev(0),
            };
            return argv;
        }

    };
}
