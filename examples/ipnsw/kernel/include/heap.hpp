#pragma once
#include <array>
#include <algorithm>

template <int N>
class Heap {
public:
    using item = std::pair<float, int>;
    class compare {
    public:
        bool operator()(const item &i0, const item &i1) {
            return i0.first > i1.first;
        }
    };
    
    Heap():_n(0){}

    void push(item i) {
        _data[_n++] = i;
        std::push_heap(_data.begin(), _data.begin()+_n, compare());
    }

    item pop() {
        std::pop_heap(_data.begin(), _data.end()+_n, compare());
        return _data[_n--];
    }
    
    int                 _n;
    std::array<item, N> _data;
};
