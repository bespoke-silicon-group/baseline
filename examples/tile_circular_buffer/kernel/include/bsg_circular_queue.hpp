#ifndef __BSG_CIRCULAR_BUFFER_HPP
#define __BSG_CIRCULAR_BUFFER_HPP

#include <array>

extern int __bsg_tile_group_id_y, __bsg_tile_group_id_x;

template<typename T, unsigned int N, unsigned int E, unsigned int src_y, unsigned int src_x, unsigned int dst_y, unsigned int dst_x>
class CircularBuffer{
public:
        
        CircularBuffer<T,N,E,src_y,src_x,dst_y,dst_x>(std::array<char, N> &o) : my_y(__bsg_tile_group_id_y), my_x(__bsg_tile_group_id_x){
                auto *occupancy = get_ptr(o);
                if(!occupancy)
                        occupancy = &o;
                else
                        ; // Assert something
        }

        CircularBuffer<T,N,E,src_y,src_x,dst_y,dst_x>(std::array<T, N * E> b) : my_y(__bsg_tile_group_id_y), my_x(__bsg_tile_group_id_x){
                auto *buffer = get_ptr(b);
                if(!buffer)
                        buffer = &b;
                else
                        ; // Assert something
        }

private:
        unsigned int my_x, my_y;
        // TODO: Comment
        template<typename TA, unsigned int NA>
        volatile static std::array<TA, NA> *& get_ptr(std::array<TA, NA> &foo) {volatile static std::array<TA, NA> *__arr = nullptr; return __arr;}
        //static std::array<T, N * E> *buf = NULL;
        //static const std::array<char, N> *occ = NULL;

};


#endif
