#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM

#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <fast-memcpy.hpp>

namespace {
        INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                                0, bsg_tiles_X-1,
                                0, bsg_tiles_Y-1);
}

extern "C" int fast_memcpy(long int *dst, const long int *src, long int length) {
        bsg_tile_group_barrier(&r_barrier, &c_barrier);
        bsg_cuda_print_stat_kernel_start();

        fast_memcpy<256>(dst, src, length);
        
        bsg_tile_group_barrier(&r_barrier, &c_barrier);
        bsg_cuda_print_stat_kernel_end();
        return 0;
}

