// Takes a vector A of length N and a 1D filter of size F, padding
// size P, and stride S.  Performs 1D convolution of A with the filter
// and stores the result in B of size M = 1 + (N - F + 2P) / S.

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

// 1400 cycles
int conv1d_float_manual(const float *A,
                        const uint32_t A_len,
                        const float *F,
                        const uint8_t F_len,
                        const uint8_t stride,
                        float *B,
                        const uint32_t B_len)
{
        uint32_t B_len_unrolled = B_len & ~0x3;
        uint32_t remaining = B_len - B_len_unrolled;
        uint32_t step = stride << 2;

        float sum[4];
        float a[4];
        uint32_t ii = 0;
        uint32_t oi = 0;
        for(; oi < B_len_unrolled; oi += 4)
        {
                asm ("fmv.s.x %0,zero\n\t"
                     "fmv.s.x %1,zero\n\t"
                     "fmv.s.x %2,zero\n\t"
                     "fmv.s.x %3,zero\n\t"
                     : "=f" (sum[0]),
                       "=f" (sum[1]),
                       "=f" (sum[2]),
                       "=f" (sum[3]));

                for(uint32_t fi = 0; fi < F_len; fi++)
                {
                        float f = F[fi];

                        uint32_t stride_offset = 0;
                        a[0] = A[ii + fi];
                        
                        stride_offset += stride;
                        a[1] = A[ii + fi + stride_offset];

                        stride_offset += stride;
                        a[2] = A[ii + fi + stride_offset];

                        stride_offset += stride;
                        a[3] = A[ii + fi + stride_offset];

                        sum[0] += f * a[0];
                        sum[1] += f * a[1];
                        sum[2] += f * a[2];
                        sum[3] += f * a[3];
                }
                B[oi + 0] = sum[0];
                B[oi + 1] = sum[1];
                B[oi + 2] = sum[2];
                B[oi + 3] = sum[3];
                ii += step;
        }

        asm ("fmv.s.x %0,zero\n\t"
             "fmv.s.x %1,zero\n\t"
             "fmv.s.x %2,zero\n\t"
             "fmv.s.x %3,zero\n\t"
             : "=f" (sum[0]),
               "=f" (sum[1]),
               "=f" (sum[2]),
               "=f" (sum[3]));
        for(uint32_t fi = 0; fi < F_len; fi++)
        {
                float f = F[fi];
                uint32_t stride_offset = 0;
                for(uint32_t ai = 0; ai < remaining; ai++, stride_offset += stride)
                        a[ai] = A[ii + fi + stride_offset];
                for(uint32_t ui = 0; ui < remaining; ui++)
                        sum[ui] += f * a[ui];
        }

        for(uint32_t ui = 0; oi < B_len; ui++, oi++)
                B[oi] = sum[ui];
        return 0;
        
}

extern "C" {
        __attribute__((noinline))
        int kernel_tile_conv1d(const float *INPUT,
                               const int i_nelements,
                               const float *FILTER,
                               const int f_nelements,
                               const int stride,
                               float *OUTPUT)
        {
                int rc;
                uint32_t o_nelements = (i_nelements - f_nelements) / stride + 1;

                float input[i_nelements];
                float filter[f_nelements];
                float output[o_nelements];

                memcpy (input, INPUT, sizeof(INPUT[0])*i_nelements);
                memcpy (filter, FILTER, sizeof(FILTER[0])*f_nelements);

                for(int i = 0; i < 2; ++i){
                        bsg_cuda_print_stat_start(i);
                        rc = conv1d_float_manual(input, i_nelements, filter, f_nelements, stride, output, o_nelements);
                        bsg_cuda_print_stat_end(i);
                }

                memcpy (OUTPUT, output, sizeof(OUTPUT[0])*o_nelements);

                return rc;
        }
}
