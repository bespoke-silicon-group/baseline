#ifndef __SUM_ABS_DIFF_HPP
#define __SUM_ABS_DIFF_HPP
#include <cstdint>

#define ABS(x) ((x) >= 0) ? (x) : (-(x))
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

// I <3 Hacks! Since bsg_manycore_arch.h can't handle the awesomeness
// of C++ templates I wrote this temporary replacement.
#ifdef bsg_tile_group_remote_ptr
#undef bsg_tile_group_remote_ptr
#include <type_traits>
#define bsg_tile_group_remote_ptr(__type,x,y,local_addr) \
        ( (typename std::add_pointer<__type>::type)                     \
        (   (REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS)               \
            | ((y) << Y_CORD_SHIFTS )                                   \
            | ((x) << X_CORD_SHIFTS )                                   \
            | ((uint32_t) (local_addr)   )                              \
            )                                                           \
                                                           )
#endif


#endif //__SUM_ABS_DIFF_HPP
