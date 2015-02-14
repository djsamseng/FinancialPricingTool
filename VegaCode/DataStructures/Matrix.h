#ifndef MATRIX_H
#define MATRIX_H

#include "MatrixStructure.h"

template <class I, class V, class S=MatrixStructure<V> >
class Matrix {
    public:
        Matrix() : _row_start(0), _col_start(0) {}
        Matrix(I rows, I cols) : _row_start(0), _col_start(0), _matrix(rows, cols) {}
        Matrix(const Matrix<I, V, S>& s) : _matrix(s._matrix), _row_start(s._row_start), _col_start(s._col_start) {}

        I minRowIndex() const { return _row_start; }
        I minColIndex() const { return _col_start; }
        I maxRowIndex() const { return _row_start + numRows() - 1; }
        I maxColIndex() const { return _col_start + numCols() - 1; }

        I numRows() const { return _matrix.numRows(); }
        I numCols() const { return _matrix.numCols(); }

        V& operator()(I row, I col) { return _matrix[row][col]; }
        const V& operator()(I row, I col) const { return _matrix[row][col]; }
        Matrix<I, V, S>& operator=(const Matrix<I, V, S>& s);

    private:
        S _matrix;
        I _row_start;
        I _col_start;
};

template <class I, class V, class S>
Matrix<I, V, S>& Matrix<I, V, S>::operator=(const Matrix<I, V, S>& s) {
    if (this != &s) {
        _matrix = s._matrix;
        _row_start = s._row_start;
        _col_start = s._col_start;
    }
    return *this;
}

#endif
