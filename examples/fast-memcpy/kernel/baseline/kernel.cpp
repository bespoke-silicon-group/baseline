#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <fast-memcpy.hpp>
#include <string.h>

namespace {
        INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                                0, bsg_tiles_X-1,
                                0, bsg_tiles_Y-1);
}

extern "C" int fast_memcpy(long int *dst, long int *src, long int length) {
        bsg_tile_group_barrier(&r_barrier, &c_barrier);
        bsg_cuda_print_stat_kernel_start();

        int partition_length = length/(bsg_tiles_X*bsg_tiles_Y);        
        memcpy(&dst[partition_length * bsg_id],
               &src[partition_length * bsg_id],
               partition_length * sizeof(int));
        
        bsg_tile_group_barrier(&r_barrier, &c_barrier);
        bsg_cuda_print_stat_kernel_end();
        return 0;
}

