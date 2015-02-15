#ifndef MESHER_H
#define MESHER_H

#include "NumericArray.h"

//T must be a numeric type
template <class T>
class Mesher {
    public:
        Mesher() {}
        Mesher(const T& xLeft, const T& xRight, const T& tLeft, const T& tRight) : _x_left(xLeft), _x_right(xRight), _t_left(tLeft), _t_right(tRight) {}

        NumericArray<int, T> xArr(int size) { return createArray(size, _x_left, _x_right); }
        NumericArray<int, T> yArr(int size) { return createArray(size, _t_left, _t_right); }
        
        const T& xStep(int n) const { return (_x_right - _x_left) / double(n); }
        const T& tStep(int n) const { return (_t_right - _t_left) / double(n); }

        Mesher<T>& operator=(const Mesher<T>& s);
    private:
        T _x_left;
        T _x_right;
        T _t_left;
        T _t_right;

        NumericArray<int, T> createArray(int size, const T& a, const T& b);
};

template <class T>
NumericArray<int, T> Mesher<T>::createArray(int size, const T& a, const T& b) {
    T step_size = (b - a) / double(size);
    NumericArray<int, T> vec(size);
    vec[vec.minIndex()] = _x_left;
    for (int i = vec.minIndex() + 1; i <= vec.maxIndex(); i++) {
        vec[i] = vec[i-1] + step_size;
    }
    return vec;
}

template <class T>
Mesher<T>& Mesher<T>::operator=(const Mesher<T>& s) {
    if (this != &s) {
        _x_left = s._x_left;
        _x_right = s._x_right;
        _t_left = s._t_left;
        _t_right = s._t_right;
    }
    return *this;
}

#endif
