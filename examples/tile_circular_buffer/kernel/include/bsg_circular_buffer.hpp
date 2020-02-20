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

template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
class CircularBuffer{
public:
        typedef std::array<T, N * E> buf_t;
        typedef std::array<volatile unsigned char, E> occ_t;

        __attribute__((noinline))
        CircularBuffer<T,N,E,src_y,src_x,dst_y,dst_x>(occ_t &o){
                set_myself();
                volatile occ_t *& occupancy = get_occ_ptr();

                // This is the second ugliest piece of C++ code I've ever seen. Help?
                volatile occ_t *& dst_occ_p = *reinterpret_cast<volatile occ_t **>(((REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS)
                                                                                    | ((dst_y) << Y_CORD_SHIFTS )
                                                                                    | ((dst_x) << X_CORD_SHIFTS )
                                                                                    | reinterpret_cast<uintptr_t>(&occupancy)));
                //bsg_print_int(4);
                if ((me == SOURCE) && (occupancy == nullptr)){
                        //bsg_print_int(5);
                        occupancy = &o;
                        dst_occ_p = &o;
                        //bsg_print_int(reinterpret_cast<int>(&dst_occ_p));
                } else {
                        ; // Assert something
                }
        }

        __attribute__((noinline))
        CircularBuffer<T,N,E,src_y,src_x,dst_y,dst_x>(buf_t &b){
                set_myself();
                volatile buf_t *& buffer = get_buf_ptr();

                // This is the second ugliest piece of C++ code I've ever seen. Help?
                volatile buf_t *& src_buf_p = *reinterpret_cast<volatile buf_t **>(((REMOTE_EPA_PREFIX << REMOTE_EPA_MASK_SHIFTS)
                                                                                    | ((src_y) << Y_CORD_SHIFTS )
                                                                                    | ((src_x) << X_CORD_SHIFTS )
                                                                                    | reinterpret_cast<uintptr_t>(&buffer)));

                //bsg_print_int(4);
                if((me == DEST) && (buffer == nullptr)){
                        //bsg_print_int(5);
                        buffer = &b;
                        src_buf_p = &b;
                        //bsg_print_int(reinterpret_cast<int>(&src_buf_p));
                } else {
                        ; // Assert something
                }
        }

        __attribute__((noinline))
        void wait(){
                if (me == DEST){
                        //bsg_print_int(6);
                        bsg_print_int(reinterpret_cast<int>(get_occ_ptr())); // TODO: If I remove these, the kernel hangs
                        while(get_occ_ptr() == nullptr);
                        bsg_print_int(reinterpret_cast<int>(get_occ_ptr())); // TODO: If I remove these, the kernel hangs
                } else if (me == SOURCE){
                        //bsg_print_int(7);
                        bsg_print_int(reinterpret_cast<int>(get_buf_ptr())); // TODO: If I remove these, the kernel hangs
                        while(get_buf_ptr() == nullptr);
                        bsg_print_int(reinterpret_cast<int>(get_buf_ptr())); // TODO: If I remove these, the kernel hangs
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
        volatile static occ_t *& get_occ_ptr() {volatile static occ_t *__arr = nullptr; return __arr;}
        __attribute__((noinline))
        volatile static buf_t *& get_buf_ptr() {volatile static buf_t *__arr = nullptr; return __arr;}
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
