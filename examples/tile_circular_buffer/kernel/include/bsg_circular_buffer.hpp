#ifndef __BSG_CIRCULAR_BUFFER_HPP
#define __BSG_CIRCULAR_BUFFER_HPP
#include <array>
#include <bsg_manycore.h>

extern int __bsg_y, __bsg_x; // Tile group X/Y coordinate

namespace CircularBuffer{
        // This is a replacement for the MACRO. Use at your own risk.
        template<unsigned int dst_y, unsigned int dst_x, typename T>
        T *bsg_remote_pointer(T* ptr){
                uintptr_t remote_prefix = (REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS);
                uintptr_t y_bits = ((dst_y) << Y_CORD_SHIFTS);
                uintptr_t x_bits = ((dst_x) << X_CORD_SHIFTS);
                uintptr_t local_bits = reinterpret_cast<uintptr_t>(ptr);
                return reinterpret_cast<T *>(remote_prefix | y_bits | x_bits | local_bits);
        }

        template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
        class Root{
        protected:
                typedef std::array<T, N * E> buf_t;
                typedef std::array<unsigned char, E> occ_t;

                // TODO: Comment
                __attribute__((noinline))
                static occ_t * volatile &get_occ_ptr() {static occ_t * volatile __arr = nullptr; return __arr;}

                __attribute__((noinline))
                static buf_t * volatile &get_buf_ptr() {static buf_t * volatile __arr = nullptr; return __arr;}
        };

        template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
        class Source : public Root<T, N, E, src_y, src_x, dst_x, dst_y> {
                typedef std::array<T, N * E> buf_t;
                typedef std::array<unsigned char, E> occ_t;
                occ_t occupancy;
        
        public:
                __attribute__((noinline))
                Source<T,N,E,src_y,src_x,dst_y,dst_x>(){
                        occ_t * volatile &occ_p = this->get_occ_ptr();
                        occ_t * volatile &dst_occ_p = *bsg_remote_pointer<dst_y, dst_x>(&occ_p);

                        if (occ_p == nullptr){
                                occ_p = &occupancy;
                                dst_occ_p = &occupancy;
                        } else {
                                bsg_print_hexadecimal(0xF1F0E000); // Assert something
                        }
                }

                __attribute__((noinline))
                void init_wait(){
                        while(this->get_buf_ptr() == nullptr);
                }
        };

        template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
        class Dest : public Root<T, N, E, src_y, src_x, dst_x, dst_y> {
                typedef std::array<T, N * E> buf_t;
                typedef std::array<unsigned char, E> occ_t;
                buf_t buffer;

        public:
                __attribute__((noinline))
                Dest<T,N,E,src_y,src_x,dst_y,dst_x>(){
                        buf_t * volatile &buf_p = this->get_buf_ptr();
                        buf_t * volatile &src_buf_p = *bsg_remote_pointer<src_y, src_x>(&buf_p);

                        if (buf_p == nullptr){
                                buf_p = &buffer;
                                src_buf_p = &buffer;
                        } else {
                                bsg_print_hexadecimal(0xF1F0E001); // Assert something
                        }
                }

                __attribute__((noinline))
                void init_wait(){
                        while(this->get_occ_ptr() == nullptr);
                }
        };
}
#endif
