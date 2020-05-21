/*
 * This kernel performs load and store to tile group shared memory.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define TEMPLATE_TG_DIM_X 4
#define TEMPLATE_TG_DIM_Y 4

#define bsg_tiles_X TEMPLATE_TG_DIM_X
#define bsg_tiles_Y TEMPLATE_TG_DIM_Y
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.hpp>
#include <cstdint>
#include <shared_mem.hpp>

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




bsg_barrier<bsg_tiles_X, bsg_tiles_Y> barrier;


template <int TG_DIM_X, int TG_DIM_Y, typename T>
int  __attribute__ ((noinline)) shared_mem_load_store(T *A, T *R,
                                                      uint32_t HEIGHT, uint32_t WIDTH) {



	bsg_tile_group_shared_mem (T, sh_A, (HEIGHT * WIDTH));

        for (int y = bsg_y; y < HEIGHT; y += TG_DIM_Y) {
            for (int x = bsg_x; x < WIDTH; x += TG_DIM_X) {
                bsg_tile_group_shared_store (T, sh_A, (y * WIDTH + x), A[y * WIDTH + x]);
            }
        }

        barrier.sync();

        for (int y = bsg_y; y < HEIGHT; y += TG_DIM_Y) {
            for (int x = bsg_x; x < WIDTH; x += TG_DIM_X) {
                bsg_tile_group_shared_load (T, sh_A, (y * WIDTH + x), R[y * WIDTH + x]);
            }
        }

        barrier.sync();

        return 0;

//        uint32_t start_y = __bsg_tile_group_id_y * block_size_y;
//        uint32_t start_x = __bsg_tile_group_id_x * block_size_x;
//        uint32_t end_y = start_y + block_size_y;
//        uint32_t end_x = start_x + block_size_x;
//        
//        // Double check matrix output dimensions. Only write where
//        // valid data is.
//	end_y = A_HEIGHT < (start_y + block_size_y) ? A_HEIGHT : (start_y + block_size_y);
//	end_x = B_WIDTH < (start_x + block_size_x) ? B_WIDTH : (start_x + block_size_x);
//
//        for (uint32_t iter_y = start_y + __bsg_y; iter_y < end_y; iter_y += TG_DIM_Y) {
//		bsg_cuda_print_stat_start(1);
//                for (uint32_t iter_x = start_x + __bsg_x; iter_x < end_x; iter_x += TG_DIM_X) {
//                        TC sum = static_cast<TC>(0);
//                        for (uint32_t k = 0; k < A_WIDTH; k ++) {
//                                sum += A[iter_y * A_WIDTH + k] * B[k * B_WIDTH + iter_x];
//                        }
//                        C[iter_y * B_WIDTH + iter_x] = sum;
//                }
//		bsg_cuda_print_stat_end(1);
//        }
//
//        return 0;
}




extern "C" {
        int  __attribute__ ((noinline)) kernel_shared_mem(
                      float *A, float *R,
                      uint32_t HEIGHT, uint32_t WIDTH) {
                int rc;
                bsg_cuda_print_stat_kernel_start();
                rc = shared_mem_load_store<TEMPLATE_TG_DIM_X, TEMPLATE_TG_DIM_Y> (A, R,
                                                                                  HEIGHT, WIDTH);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
