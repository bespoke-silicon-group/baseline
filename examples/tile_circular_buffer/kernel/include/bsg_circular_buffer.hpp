#ifndef __BSG_CIRCULAR_BUFFER_HPP
#define __BSG_CIRCULAR_BUFFER_HPP
#include <array>
#include <bsg_manycore.h>
#include <atomic>

// Tile group X/Y coordinates. If these are not defined then we should be scared
// and exit during compilation.
extern int __bsg_y, __bsg_x; 

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

        template<typename T, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x, unsigned int N, unsigned int DEPTH = 4>
        class Root{
        protected:
                unsigned int occ_idx = 0;

                ~Root<T, src_y, src_x, dst_y, dst_x, N, DEPTH>(){
                        occ_idx = 0;
                }

                // It's not possible to declare a static pointer (static
                // unsigned char *foo = nullptr); in the class scope in
                // C++. Instead, we have to declare a static pointer inside of a
                // method and intitalize it there. By returning a reference, we
                // can modify the pointer, and by making it *volatile we
                // indicate that the pointer value may change (as opposed to the
                // data).
                __attribute__((noinline))
                static unsigned char *volatile &get_occ_ptr() {static unsigned char *volatile __arr = nullptr; return __arr;}

                __attribute__((noinline))
                static T *volatile &get_buf_ptr() {static T *volatile __arr = nullptr; return __arr;}
        };

        template<typename T, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x, unsigned int N, unsigned int DEPTH = 4>
        class Source : public Root<T, src_y, src_x, dst_x, dst_y, N, DEPTH> {
                unsigned char occupancy [DEPTH] = {{0}};

        public:
                __attribute__((noinline))
                Source<T, src_y, src_x, dst_y, dst_x, N, DEPTH>(){
                        // Get a reference to our local buffer pointer
                        unsigned char *volatile &occ_p = this->get_occ_ptr();
                        // Get a pointer to the Destination's occupancy buffer pointer
                        unsigned char *volatile *dst_occ_p = bsg_remote_pointer<dst_y, dst_x>(&occ_p);

                        if (occ_p == nullptr){
                                // Set our occ_p (the static one in get_occ_ptr) to the stack allocated buffer
                                occ_p = occupancy;
                                // Set Dest's occ_p to the remote address (within it's EVA) of our stack-allocated buffer
                                *dst_occ_p = bsg_remote_pointer<src_y, src_x>(occupancy);
                        } else {
                                // Error: Someone intitialized occ_p. Were two Source objects declared?
                                // TODO: Would this fail on the second invocation of a tile group?
                                bsg_print_hexadecimal(0xF1F0E100);
                        }

                        // Error: The runtime Y-coordinate of this Source Object
                        // doesn't match the compiled Y-Coordinate
                        if(__bsg_y != src_y)
                                bsg_print_hexadecimal(0xF1F0E101);

                        // Error: The runtime X-coordinate of this Source Object
                        // doesn't match the compiled X-Coordinate
                        if(__bsg_x != src_x)
                                bsg_print_hexadecimal(0xF1F0E102);
                }

                __attribute__((noinline))
                ~Source<T, src_y, src_x, dst_y, dst_x, N, DEPTH>(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        unsigned int idx = this->occ_idx != 0 ? this->occ_idx - 1 : DEPTH - 1;
                                
                        // WARNING: Race Condition

                        // If SOURCE finishes before DEST we want to avoid
                        // cleaning up our occ_ptr before SOURCE finishes
                        volatile unsigned char &o = occupancy[idx];
                        
                        while(o);

                        this->get_occ_ptr() = nullptr;
                }

                // init_wait blocks until the destination has finished initialization. 
                // 
                // USERS MUST INSTANTIATE ALL CircularBuffer OBJECTS BEFORE
                // CALLING init_wait. NOT DOING THIS RISKS DEADLOCK.
                __attribute__((noinline))
                void init_wait(){
                        // While the Destination has not initialized our buffer pointer
                        while(this->get_buf_ptr() == nullptr);
                        this->occ_idx = 0;
                }

                // obtain_wr_ptr returns a pointer to the start of the current
                // data range in the buffer. If the corresponding location in
                // the occupancy array is 1 it will return nullptr, otherwise
                // there the data range is empty and it will return a pointer to
                // the start of the current data range in the buffer.
                __attribute__((noinline))
                T *obtain_wr_ptr(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        volatile unsigned char &o = occupancy[this->occ_idx];

                        if(o)
                                return nullptr;

                        T *buffer = this->get_buf_ptr();
                        return &buffer[this->occ_idx * DEPTH];
                }

                // obtain_wr_ptr returns a pointer to the start of the current
                // data range in the buffer. If the corresponding location in
                // the occupancy array is 1 it loop until there is valid data
                // and never time out. When the corresponding value is zero the
                // data range is empty and it will return a pointer to the start
                // of the current data range in the buffer.
                __attribute__((noinline))
                T *obtain_wr_ptr_wait(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        volatile unsigned char &o = occupancy[this->occ_idx];
                        
                        while(o);

                        T *buffer = this->get_buf_ptr();
                        return &buffer[this->occ_idx * DEPTH];
                }

                // finish_wr_ptr signals to the destination that the current
                // data range in the buffer is no longer being written. If the
                // corresponding location in the occupancy array is 1 the method
                // will use bsg_print_hexadecimal to signal an error and return
                // -1. If the command is successful, it will return 0 and
                // increment occ_idx. Call obtain_wr_ptr* to get the next write
                // pointer.
                //
                // WARNING: DEADLOCK. obtain_rd_ptr_wait in the Destination will
                // hang if finish_rd_ptr is not called on each data range.
                __attribute__((noinline))
                int finish_wr_ptr(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        volatile unsigned char &o = occupancy[this->occ_idx];

                        if(o){
                                bsg_print_hexadecimal(0xF1F0E103);
                                return -1;
                        }

                        // TODO: Flush o, if necessary?
                        o = 1;

                        this->occ_idx = (this->occ_idx + 1) % DEPTH;
                        return 0;
                }

        };

        template<typename T, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x, unsigned int N, unsigned int DEPTH = 4>
        class Dest : public Root<T, src_y, src_x, dst_x, dst_y, N, DEPTH> {
                T buffer[N * DEPTH];

        public:
                __attribute__((noinline))
                Dest<T, src_y, src_x, dst_y, dst_x, N, DEPTH>(){
                        // Get a reference to our buffer pointer
                        T *volatile &buf_p = this->get_buf_ptr();
                        // Get a reference to source's buffer pointer
                        T *volatile *src_buf_p = bsg_remote_pointer<src_y, src_x>(&buf_p);

                        if (buf_p == nullptr){
                                // Set our buf_p (the static one in get_buf_ptr) to the stack allocated buffer
                                buf_p = buffer;
                                // Set Source's buf_p to the remote address
                                // (within it's EVA) of our stack-allocated
                                // buffer
                                *src_buf_p = bsg_remote_pointer<dst_y, dst_x>(buffer);
                        } else {
                                // If buf_p isn't null (the static
                                // initialization value) something has gone
                                // horribly wrong
                                bsg_print_hexadecimal(0xF1F0E000); // Assert something
                        }

                        // Error: The runtime Y-coordinate of this Source Object
                        // doesn't match the compiled Y-Coordinate
                        if(__bsg_y != dst_y)
                                bsg_print_hexadecimal(0xF1F0E001);

                        // Error: The runtime X-coordinate of this Source Object
                        // doesn't match the compiled X-Coordinate
                        if(__bsg_x != dst_x)
                                bsg_print_hexadecimal(0xF1F0E002);

                }

                __attribute__((noinline))
                ~Dest<T, src_y, src_x, dst_y, dst_x, N, DEPTH>(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        unsigned int idx = this->occ_idx != 0 ? this->occ_idx - 1 : DEPTH - 1;
                                
                        // WARNING: Race Condition

                        // If Dest finishes before Source and there's still data
                        // available, we can't really do anything. Dest will
                        // deadlock on its destructor, we'll "throw a warning"
                        // to give a hint.
                        volatile unsigned char &o = occupancy[idx];
                        if(o)
                                bsg_print_hexadecimal(0xF1F0EDED);

                        this->get_buf_ptr() = nullptr;
                }

                // init_wait blocks until the Source has finished initialization. 
                // 
                // USERS MUST INSTANTIATE ALL CircularBuffer OBJECTS BEFORE
                // CALLING init_wait. NOT DOING THIS RISKS DEADLOCK.
                __attribute__((noinline))
                void init_wait(){
                        // Wait until the source has initialized our occupancy pointer
                        while(this->get_occ_ptr() == nullptr);
                        this->occ_idx = 0;
                }

                // obtain_rd_ptr returns a pointer to the start of the current
                // data range in the buffer. If the corresponding location in
                // the occupancy array is 0 it will return nullptr, otherwise
                // there is valid data and it will return a pointer to the start
                // of the current data range in the buffer.
                __attribute__((noinline))
                const T *obtain_rd_ptr(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        volatile unsigned char &o = occupancy[this->occ_idx];

                        if(!o)
                                return nullptr;

                        return &(buffer[this->occ_idx * DEPTH]);
                }

                // obtain_rd_ptr returns a pointer to the start of the current
                // data range in the buffer. If the corresponding location in
                // the occupancy array is 0 it loop until there is valid data
                // and never time out. When the corresponding value is non-zero
                // it will return a pointer to the start of the current data
                // range in the buffer.
                __attribute__((noinline))
                const T *obtain_rd_ptr_wait(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        volatile unsigned char &o = occupancy[this->occ_idx];

                        while(!o);

                        return &buffer[this->occ_idx * DEPTH];
                }

                // finish_rd_ptr signals to the destination that the current
                // data range in the buffer is no longer being read. If the
                // corresponding location in the occupancy array is 1 the method
                // will use bsg_print_hexadecimal to signal an error and return
                // -1. If the command is successful, it will return 0 and
                // increment occ_idx. Call obtain_wr_ptr* to get the next write
                // pointer.
                //
                // WARNING: DEADLOCK. obtain_wr_ptr_wait in the Source will hang
                // if finish_rd_ptr is not called on each data range.
                //
                // WARNING: DEADLOCK. The Source destructor will hang until all
                // buffers have been read. Users must call finish_rd_ptr on ALL
                // data transferred.
                __attribute__((noinline))
                int finish_rd_ptr(){
                        unsigned char *occupancy = this->get_occ_ptr();
                        volatile unsigned char &o = occupancy[this->occ_idx];

                        if(!o){
                                bsg_print_hexadecimal(0xF1F0E003);
                                return -1;
                        }

                        // TODO: Flush, if necessary?
                        o = 0;
                        this->occ_idx = (this->occ_idx + 1) % DEPTH;
                        return 0;
                }

        };
}
#endif
