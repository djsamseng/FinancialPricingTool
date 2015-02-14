#include <iostream>
#include <assert.h>
#include <cmath>

#include "../VegaCode/DataStructures/Matrix.h"

template <class I, class V, class S>
void print(const Matrix<I, V, S>& mat) {
    for (I i = mat.minRowIndex(); i <= mat.maxRowIndex(); i++) {
        for (I j = mat.minColIndex(); j <= mat.maxColIndex(); j++) {
            std::cout << mat(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

template <class I, class V, class S>
void print(const Array<I, V, S>& ar) {
    for (I i = ar.minIndex(); i <= ar.maxIndex(); i++) {
        std::cout << ar[i] << " ";
    }
    std::cout << std::endl;
}
