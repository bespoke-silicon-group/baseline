#ifndef __REDUCTION_SHARED_MEM_HPP
#define __REDUCTION_SHARED_MEM_HPP
#include <cstdint>

template <typename TA>
int  __attribute__ ((noinline)) kernel_reduction_shared_mem_single_tile_group(TA *A, uint32_t N) {

        // Define tile group shared memory with size of N
        bsg_tile_group_shared_mem(float, sh_A, N);

        // Each tile loads one element from DRAM based on its flat ID 
        // inside tile group (bsg_id) into tile group shared memory
        bsg_tile_group_shared_store (float, sh_A, bsg_id, A[bsg_id]);

        // Barrier to make sure all tiles are finished storing into
        // tile group shared memory
        bsg_tile_group_barrier(&r_barrier, &c_barrier);


        int offset = 1;
        int mult = 2;

        while (offset < N) {
                if (!(bsg_id % mult)){
                        float lc_A, lc_B;

                        bsg_tile_group_shared_load (float, sh_A, bsg_id, lc_A);
                        bsg_tile_group_shared_load (float, sh_A, bsg_id + offset, lc_B);

                        bsg_tile_group_shared_store (float, sh_A, bsg_id, lc_A + lc_B);
		}

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                mult *= 2;
                offset *= 2;
	}

        // Only one tile stores the reduction result back into A[0]
        if (bsg_id == 0)
                bsg_tile_group_shared_load(float, sh_A, 0, A[0]);

        bsg_tile_group_barrier(&r_barrier, &c_barrier);

        return 0;
}

#endif //__REDUCTION_SHARED_MEM_HPP
