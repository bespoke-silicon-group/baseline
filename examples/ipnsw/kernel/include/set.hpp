#pragma once
#include <algorithm>
template<typename T, typename Comparitor>
class DynSet {
public:
    DynSet(T *data, int N):
        _data(data),
        _data_N(N),
        _n(0) {
    }

    void insert(T i) {
        _data[_n++] = i;
        std::sort(_data, _data+_n, Comparitor());
    }

    bool in(T i) {
        return std::binary_search(_data, _data+_n, i, Comparitor());
    }

    int size() const {
        return _n;
    }

    T    *_data;
    int   _n;
    int   _data_N;
};

template<typename T>
class DenseSet {
public:
    DenseSet(int *data):
        _data(data) {
    }

    void insert(T i) {
        _data[i] = 1;
    }

    bool in(T i) {
        return _data[i] == 1;
    }

    int *_data;
};

