#ifndef __BSG_CIRCULAR_BUFFER_HPP
#define __BSG_CIRCULAR_BUFFER_HPP
#include <array>
#include <bsg_manycore.h>
#include <atomic>

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
                unsigned int occ_idx;

                // TODO: Comment
                __attribute__((noinline))
                static unsigned char * volatile &get_occ_ptr() {static unsigned char * volatile __arr = nullptr; return __arr;}

                __attribute__((noinline))
                static T * volatile &get_buf_ptr() {static T * volatile __arr = nullptr; return __arr;}
        };

        template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
        class Source : public Root<T, N, E, src_y, src_x, dst_x, dst_y> {
                unsigned char occupancy [E] = {{0}};

        public:
                __attribute__((noinline))
                Source<T,N,E,src_y,src_x,dst_y,dst_x>(){
                        // Get a reference to our local buffer pointer
                        unsigned char * volatile &occ_p = this->get_occ_ptr();
                        // Get a pointer to the Destination's occupancy buffer pointer
                        unsigned char * volatile *dst_occ_p = bsg_remote_pointer<dst_y, dst_x>(&occ_p);

                        if (occ_p == nullptr){
                                // Set our buf_p to the stack allocated buffer
                                occ_p = occupancy;
                                // Set Dest's occ_p to the remote address (within it's EVA) of our stack-allocated buffer
                                *dst_occ_p = bsg_remote_pointer<src_y, src_x>(occupancy);
                        } else {
                                bsg_print_hexadecimal(0xF1F0E000); // Assert something
                        }
                }

                __attribute__((noinline))
                void init_wait(){
                        while(this->get_buf_ptr() == nullptr);
                        this->get_buf_ptr() = bsg_remote_pointer<dst_y, dst_x>(this->get_buf_ptr());
                        this->occ_idx = 0;
                }

                __attribute__((noinline))
                T *obtain_wr_ptr(){
                        T *buffer = this->get_buf_ptr();
                        volatile auto &o = occupancy[this->occ_idx];

                        if(o)
                                return &buffer[this->occ_idx * E];
                        else
                                return nullptr;
                }

                __attribute__((noinline))
                T *obtain_wr_ptr_wait(){
                        T *buffer = this->get_buf_ptr();
                        auto &o = occupancy[this->occ_idx];

                        while(o);
                        return bsg_remote_pointer<dst_y, dst_x>(&buffer[this->occ_idx * E]);
                }

                __attribute__((noinline))
                int finish_wr_ptr(){
                        volatile auto &o = occupancy[this->occ_idx];

                        if(o){
                                bsg_print_hexadecimal(0xF1F0E002);
                                return -1;
                        }

                        // TODO: Flush, if necessary?
                        occupancy[this->occ_idx] = 1;
                        return 0;
                }

        };

        template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
        class Dest : public Root<T, N, E, src_y, src_x, dst_x, dst_y> {
                T buffer[N * E];

        public:
                __attribute__((noinline))
                Dest<T,N,E,src_y,src_x,dst_y,dst_x>(){
                        // Get a reference to our buffer pointer
                        T * volatile &buf_p = this->get_buf_ptr();
                        // Get a reference to source's buffer pointer
                        T * volatile *src_buf_p = bsg_remote_pointer<src_y, src_x>(&buf_p);

                        if (buf_p == nullptr){
                                // Set our buf_p to the stack allocated buffer
                                buf_p = buffer;
                                // Set Source's buf_p to the remote address (within it's EVA) of our stack-allocated buffer
                                *src_buf_p = bsg_remote_pointer<dst_y, dst_x>(buffer);
                        } else {
                                bsg_print_hexadecimal(0xF1F0E001); // Assert something
                        }
                }

                __attribute__((noinline))
                void init_wait(){
                        while(this->get_occ_ptr() == nullptr);

                        this->get_occ_ptr() = bsg_remote_pointer<src_y, src_x>(this->get_occ_ptr());
                        this->occ_idx = 0;
                }

                __attribute__((noinline))
                T *obtain_rd_ptr(){
                        volatile unsigned char *occupancy = this->get_occ_ptr();

                        if(occupancy[this->occ_idx])
                                return &(buffer[this->occ_idx * E]);
                        else
                                return nullptr;
                }

                __attribute__((noinline))
                T *obtain_rd_ptr_wait(){
                        unsigned char *occupancy = bsg_remote_pointer<src_y, src_x>(this->get_occ_ptr());
                        bsg_print_hexadecimal((int)this->get_occ_ptr());
                        bsg_print_hexadecimal((int)bsg_remote_pointer<src_y, src_x>(this->get_occ_ptr()));
                        bsg_print_hexadecimal((int)&occupancy[this->occ_idx]);
                        bsg_print_hexadecimal((int)bsg_remote_pointer<src_y, src_x>(&occupancy[this->occ_idx]));
                        bsg_print_hexadecimal((int)bsg_remote_pointer<src_y, src_x>(&occupancy[this->occ_idx])[0]);
                        bsg_print_int(19);
                        volatile auto &o = bsg_remote_pointer<src_y, src_x>(&occupancy[this->occ_idx])[0];
                        while(!o);
                        bsg_print_int(20);
                        bsg_print_hexadecimal(bsg_remote_pointer<src_y, src_x>(&occupancy[this->occ_idx])[0]);
                        return &buffer[this->occ_idx * E];
                }

        };
}
#endif
