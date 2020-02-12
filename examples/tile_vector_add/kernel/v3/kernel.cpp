/*
 * This kernel performs vector addition. 
 * 
 * This version of tile 
 * This version assumes only a single 1x1 tile group is called.
 */

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

#include <vector_add.hpp>
#include <cstring>

extern int bsg_printf(const char*, ...);

/* We wrap all external-facing C++ kernels with `extern "C"` to
 * prevent name mangling 
 */
extern "C" {

        int  __attribute__ ((noinline)) kernel_vector_add_float(
                      float *A, float *B, float *C,
                      uint32_t nels,
                      uint32_t block_size_y, uint32_t block_size_x,
                      uint32_t tag) {

                bsg_cuda_print_stat_kernel_start();
                float a_[nels],b_[nels];
                float c_[nels];
                for (size_t i = 0; i < nels; i++)
                {
                        a_[i]=A[i];
                        b_[i]=B[i];
                }
                for (int iter=0; iter<2; iter++){
                        bsg_cuda_print_stat_start(tag+iter);
                        rc = kernel_tile_vector_add(a_, b_, c_, nels);
                        bsg_cuda_print_stat_end(tag+iter);

                }
                for (size_t i = 0; i < nels; i++)
                {
                        C[i]=c_[i];
                }
                bsg_cuda_print_stat_kernel_end();

                return rc;
        }
}
