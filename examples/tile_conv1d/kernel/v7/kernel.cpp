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

// 939 cycles, 0.9808 IPC
int conv1d_float_manual(const float *A,
                        const uint32_t A_len,
                        const float *F,
                        const uint8_t F_len,
                        const uint8_t stride,
                        float *B,
                        const uint32_t B_len)
{
        uint32_t step = stride << 2;

        register float sum0, sum1, sum2, sum3;
        register float a0, a1, a2, a3;
        uint32_t ii = 0;
        uint32_t oi = 0;

        while(oi < B_len)
        {
                register uint32_t to_compute = oi & 0x3;
                asm ("fmv.s.x %0,zero\n\t"
                     "fmv.s.x %1,zero\n\t"
                     "fmv.s.x %2,zero\n\t"
                     "fmv.s.x %3,zero\n\t"
                     : "=f" (sum0),
                       "=f" (sum1),
                       "=f" (sum2),
                       "=f" (sum3));
                for(uint32_t fi = 0; fi < F_len; fi++)
                {
                        float f = F[fi];
                        uint32_t stride_offset = 0;
                        switch(to_compute)
                        {
                        case 0:
                                a0 = A[ii + fi];
                                stride_offset += stride;
                        case 3:
                                a1 = A[ii + fi + stride_offset];
                                stride_offset += stride;
                        case 2:
                                a2 = A[ii + fi + stride_offset];
                                stride_offset += stride;
                        case 1:
                                a3 = A[ii + fi + stride_offset];
                                stride_offset += stride;
                        default:
                                break;
                        }

                        switch(to_compute)
                        {
                        case 0:
                                sum0 += f * a0;
                        case 3:
                                sum1 += f * a1;
                        case 2:
                                sum2 += f * a2;
                        case 1:
                                sum3 += f * a3;
                        default:
                                break;
                        }
                }
                switch(to_compute)
                {
                case 0:
                        B[oi++] = sum0;
                case 3:
                        B[oi++] = sum1;
                case 2:
                        B[oi++] = sum2;
                case 1:
                        B[oi++] = sum3;
                default:
                        break;
                }
                ii += step;
        }
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
