#pragma once
#include <array>
#include <algorithm>

template <int N, typename T, typename Comparitor>
class Heap {
public:
    Heap(T *data):
        _data(data),
        _n(0){
    }

    void push(item i) {
        _data[_n++] = i;
        std::push_heap(_data.begin(), _data.begin()+_n, Comparitor());
    }

    item pop() {
        std::pop_heap(_data.begin(), _data.end()+_n, Comparitor());
        return _data[_n--];
    }

    int _n;
    T  *_data;
};
