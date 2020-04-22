#pragma once
#include <cstdint>
#include <cstring>
#include <bsg_manycore.h>
namespace {
        template <int BLOCK_SIZE, int CACHE_LINE_WORDS>
        void block_memcpy(long int *dst, const long int *src)
        {
                memcpy(dst, src, BLOCK_SIZE * sizeof(*dst));
        }

        template <int BLOCK_SIZE, int CACHE_LINE_WORDS, int UNROLL_FACTOR>
        void block_memcpy_unrolled(long int *dst, const long int *src)
        {
        }

        template <>
        void block_memcpy<32, 32>(long int *dst, const long int *src)
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
        void block_memcpy<128, 32>(long int *dst, const long int *src)
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
        void block_memcpy<256, 32>(long int *dst, const long int *src)
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
        void fast_memcpy(long int *dst, const long int *src, long int length)
        {
                long int block [BLOCK_SIZE];
                int blocks
                        = length/BLOCK_SIZE
                        + (length%BLOCK_SIZE == 0 ? 0 : 1);

                for (int b_i = bsg_id; b_i < blocks; b_i += (bsg_tiles_X * bsg_tiles_Y)) {
                        block_memcpy<BLOCK_SIZE, CACHE_LINE_WORDS>(block, &src[b_i*BLOCK_SIZE]);
                        block_memcpy<BLOCK_SIZE, CACHE_LINE_WORDS>(&dst[b_i*BLOCK_SIZE], block);
                }
        }
}
