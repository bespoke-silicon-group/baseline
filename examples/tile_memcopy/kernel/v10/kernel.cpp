// Copies a list of integers from INPUT into a tile, adds one to each element,
// and then copies the result to OUTPUT. Only INPUT/OUTPUT data transfer is
// profiled to understand the limitations of memory copy. INPUT/OUTPUT copy is
// run twice to initialize the icache, which also brings the data into the
// victim cache. Therefore, Tags 0 (into tile) and 1 (out of tile) can be
// ignored, and tags 2 (into tile) and 3 (out of tile) profile data transfer
// performance.

// * Kernel code is small enough to be loaded into icache. (don't rely on this)
// * Uses a for loop to copy data to rtemp, then write to DMEM
//   * For loops use assembly
//   * rtemp now declared as float
//   * Unrolled by a factor of FACTOR (gcc pragma says 16, but array size/FACTOR dictates limit)
//   * Asm looks like lw/*/sw* (32 loads in flight before stall),
//   * sw dependencies ARE in same order as the lw producers. See:

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 1
#define BSG_TILE_GROUP_Y_DIM 1
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <cstdint>
#include <cstring>

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

__attribute__((noinline))
void * bsg_memcpy(void *__restrict dst, const void *__restrict src, size_t n){
        uintptr_t udst = reinterpret_cast<uintptr_t>(dst), usrc = reinterpret_cast<uintptr_t>(src);
        static const unsigned int C_WORD_MASK = 0x3;
        if ((n & C_WORD_MASK) | (udst & C_WORD_MASK) | (usrc & C_WORD_MASK)){
                return memcpy(dst, src, n);
        } else {
                return __bsg_memcpy<32>(dst, src, n);
        }
}

extern "C" {
        __attribute__((noinline))
        int kernel_tile_memcopy(const int *INPUT,
                                const uint32_t i_nelements,
                                int *OUTPUT)
        {
                int rc;

                int temp[i_nelements];
                for(int i = 0; i < 4; i += 2){
                        bsg_cuda_print_stat_start(i);
                        bsg_memcpy(temp, INPUT, i_nelements* sizeof(int));
                        bsg_cuda_print_stat_end(i);

                        for(int j = 0; j < i_nelements; ++j){
                                temp[j] += 1;
                        }
                                
                        bsg_cuda_print_stat_start(i + 1);
                        for(int j = 0; j < i_nelements; ++j){
                                OUTPUT[j] = temp[j];
                        }
                        bsg_cuda_print_stat_end(i + 1);
                }

                return rc;
        }
}
