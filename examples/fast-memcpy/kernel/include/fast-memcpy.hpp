#pragma once
#include <cstdint>
#include <cstring>
#include <bsg_manycore.h>
namespace {

        template <unsigned int FACTOR>
        void *__bsg_memcpy(void *dest,
                           const void *src,
                           const size_t n){

                const float *psrc  asm ("x10") = reinterpret_cast<const float *>(src);
                uint32_t src_nelements = n / sizeof(psrc[0]);
                float *pdest asm ("x12") = reinterpret_cast<float *>(dest);

                for(int j = 0; j < src_nelements; j+= FACTOR){
                        float rtemp[FACTOR];
#pragma GCC unroll 32
                        for(int f = 0; f < FACTOR; f++){
                                asm volatile ("flw %0,%1" : "=f" (rtemp[f]) : "m" (psrc[f]));
                        }

                        // Write
#pragma GCC unroll 32
                        for(int f = 0; f < FACTOR; f++){
                                asm volatile ("fsw %1,%0" : "=m" (pdest[f]) : "f" (rtemp[f]));
                        }
                        psrc += FACTOR;
                        pdest += FACTOR;
                }
                return dest;
        }

        template <int BLOCK_SIZE, int CACHE_LINE_WORDS>
        void block_memcpy_unrolled(long int *dst, const long int *src);

        template <>
        void block_memcpy_unrolled<32, 32>(long int *dst, const long int *src)
        {
                static constexpr int CACHE_LINE_WORDS = 32;
                for (int i = 0; i < 4; i++) {
                        dst[0 + i*8] = src[0 + i*8];
                        dst[1 + i*8] = src[1 + i*8];
                        dst[2 + i*8] = src[2 + i*8];
                        dst[3 + i*8] = src[3 + i*8];
                        dst[4 + i*8] = src[4 + i*8];
                        dst[5 + i*8] = src[5 + i*8];
                        dst[6 + i*8] = src[6 + i*8];
                        dst[7 + i*8] = src[7 + i*8];
                }
        }


        template <>
        void block_memcpy_unrolled<64, 32>(long int *dst, const long int *src)
        {
                static constexpr int CACHE_LINE_WORDS = 32;

                for (int i = 0; i < CACHE_LINE_WORDS; i++) {
                        dst[i + 0 * CACHE_LINE_WORDS] = src[i + 0 * CACHE_LINE_WORDS];
                        dst[i + 1 * CACHE_LINE_WORDS] = src[i + 1 * CACHE_LINE_WORDS];
                }
        }

        template <>
        void block_memcpy_unrolled<128, 32>(long int *dst, const long int *src)
        {
                static constexpr int CACHE_LINE_WORDS = 32;

                for (int i = 0; i < CACHE_LINE_WORDS; i++) {
                        dst[i + 0 * CACHE_LINE_WORDS] = src[i + 0 * CACHE_LINE_WORDS];
                        dst[i + 1 * CACHE_LINE_WORDS] = src[i + 1 * CACHE_LINE_WORDS];
                        dst[i + 2 * CACHE_LINE_WORDS] = src[i + 2 * CACHE_LINE_WORDS];
                        dst[i + 3 * CACHE_LINE_WORDS] = src[i + 3 * CACHE_LINE_WORDS];
                }
        }


        template<>
        void block_memcpy_unrolled<256, 32>(long int *dst, const long int *src)
        {
                static constexpr int CACHE_LINE_WORDS = 32;

                for (int i = 0; i < CACHE_LINE_WORDS; i++) {
                        dst[i + 0 * CACHE_LINE_WORDS] = src[i + 0 * CACHE_LINE_WORDS];
                        dst[i + 1 * CACHE_LINE_WORDS] = src[i + 1 * CACHE_LINE_WORDS];
                        dst[i + 2 * CACHE_LINE_WORDS] = src[i + 2 * CACHE_LINE_WORDS];
                        dst[i + 3 * CACHE_LINE_WORDS] = src[i + 3 * CACHE_LINE_WORDS];
                        dst[i + 4 * CACHE_LINE_WORDS] = src[i + 4 * CACHE_LINE_WORDS];
                        dst[i + 5 * CACHE_LINE_WORDS] = src[i + 5 * CACHE_LINE_WORDS];
                        dst[i + 6 * CACHE_LINE_WORDS] = src[i + 6 * CACHE_LINE_WORDS];
                        dst[i + 7 * CACHE_LINE_WORDS] = src[i + 7 * CACHE_LINE_WORDS];
                }
        }

        template <int BLOCK_SIZE, int CACHE_LINE_WORDS>
        void fast_memcpy_unrolled(long int *dst, const long int *src, long int length)
        {
                long int block [BLOCK_SIZE];
                int blocks
                        = length/BLOCK_SIZE
                        + (length%BLOCK_SIZE == 0 ? 0 : 1);

                for (int b_i = bsg_id; b_i < blocks; b_i += (bsg_tiles_X * bsg_tiles_Y)) {
                        block_memcpy_unrolled<BLOCK_SIZE, CACHE_LINE_WORDS>(block, &src[b_i*BLOCK_SIZE]);
                        block_memcpy_unrolled<BLOCK_SIZE, CACHE_LINE_WORDS>(&dst[b_i*BLOCK_SIZE], block);
                }
        }

        template<int BLOCK_SIZE>
        void fast_memcpy(long int *dst, const long int *src, long int length)
        {
                long int block [BLOCK_SIZE];
                int blocks
                        = length/BLOCK_SIZE
                        + (length%BLOCK_SIZE == 0 ? 0 : 1);

                for (int b_i = bsg_id; b_i < blocks; b_i += (bsg_tiles_X * bsg_tiles_Y)) {
                        memcpy(block, &src[b_i * BLOCK_SIZE], sizeof(block));
                        memcpy(&dst[b_i * BLOCK_SIZE], block, sizeof(block));
                }
        }

        template<int BLOCK_SIZE>
        void faster_memcpy(long int *dst, const long int *src, long int length)
        {
                long int block [BLOCK_SIZE];
                int blocks
                        = length/BLOCK_SIZE
                        + (length%BLOCK_SIZE == 0 ? 0 : 1);

                for (int b_i = bsg_id; b_i < blocks; b_i += (bsg_tiles_X * bsg_tiles_Y)) {
                        __bsg_memcpy<32>(block, &src[b_i * BLOCK_SIZE], sizeof(block));
                        __bsg_memcpy<32>(&dst[b_i * BLOCK_SIZE], block, sizeof(block));
                }
        }

        template<int BLOCK_SIZE>
        void interleave(long int *dst, const long int *src, long int length)
        {
                int blocks
                        = length/BLOCK_SIZE
                        + (length%BLOCK_SIZE == 0 ? 0 : 1);

                for (int b_i = bsg_id; b_i < blocks; b_i += (bsg_tiles_X * bsg_tiles_Y)) {
                        memcpy(&dst[b_i * BLOCK_SIZE], &src[b_i * BLOCK_SIZE], BLOCK_SIZE * sizeof(long int));
                }

        }

        // this is currently the fastest we have
        template<int BLOCK_SIZE>
        void faster_interleave(long int *dst, const long int *src, long int length)
        {
                int blocks
                        = length/BLOCK_SIZE
                        + (length%BLOCK_SIZE == 0 ? 0 : 1);

                for (int b_i = bsg_id; b_i < blocks; b_i += (bsg_tiles_X * bsg_tiles_Y)) {
                        __bsg_memcpy<32>(&dst[b_i * BLOCK_SIZE], &src[b_i * BLOCK_SIZE], BLOCK_SIZE * sizeof(long int));
                }

        }
}
