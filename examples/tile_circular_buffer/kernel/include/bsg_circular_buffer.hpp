#ifndef __BSG_CIRCULAR_BUFFER_HPP
#define __BSG_CIRCULAR_BUFFER_HPP
#include <array>
#include <bsg_manycore.h>

extern int __bsg_y, __bsg_x; // Tile group X/Y coordinate

typedef enum _qtype{
        SOURCE = 0,
        DEST = 1,
        NEITHER = 2
} qtype;



template<typename T, unsigned int dst_y, unsigned int dst_x>
T *bsg_remote_pointer(T* ptr){
        uintptr_t remote_prefix = (REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS);
        uintptr_t y_bits = ((dst_y) << Y_CORD_SHIFTS);
        uintptr_t x_bits = ((dst_x) << X_CORD_SHIFTS);
        uintptr_t local_bits = reinterpret_cast<uintptr_t>(ptr);
        return reinterpret_cast<T *>(remote_prefix | y_bits | x_bits | local_bits);
}

template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
class CircularBuffer{
public:
        typedef std::array<T, N * E> buf_t;
        typedef std::array<volatile unsigned char, E> occ_t;

        __attribute__((noinline))
        CircularBuffer<T,N,E,src_y,src_x,dst_y,dst_x>(occ_t &o){
                set_myself();
                occ_t * volatile& occupancy = get_occ_ptr();

                // This is the second ugliest piece of C++ code I've ever seen. Help?
                occ_t * volatile& dst_occ_p = *reinterpret_cast<decltype(&dst_occ_p)>(((REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS)
                                                                                    | ((dst_y) << Y_CORD_SHIFTS )
                                                                                    | ((dst_x) << X_CORD_SHIFTS )
                                                                                    | reinterpret_cast<uintptr_t>(&occupancy)));

                if ((me == SOURCE) && (occupancy == nullptr)){
                        occupancy = &o;
                        dst_occ_p = &o;
                        //bsg_print_hexadecimal((int)&dst_occ_p);
                } else {
                        ; // Assert something
                }
        }

        __attribute__((noinline))
        CircularBuffer<T,N,E,src_y,src_x,dst_y,dst_x>(buf_t &b){
                set_myself();
                buf_t * volatile& buffer = get_buf_ptr();

                // This is the second ugliest piece of C++ code I've ever seen. Help?
                buf_t * volatile& src_buf_p = *reinterpret_cast<decltype(&src_buf_p)>(((REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS)
                                                                                    | ((src_y) << Y_CORD_SHIFTS )
                                                                                    | ((src_x) << X_CORD_SHIFTS )
                                                                                    | reinterpret_cast<uintptr_t>(&buffer)));


                if((me == DEST) && (buffer == nullptr)){
                        buffer = &b;
                        src_buf_p = &b;
                        //bsg_print_hexadecimal((int)&src_buf_p);
                } else {
                        ; // Assert something
                }
        }

        __attribute__((noinline))
        void wait(){
                if (me == DEST){
                        while(get_occ_ptr() == nullptr);
                } else if (me == SOURCE){
                        while(get_buf_ptr() == nullptr);
                } else {
                        ; // Assert something
                }
        }
        // Get Read pointer (nullptr if not available?)
        // Get Write Pointer (nullptr if not available?)

private:
        qtype me;

        // TODO: Comment
        __attribute__((noinline))
        static occ_t * volatile& get_occ_ptr() {static occ_t * volatile __arr = nullptr; return __arr;}
        __attribute__((noinline))
        static buf_t * volatile & get_buf_ptr() {static buf_t * volatile __arr = nullptr; return __arr;}
        //volatile static std::array<TA, NA> *& get_ptr(std::array<TA, NA> &foo) {volatile static std::array<TA, NA> *__arr = nullptr; return __arr;}

        __attribute__((noinline))
        void set_myself(){
                if (__bsg_x == src_x && __bsg_y == src_y){
                        me = SOURCE;
                } else if (__bsg_x == dst_x && __bsg_y == dst_y){
                        me = DEST;
                } else { 
                        me = NEITHER;
                        return;
                }
        }
};


#endif
