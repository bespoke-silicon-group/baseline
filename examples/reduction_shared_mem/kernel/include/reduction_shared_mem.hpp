#ifndef __REDUCTION_SHARED_MEM_HPP
#define __REDUCTION_SHARED_MEM_HPP
#include <cstdint>

template <typename TA>
int  __attribute__ ((noinline)) kernel_reduction_shared_mem_single_thread(TA *A, uint32_t N) {

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

        // We perform reduction in this loop, starting from an offset of 1 and a multiplicand of 2:
        // For every element with index multiplicand of 2: A[i] <-- A[i] + A[i+1]
        // For every element with index multiplicand of 4: A[i] <-- A[i] + 2
        // For every element with index multiplicand of 8: A[i] <-- A[i] + 4
        // .... Continue until offset is larger that array size ....
        // Example
        // |1|1|1|1|1|1|1|1|   Offset: 1  - Mult: 2
        //  |/  |/  |/  |/
        // |2|1|2|1|2|1|2|1|   Offset: 2  - Mult: 4
        //  |  /   |  /  
        //  | /    | /
        //  |/     |/
        // |4|1|2|1|4|1|2|1|   Offset: 4  - Mult: 8
        //  |       /
        //  |      /
        //  |     /
        //  |    /
        //  |   /
        //  |  /
        //  | /
        //  |/
        // |8|1|2|1|4|1|2|1|

        while (offset < N) {
                if (!(bsg_id % mult)){

                        float lc_A, lc_B;
                        // lc_A <-- sh_A[bsg_id]
                        bsg_tile_group_shared_load (float, sh_A, bsg_id, lc_A);
                        // lc_B <-- sh_A[bsg_id + offset]
                        bsg_tile_group_shared_load (float, sh_A, bsg_id + offset, lc_B);

                        // sh_A[bsg_id] <-- lc_A + lc_B
                        bsg_tile_group_shared_store (float, sh_A, bsg_id, lc_A + lc_B);
		}

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                mult *= 2;
                offset *= 2;
        }

        // Only one tile stores the reduction result back into A[0]
        if (bsg_id == 0) {
                // A[0] <-- sh_A[0]
                bsg_tile_group_shared_load(float, sh_A, 0, A[0]);
        }

        bsg_tile_group_barrier(&r_barrier, &c_barrier);

        return 0;
}


template <typename TA>
int  __attribute__ ((noinline)) kernel_reduction_shared_mem_multi_thread(TA *A, uint32_t N) {

        // Define tile group shared memory with size of N
        bsg_tile_group_shared_mem(float, sh_A, N);

        // Work is divided evenly among tiles in the tile group
        // Each tile's share: N / (bsg_tiles_X * bsg_tiles_Y)
        // We wrap a `thread loop` around the code, with each iteration iter_x
        // representing a virtual thread, which loads one element into shared memory
        // Each tile loads its share of the elements from DRAM based on its flat ID 
        // inside tile group (bsg_id) into tile group shared memory
        for (int iter_x = bsg_id; iter_x < N; iter_x += bsg_tiles_X * bsg_tiles_Y) {
                bsg_tile_group_shared_store (float, sh_A, iter_x, A[iter_x]);
        }

        // Barrier to make sure all tiles are finished storing into
        // tile group shared memory
        bsg_tile_group_barrier(&r_barrier, &c_barrier);


        int offset = 1;
        int mult = 2;


        // We perform reduction in this loop, starting from an offset of 1 and a multiplicand of 2:
        // For every element with index multiplicand of 2: A[i] <-- A[i] + A[i+1]
        // For every element with index multiplicand of 4: A[i] <-- A[i] + 2
        // For every element with index multiplicand of 8: A[i] <-- A[i] + 4
        // .... Continue until offset is larger that array size ....
        // Example
        // |1|1|1|1|1|1|1|1|   Offset: 1  - Mult: 2
        //  |/  |/  |/  |/
        // |2|1|2|1|2|1|2|1|   Offset: 2  - Mult: 4
        //  |  /   |  /  
        //  | /    | /
        //  |/     |/
        // |4|1|2|1|4|1|2|1|   Offset: 4  - Mult: 8
        //  |       /
        //  |      /
        //  |     /
        //  |    /
        //  |   /
        //  |  /
        //  | /
        //  |/
        // |8|1|2|1|4|1|2|1|

        // Each tile however, is responsible for multiple elements
        // We wrap a `thread loop` around the code, with each iteration (iter_x) representing
        // a virtual thread, that is repsonsible for the element with index iter_x
        while (offset < N) {
                for (int iter_x = bsg_id; iter_x < N; iter_x += bsg_tiles_X * bsg_tiles_Y) {
                        if (!(iter_x % mult)){
                                float lc_A, lc_B;

                                // lc_A <-- sh_A[iter_x]
                                bsg_tile_group_shared_load (float, sh_A, iter_x, lc_A);
                                // lc_B <-- sh_A[iter_x + offset]
                                bsg_tile_group_shared_load (float, sh_A, iter_x + offset, lc_B);

                                // sh_A[iter_x] <-- lc_A + lc_B
                                bsg_tile_group_shared_store (float, sh_A, iter_x, lc_A + lc_B);
                        }
                }

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                mult *= 2;
                offset *= 2;
	}

        // Only one tile stores the reduction result back into A[0]
        // And it is only done once, so no need to wrap this section
        // in thread loop
        if (bsg_id == 0) {
                // A[0] <-- sh_A[0]
                bsg_tile_group_shared_load(float, sh_A, 0, A[0]);
        }

        bsg_tile_group_barrier(&r_barrier, &c_barrier);

        return 0;
}



#endif //__REDUCTION_SHARED_MEM_HPP
