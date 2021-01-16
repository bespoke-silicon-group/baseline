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
            r0 = fmaf(a[i+j+0*BSIZE], b[i+j+0*BSIZE], r0);
            r1 = fmaf(a[i+j+1*BSIZE], b[i+j+1*BSIZE], r1);
        }
    }
    return r0+r1;
}

template<std::size_t TG_X, std::size_t TG_Y, typename FLOAT_T=float, std::size_t VSIZE=100, std::size_t BSIZE=5>
__attribute__((noinline))
FLOAT_T inner_product_v4(const FLOAT_T *__restrict a,
                         bsg_attr_remote const FLOAT_T *__restrict b)
{
    FLOAT_T r0 = 0.0, r1 = 0.0;
    FLOAT_T r2 = 0.0, r3 = 0.0;
    for (int i = __bsg_id * BSIZE; i < VSIZE; i += 4 * BSIZE * TG_X * TG_Y) {
#pragma bsg_unroll(32)
        for (int j = 0; j < BSIZE; ++j) {
            r0 = fmaf(a[i+j+0*BSIZE], b[i+j+0*BSIZE], r0);
            r1 = fmaf(a[i+j+1*BSIZE], b[i+j+1*BSIZE], r1);
            r2 = fmaf(a[i+j+2*BSIZE], b[i+j+2*BSIZE], r2);
            r3 = fmaf(a[i+j+3*BSIZE], b[i+j+3*BSIZE], r3);
        }
    }
    return r0+r1+r2+r3;
}
