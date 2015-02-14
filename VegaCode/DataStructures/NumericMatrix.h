#ifndef NUMERIC_MATRIX_H
#define NUMERIC_MATRIX_H

#include <assert.h>

#include "Matrix.h"
#include "MatrixStructure.h"

template <class I, class V, class S=MatrixStructure<V> >
class NumericMatrix : public Matrix<I, V, S> {
    public:
       NumericMatrix() : Matrix<I, V, S>() {}
       NumericMatrix(I rows, I cols) : Matrix<I, V, S>(rows, cols) {}
       NumericMatrix(const Matrix<I, V, S>& s) : Matrix<I, V, S>(s) {}
       virtual ~NumericMatrix() {}

       NumericMatrix<I, V, S>& operator=(const NumericMatrix<V, I, S>& s);
       NumericMatrix<I, V, S> operator-() const;
       NumericMatrix<I, V, S> operator+(const NumericMatrix<V, I, S>& mat) const;
       NumericMatrix<I, V, S> operator-(const NumericMatrix<V, I, S>& mat) const;
       NumericMatrix<I, V, S> operator*(const NumericMatrix<V, I, S>& mat) const;
       NumericArray<I, V> operator*(const NumericArray<I, V>& vec) const;

    private:

};

template <class I, class V, class S>
NumericMatrix<I, V, S>& NumericMatrix<I, V, S>::operator=(const NumericMatrix<V, I, S>& s) {
    if (this != &s) {
        Matrix<I, V, S>::operator=(s);
    }
    return *this;
}
template <class I, class V, class S>
NumericMatrix<I, V, S> NumericMatrix<I, V, S>::operator-() const {
    NumericMatrix<I, V, S> result(this->numRows(), this->numCols());
    for (I i = this->minRowIndex(); i <= this->maxRowIndex(); i++) {
        for (I j = this->minColIndex(); j <= this->maxColIndex(); j++) {
            result(i,j) = -1 * (*this)(i, j);
        }
    }
    return result;
}

template <class I, class V, class S>
NumericMatrix<I, V, S> NumericMatrix<I, V, S>::operator+(const NumericMatrix<V, I, S>& mat) const {
    assert(this->numRows() == mat.numRows());
    assert(this->numCols() == mat.numCols());
    assert(this->minRowIndex() == mat.minRowIndex());
    assert(this->minColIndex() == mat.minColIndex());

    NumericMatrix<I, V, S> result(this->numRows(), this->numCols());
    for (I i = this->minRowIndex(); i <= this->maxRowIndex(); i++) {
        for (I j = this->minColIndex(); j <= this->maxColIndex(); j++) {
            result(i,j) = (*this)(i, j) + mat(i, j);
        }
    }
    return result;
}

 
template <class I, class V, class S>
NumericMatrix<I, V, S> NumericMatrix<I, V, S>::operator-(const NumericMatrix<V, I, S>& mat) const {
    assert(this->numRows() == mat.numRows());
    assert(this->numCols() == mat.numCols());
    assert(this->minRowIndex() == mat.minRowIndex());
    assert(this->minColIndex() == mat.minColIndex());

    NumericMatrix<I, V, S> result(this->numRows(), this->numCols());
    for (I i = this->minRowIndex(); i <= this->maxRowIndex(); i++) {
        for (I j = this->minColIndex(); j <= this->maxColIndex(); j++) {
            result(i,j) = (*this)(i, j) - mat(i, j);
        }
    }
    return result;
}
 
template <class I, class V, class S>
NumericMatrix<I, V, S> NumericMatrix<I, V, S>::operator*(const NumericMatrix<V, I, S>& mat) const {
    assert(this->numCols() == mat.numRows());
    assert(this->minRowIndex() == mat.minRowIndex());
    assert(this->minColIndex() == mat.minColIndex());

    NumericMatrix<I, V, S> result(this->numRows(), mat.numCols());
    for (I r = result.minRowIndex(); r <= result.maxRowIndex(); r++) {
        for (I i = result.minColIndex(); i <= result.maxColIndex(); i++) {
            result(r, i) = 0.0;
            for (I j = this->minColIndex(); j <= this->maxColIndex(); j++) {
                result(r,i) += (*this)(r, j) + mat(j, i);
            }
        }
    }
    return result;
}
 
template <class I, class V, class S>
NumericArray<I, V> NumericMatrix<I, V, S>::operator*(const NumericArray<I, V>& vec) const {
    assert(this->numCols() == vec.size());
    assert(this->minColIndex() == vec.minIndex());

    NumericArray<I, V> result(this->numRows());
    for (I i = this->minRowIndex(); i <= this->maxRowIndex(); i++) {
        for (I j = this->minColIndex; j <= this->maxColIndex(); j++) {
            result[i] += (*this)(i, j) + vec[j];
        }
    }
    return result;
}

#endif
