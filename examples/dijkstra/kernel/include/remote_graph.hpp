#pragma once
#include <bsg_manycore.h>

struct graph {
    int V;
    int E;
    bsg_attr_remote int *__restrict offsets;
    bsg_attr_remote int *__restrict neighbors;
    bsg_attr_remote float *__restrict weights;
};
