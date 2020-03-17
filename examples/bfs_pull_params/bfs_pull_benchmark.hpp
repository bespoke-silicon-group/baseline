#ifndef __BFS_PULL_BENCHMARK_HPP
#define __BFS_PULL_BENCHMARK_HPP

#include "builtins_hammerblade.h"
#include <string.h>
#include <stdio.h>
#include "../common.h"

const std::string ucode_path =
        "/nbu/spin/eafurst/bsg_bladerunner/baseline"
        "/examples/bfs_pull_params/kernel.riscv";

using hammerblade::Device;
using hammerblade::Vector;
using hammerblade::GraphHB;
using hammerblade::GlobalScalar;

#endif
