#pragma once

struct graph {
    int V;
    int E;
    int *offsets;
    int *neighbors;
    float *weights;
};
