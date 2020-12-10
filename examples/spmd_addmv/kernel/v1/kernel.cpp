#include <kernel_common.hpp>

// Locations:
//     src should be in remote memory (DRAM)
//     dest should be in local scratchpad
template <unsigned int BY, unsigned int BX>
//__attribute__ ((noinline))
inline void load_block(float * bsg_attr_noalias dest,
                float bsg_attr_remote * bsg_attr_noalias src,
                uint32_t  bsg_attr_remote * bsg_attr_noalias src_strides,
                int by_i, int bx_i) {

        // Move the raw pointer to the row/column start.
        src = src +
                (by_i * BY * src_strides[0]) +
                (bx_i * BX * src_strides[1]);

        //bsg_unroll(2)
        for (int i = 0; i < BY; i++) {
                // If the unroll factor > B, it will unroll by factor B
                // instead.
                bsg_unroll(16)
                for (int j = 0 ; j < BX; j ++){
                        dest[BX * i + j] = src[i * src_strides[0] + j];
                }
        }
}

// Locations:
//     src should be in remote memory (DRAM)
//     dest should be in local scratchpad
template <unsigned int BX>
//__attribute__ ((noinline))
inline void load_col(float * bsg_attr_noalias dest,
                float bsg_attr_remote * bsg_attr_noalias src,
                uint32_t  bsg_attr_remote * bsg_attr_noalias src_strides,
                int by_i) {

        // Move the raw pointer to the row/column start.
        //Generic: src = src + (by_i * BX * src_strides[0]);
        src = src + (by_i * BX);

        bsg_unroll(16)
        for (int i = 0; i < BX; i++) {
                dest[i] = src[i];
        }
}

// Store the result (psum) to remote memory and reset the psum array
// in scratchpad.
// Locations:
//     src should be in local scratchpad
//     dest should be in remote memory (DRAM)
template <unsigned int BY>
//__attribute__ ((noinline))
inline void store_block_and_reset(float * bsg_attr_noalias src,
                           float bsg_attr_remote * bsg_attr_noalias dest,
                           uint32_t  bsg_attr_remote * bsg_attr_noalias dest_strides,
                           int by_i) {

        // Move the raw pointer to the row/column start.
        //Generic: dest = dest + (by_i * BY * dest_strides[0]);
        dest = dest + (by_i * BY);
                
        // Store from the source matrix, into the block.
        bsg_unroll(16)
        for (int sby_i = 0; sby_i < BY; sby_i++) {
                //General: dest[sby_i * dest_strides[0]] = src[sby_i];
                dest[sby_i] = src[sby_i];
                src[sby_i] = 0.0f;
        }
}

// Accumulate the product of two BY-by-BX input matrices into an
// output matrix.
//
// This is done by iteratively computing SBY-by-SBX sub-matrix
// outputs, and individually accumulating those into the output
// matrix.
// Locations:
//     dest should be in local scratchpad
//     mat1 should be in local scratchpad
//     mat2 should be in local scratchpad
template<unsigned int BY, unsigned int BX>
//__attribute__ ((noinline))
inline void accum_col(float* bsg_attr_noalias dest,
                        float* bsg_attr_noalias mat,
                        float* bsg_attr_noalias vec) {

        // Load in a SBY-by-1 sub-block of the output
        // vector into psum for accumulation.
        // Location:
        //    Registers
        float psum[BY];

        bsg_unroll(16)
        for(int by_i = 0; by_i < BY; ++by_i){
                psum[by_i] = dest[by_i];
        }

        // For each X sub-block
        for (int bx_i = 0; bx_i < BX; ++bx_i) {
                float col = vec[bx_i];

                bsg_unroll(16)
                for(int by_i = 0; by_i < BY; ++by_i) {
                        int sb_anchor_y = by_i * BX;
                        float * bsg_attr_noalias row_anchor = &(mat[sb_anchor_y]);
                                
                        psum[by_i] += col * row_anchor[bx_i];
                }
        }

        // Write the partial sum sub-block back into
        // the result.
        bsg_unroll(16)
        for(int by_i = 0; by_i < BY; ++by_i){
                dest[by_i] = psum[by_i];
        }
}

template<unsigned int BY, unsigned int BX, bool unused>
__attribute__ ((noinline))
int kernel_addmv(float bsg_attr_remote * bsg_attr_noalias result,
                 uint32_t *bsg_attr_noalias result_strides,
                 float bsg_attr_remote * bsg_attr_noalias input,
                 uint32_t * bsg_attr_noalias input_strides,
                 float bsg_attr_remote * bsg_attr_noalias mat,
                 uint32_t * bsg_attr_noalias mat_strides,
                 int r1, int c1,
                 float bsg_attr_remote * bsg_attr_noalias vec,
                 uint32_t * bsg_attr_noalias vec_strides,
                 float alpha,
                 float beta
                 ) {

#ifdef USE_ASSERT
        // This MM implementation is blocked into BY-by-BX output
        // blocks. This implies the following dimension constraints:

        // M1 columns must be divisible by the Block X-dimension
        hb_assert(c1 % BX == 0);

        // M1 rows must be divisible by the Block Y-dimension
        hb_assert(r1 % BY == 0);
#endif
        // TODO: The compiler doesn't know that c1 is always (or
        // should always be) nonzero. This adds an extra BNE
        // instruction in the inner-loop. There should be some way to
        // signal to the compiler, perhaps with hb_assert?
        int blocks = c1 / BX;

        // Determine the number of output blocks
        int by_blocks = (r1 / BY);
        int by_each = r1 / (BY * BSG_TILE_GROUP_X_DIM * BSG_TILE_GROUP_Y_DIM);
        int by_start = __bsg_id * by_each;
        int by_end = by_start + by_each;
        
        // Local Storage for blocks, and partial sums
        // Locations:
        //    block_rows is in Local Scratchpad
        //    block_col is in Local Scratchpad
        float block_rows[BY * BX];
        register float block_col[BX];
        register float block_input[BY];
        float psum[BY];

        for (int by_i = 0; by_i < BY; ++by_i) {
                psum[by_i] = 0.0f;
        }

        g_barrier.sync();

        //   Start profiling
        bsg_cuda_print_stat_kernel_start();

        for (int by_i = by_start; by_i < by_end; by_i++){
                load_col<BY>(block_input, input, input_strides, by_i);
                for (int bx_i = 0; bx_i < blocks; bx_i++){
                        load_block<BY, BX>(block_rows, mat, mat_strides, by_i, bx_i);
                        load_col<BX>(block_col, vec, vec_strides, bx_i);
                        accum_col<BY, BX>(psum, block_rows, block_col);
                }

                bsg_unroll(16)
                for (int by_i = 0; by_i < BY; ++by_i) {
                        psum[by_i] = psum[by_i] * alpha + block_input[by_i] * beta;
                }
                
                store_block_and_reset<BY>(psum, result, result_strides, by_i);
        }

        //   End profiling
        bsg_cuda_print_stat_kernel_end();

        return 0;

}
extern "C"
int kernel_addmv(
                 hb_tensor_t* _result, 
                 hb_tensor_t* _input, 
                 hb_tensor_t* _mat,
                 hb_tensor_t* _vec, 
                 float* _beta, 
                 float* _alpha
                 ){
        auto input  = HBTensor<float>(_input);
        auto mat    = HBTensor<float, 2>(_mat);
        auto vec    = HBTensor<float>(_vec);
        auto result = HBTensor<float>(_result);
        float beta  = *_beta;
        float alpha = *_alpha;


        // get data pointers
        float* bsg_attr_noalias input_p = (float* bsg_attr_noalias) input.data_ptr();
        float* bsg_attr_noalias mat_p  = (float* bsg_attr_noalias) mat.data_ptr();
        float* bsg_attr_noalias vec_p  = (float* bsg_attr_noalias) vec.data_ptr();
        float* bsg_attr_noalias result_p  = (float* bsg_attr_noalias) result.data_ptr();

        kernel_addmv<8, 16, false>(result_p,
                                    result.get_strides(),
                                    input_p,
                                    input.get_strides(),
                                    mat_p,
                                    mat.get_strides(),
                                    mat.dim(0), mat.dim(1),
                                    vec_p, // vec strides?
                                    vec.get_strides(),
                                    alpha,
                                    beta);
        g_barrier.sync();
        return 0;
}
