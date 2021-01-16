#pragma once
#include "bsg_striped_array.hpp"
#include <cmath>

template<std::size_t TG_X, std::size_t TG_Y, typename FLOAT_T=float, std::size_t VSIZE=100, std::size_t BSIZE=10>
__attribute__((noinline))
FLOAT_T inner_product(const FLOAT_T *__restrict a, const FLOAT_T *__restrict b)
{
    FLOAT_T r = 0.0;
    for (int i = __bsg_id * BSIZE; i < VSIZE; i += BSIZE * TG_X * TG_Y) {
        #pragma GCC unroll 32
        for (int j = 0; j < BSIZE; ++j) {
            r += a[i + j]*b[i + j];
        }
    }
    return r;
}


template<std::size_t TG_X, std::size_t TG_Y, typename FLOAT_T=float, std::size_t VSIZE=100, std::size_t BSIZE=10>
__attribute__((noinline))
FLOAT_T inner_product_v1(const FLOAT_T *__restrict a,
                         bsg_attr_remote const FLOAT_T *__restrict b)
{
    FLOAT_T r = 0.0;
    for (int i = __bsg_id * BSIZE; i < VSIZE; i += BSIZE * TG_X * TG_Y) {
        #pragma GCC unroll 32
        for (int j = 0; j < BSIZE; ++j) {
            r += a[i + j]*b[i + j];
        }
    }
    return r;
}


template<std::size_t TG_X, std::size_t TG_Y, typename FLOAT_T=float, std::size_t VSIZE=100, std::size_t BSIZE=10>
__attribute__((noinline))
FLOAT_T inner_product_v2(const FLOAT_T *__restrict a,
                         bsg_attr_remote const FLOAT_T *__restrict b)
{
    FLOAT_T r = 0.0;
    for (int i = __bsg_id * BSIZE; i < VSIZE; i += BSIZE * TG_X * TG_Y) {
        #pragma GCC unroll 32
        for (int j = 0; j < BSIZE; ++j) {
            r = fmaf(a[i+j], b[i+j], r);
        }
    }
    return r;
}



template<std::size_t TG_X, std::size_t TG_Y, typename FLOAT_T=float, std::size_t VSIZE=100, std::size_t BSIZE=10>
__attribute__((noinline))
FLOAT_T inner_product_v3(const FLOAT_T *__restrict a,
                         bsg_attr_remote const FLOAT_T *__restrict b)
{
    FLOAT_T r0 = 0.0, r1 = 0.0;
    for (int i = __bsg_id * BSIZE; i < VSIZE; i += 2 * BSIZE * TG_X * TG_Y) {
#pragma bsg_unroll(32)
        for (int j = 0; j < BSIZE; ++j) {
            r0 = fmaf(a[i+j], b[i+j], r0);
            r1 = fmaf(a[i+j+BSIZE], b[i+j+BSIZE], r1);
        }
    }
    return r0+r1;
}
