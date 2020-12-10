#include <kernel_common.hpp>

extern "C"
int kernel_addmv_c(float bsg_attr_remote * bsg_attr_noalias result,
                 uint32_t bsg_attr_remote *bsg_attr_noalias result_strides,
                 float bsg_attr_remote * bsg_attr_noalias input,
                 uint32_t bsg_attr_remote * bsg_attr_noalias input_strides,
                 float bsg_attr_remote * bsg_attr_noalias mat,
                 uint32_t bsg_attr_remote * bsg_attr_noalias mat_strides,
                 int r1, int c1,
                 float bsg_attr_remote * bsg_attr_noalias vec,
                 uint32_t bsg_attr_remote * bsg_attr_noalias vec_strides,
                 float alpha,
                 float beta
                   );

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
        float bsg_attr_remote * bsg_attr_noalias input_p = (float bsg_attr_remote * bsg_attr_noalias) input.data_ptr();
        float bsg_attr_remote * bsg_attr_noalias mat_p  = (float bsg_attr_remote * bsg_attr_noalias) mat.data_ptr();
        float bsg_attr_remote * bsg_attr_noalias vec_p  = (float bsg_attr_remote * bsg_attr_noalias) vec.data_ptr();
        float bsg_attr_remote * bsg_attr_noalias result_p  = (float bsg_attr_remote * bsg_attr_noalias) result.data_ptr();

        kernel_addmv_c(result_p,
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
