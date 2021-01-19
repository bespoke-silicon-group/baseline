#pragma once
#include "HammerBlade.hpp"
#include <memory>
#include <string>
namespace ipnsw {
    class IPNSWRunner; // forward declaration

    class IPNSWKernelRunnerConfig {
    public:
        using Dim = hammerblade::host::Dim;

        IPNSWKernelRunnerConfig():
            _gd(Dim(1,1)),
            _tgd(Dim(1,1)) {}

        Dim gridDim() const { return _gd; }
        Dim &gridDim() { _gd; }

        Dim groupDim() const { return _tgd; }
        Dim & groupDim() { return _tgd; }

    private:
        Dim _gd;
        Dim _tgd;
    };

    class IPNSWKernelRunner {
    public:
        using HammerBlade = hammerblade::host::HammerBlade;
        using Dim = hammerblade::host::Dim;
        IPNSWKernelRunner():IPNSWKernelRunner(IPNSWKernelRunnerConfig()) {}
        IPNSWKernelRunner(const IPNSWKernelRunnerConfig &cfg) : _cfg(cfg) {}

    protected:
        virtual std::string kernelName(const IPNSWRunner & runner) const =0;
        virtual std::vector<hb_mc_eva_t> argv(const IPNSWRunner & runner) const =0;

    public:
        virtual Dim gd(const IPNSWRunner &runner) const { return _cfg.gridDim(); }
        virtual Dim tgd(const IPNSWRunner &runner) const { return _cfg.groupDim(); }

    public:
        void runKernel(IPNSWRunner &runner) {
            HammerBlade::Ptr hb = HammerBlade::Get();
            hb->push_jobv(gd(runner),
                          tgd(runner),
                          kernelName(runner),
                          argv(runner));
            hb->exec();
        }

    protected:
        IPNSWKernelRunnerConfig _cfg;
    };

}
