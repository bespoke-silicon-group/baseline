#pragma once
#include <algorithm>
#include <atomic>

template<typename T>
class DenseSet {
public:
    DenseSet(int *data, int size) :
        _data(data),
        _size(size){
    }

    void insert(T i) {
        _data[word(i)] |= (1 << bit(i));
        _size += 1;
    }

    void remove(T i) {
        int *ptr = &_data[word(i)];
        int r    = 1 << bit(i);
        _data[word(i)] &= ~(1<<bit(i));
        _size -= 1;
        return;
    }    

    bool in(T i) {
        return _data[word(i)] & (1 << bit(i));
    }

    int word(T i) const {
        return  i >> 5;
    }

    int bit(T i) const {
        return i & 31;
    }
    bool empty() const {
        return _size == 0;
    }
    int *_data;
    int _size;
};
