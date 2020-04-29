#pragma once
// define bsg_tiles_X
#if !defined(bsg_tiles_X)
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#endif

// define bsg_tiles_Y
#if !defined(bsg_tiles_Y)
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#endif

#define NEW_BARRIER // use the new C++ barrier

#include <bsg_manycore.h>
#if defined(NEW_BARRIER)
#include <bsg_tile_group_barrier.hpp>
#else
#include <bsg_tile_group_barrier.h>
#endif

#if defined(NEW_BARRIER)

namespace { bsg_barrier<BSG_TILE_GROUP_X_DIM, BSG_TILE_GROUP_Y_DIM> barrier; }

#define bfs_kernel_prologue()                                           \
    do {                                                                \
        barrier.sync();                                                 \
        bsg_cuda_print_stat_kernel_start();                             \
    } while (0)                                                         \


#define bfs_kernel_epilogue()                   \
    do {                                        \
        bsg_cuda_print_stat_kernel_end();       \
        barrier.sync();                         \
    } while (0)

#else

namespace {
    INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                            0, BSG_TILE_GROUP_X_DIM-1,
                            0, BSG_TILE_GROUP_Y_DIM-1);
}

#define bfs_kernel_prologue()                                   \
    do {                                                        \
        bsg_tile_group_barrier(&r_barrier, &c_barrier);         \
        bsg_cuda_print_stat_kernel_start();                     \
    } while (0)


#define bfs_kernel_epilogue()                                   \
    do {                                                        \
        bsg_cuda_print_stat_kernel_end();                       \
        bsg_tile_group_barrier(&r_barrier, &c_barrier);         \
    } while (0)

#endif
