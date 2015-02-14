#ifndef MATRIX_STRUCTURE_H
#define MATRIX_STRUCTURE_H

#include "ArrayStructure.h"

template <class T>
class MatrixStructure {
    public:
        MatrixStructure() {}
        MatrixStructure(size_t rows, size_t cols);
        MatrixStructure(const MatrixStructure<T>& s) : _matrix(s._matrix) {}

        size_t numRows() const { return _matrix.size(); }
        size_t numCols() const;

        ArrayStructure<T>& operator[](size_t index) { return _matrix[index]; }
        const ArrayStructure<T>& operator[](size_t index) const { return _matrix[index]; }
        MatrixStructure<T>& operator=(const MatrixStructure<T>& s);

    private:
        ArrayStructure<ArrayStructure<T> > _matrix;
};

template <class T>
MatrixStructure<T>::MatrixStructure(size_t rows, size_t cols) {
    _matrix = ArrayStructure<ArrayStructure<T> >(rows);
    for (int i = 0; i < _matrix.size(); i++) {
        _matrix[i] = ArrayStructure<T>(cols);
    }
}

template <class T>
size_t MatrixStructure<T>::numCols() const {
    if (_matrix.size() > 0) {
        return _matrix[0].size();
    }
    return 0;
}

template <class T>
MatrixStructure<T>& MatrixStructure<T>::operator=(const MatrixStructure<T>& s) {
    if (this != &s) {
        _matrix = s._matrix;
    }
    return *this;
}

#endif
