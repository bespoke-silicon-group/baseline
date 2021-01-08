#pragma once
#include "bsg_striped_array.hpp"

#if 1
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
#else
template<std::size_t TG_X, std::size_t TG_Y, typename FLOAT_T=float, std::size_t VSIZE=100, std::size_t BSIZE=10>
//__attribute__((noinline))
FLOAT_T inner_product(const FLOAT_T *__restrict a, const FLOAT_T *__restrict b)
{
    FLOAT_T r = 0.0;
    for (int i = 0; i < VSIZE; ++i)
        r += a[i]*b[i];

    return r;
}
#endif
