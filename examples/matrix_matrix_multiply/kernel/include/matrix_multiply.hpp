#ifndef __MATRIX_MULTIPLY_HPP
#define __MATRIX_MULTIPLY_HPP
#include <cstdint>

/*
 * This is a naive implementation of matrix multiplication that
 * multiplies the two matricies A and B and stores the result in C.
 *
 * NOTE: Compiler is optimizing multiplies for indexing
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_matrix_multiply(TA *A, TB *B, TC *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH) {
        TC sum;
        for (uint32_t y = 0; y < A_HEIGHT; ++y) {
                for (uint32_t x = 0; x < B_WIDTH; ++x){
                        sum = static_cast<TC>(0);
                        for (uint32_t k = 0; k < A_WIDTH; k ++) {
                                sum += A[y * A_WIDTH + k] * B[k * B_WIDTH + x];
                        }
                        C[y * B_WIDTH + x] = sum;
                }
        }
        return 0;
}

/*
 * This is a slightly-smarter implementation of matrix multiplication
 * that multiplies the two matricies A and B and stores the result in
 * C. In this implementation, B is transposed into BT prior to calling
 * the kernel.
 *
 * NOTE: Compiler is optimizing multiplies for indexing
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_matrix_multiply_transpose(
                      TA *A, TB *BT, TC *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH) {

        TC sum;
        for (uint32_t y = 0; y < A_HEIGHT; ++y) {
                for (uint32_t x = 0; x < B_WIDTH; ++x){
                        sum = static_cast<TC>(0);
                        for (uint32_t k = 0; k < A_WIDTH; ++k) {
                                sum += A[y * A_WIDTH + k] * 
                                        BT[x * A_WIDTH + k];
                        }
                        C[y * B_WIDTH + x] = sum;
                }
        }

        return 0;
}

/*
 * This is a smarter implementation of matrix multiplication that
 * multiplies the two matricies A and B and stores the result in C. In
 * this implementation, B is transposed into BT prior to calling the
 * kernel and all multiplies used to index the A, B and
 * C arrays are transformed into additions (nomul).
 */
template <typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_matrix_multiply_transpose_nomul(
                      TA *A, TB *BT, TC *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH) {

        TC sum;
        for (uint32_t y = 0, ayoff = 0, boff, coff = 0; y < A_HEIGHT; ++y, ayoff += A_WIDTH) {
                boff = 0;
                for (uint32_t x = 0; x < B_WIDTH; x++, coff++){
                        sum = static_cast<TC>(0);
                        for (uint32_t aoff = ayoff; 
                             aoff < ayoff + A_WIDTH; 
                             ++aoff, ++boff) {
                                sum += A[aoff] * BT[boff];
                        }
                        C[coff] = sum;
                }
        }

        return 0;
}

/*
 * This is a smarter implementation of matrix multiplication that
 * multiplies the two matricies A and B and stores the result in C. In
 * this implementation, B is transposed into BT prior to calling the
 * kernel and all multiplies used to index the A, B and C arrays are
 * transformed into additions (nomul). The row-column dot product is
 * unrolled by a factor of F (a template parameter)
 */
template <unsigned int F, typename TA, typename TB, typename TC>
int __attribute__ ((noinline)) kernel_matrix_multiply_transpose_nomul_unroll (
                      TA *A, TB *BT, TC *C,
                      uint32_t A_HEIGHT, uint32_t A_WIDTH,
                      uint32_t B_WIDTH) {

        uint32_t incr = A_WIDTH * (F-1);
        for (uint32_t y = 0, ayoff = 0, boff = 0, coff = 0; y < A_HEIGHT; y ++, ayoff += A_WIDTH) {
                boff = 0;
                for (uint32_t x = 0; x < B_WIDTH; x += F) {
                        uint32_t bofff = 0;
                        TC sum[F] = {{static_cast<TC>(0)}};
                        for (uint32_t aoff = ayoff; aoff < ayoff + A_WIDTH; aoff++, ++boff) {
                                bofff = boff;
#pragma GCC unroll 8 // Does this unroll correctly when F < 4?
                                for (uint32_t f = 0; f < F; ++f, bofff += A_WIDTH){
                                        sum[f] += A[aoff] * BT[bofff];
                                }
                        }

#pragma GCC unroll 8
                        for (uint32_t f = 0; f < F; f++){
                                C[coff + f] = sum[f];
                        }
                        boff += incr;
                        coff += F;
                }
        }
        return 0;
}

#endif
