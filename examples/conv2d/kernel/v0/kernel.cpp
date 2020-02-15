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
#include <algorithm>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier, 0, bsg_tiles_X - 1, 0, bsg_tiles_Y - 1);

constexpr int output_dim(int N, int F, int P, int S)
{
        return 1 + (N - F + 2 * P) / S;
}

int do_conv2d(const float *A,
              const int M,
              const int N,
              const float *filter,
              const int Fy,
              const int Fx,
              const int P,
              float *B,
              const int Sy,
              const int Sx,
              const int tg_dim_x,
              const int tg_dim_y,
              const int block_size_y,
              const int block_size_x)
{
        int result_y = output_dim(M, Fy, P, Sy);
        int result_x = output_dim(N, Fx, P, Sx);

        int start_y = __bsg_tile_group_id_y * block_size_y;
        int start_x = __bsg_tile_group_id_x * block_size_x;
        int end_y = std::min(start_y + block_size_y, result_y);
        int end_x = std::min(start_x + block_size_x, result_x);
                
        for(int by = start_y +__bsg_y; by < end_y; by += tg_dim_y)
                for(int bx = start_x + __bsg_x; bx < end_x; bx += tg_dim_x)
                {
                        int window_y = by * Sy;
                        int window_x = bx * Sx;
                        
                        float res = 0;
                        for(int fy = 0; fy < Fy; fy++)
                                for(int fx = 0; fx < Fx; fx++)
                                {
                                        int ay = window_y - P + fy;
                                        int ax = window_x - P + fx;
                                        float a = 0;
                                        
                                        if((0 <= ay && ay < M) &&
                                           (0 <= ax && ax < N))
                                                a = A[ay * N + ax];
                                        res += filter[fy * Fx + fx] * a;
                                }
                        B[by * result_x + bx] = res;
                }

        bsg_tile_group_barrier(&r_barrier, &c_barrier);
        return 0;
}

extern "C"
{
        __attribute__((noinline))
        int kernel_conv2d(const float *A, const int M, const int N,
                          const float *filter, const int Fy, const int Fx,
                          const int P,
                          float *B,
                          const int Sy, const int Sx,
                          const int tg_dim_x, const int tg_dim_y,
                          const int block_size_y, const int block_size_x)
        {
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);
                do_conv2d(A, M, N,
                          filter, Fy, Fx,
                          P,
                          B,
                          Sy, Sx,
                          tg_dim_x,
                          tg_dim_y,
                          block_size_y,
                          block_size_x);
                bsg_cuda_print_stat_end(0);
                bsg_cuda_print_stat_kernel_end();
                return 0;
        }
}
