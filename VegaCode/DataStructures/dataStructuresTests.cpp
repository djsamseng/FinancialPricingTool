#include <iostream>
#include <assert.h>

#include "Property.h"
#include "PropertySet.h"
#include "Lattice.h"
#include "NumericArray.h"
#include "Matrix.h"
#include "NumericMatrix.h"
#include "Mesher.h"

void testNumericArray() {
    std::cout << "Running NumericArray Tests" << std::endl;
    NumericArray<int, int> a;
    a.pushBack(2);
    assert(a[0] == 2);
    assert(a.size() == 1);
    assert(a.minIndex() == 0);
    assert(a.maxIndex() == 0);
    a.pushBack(3);
    assert(a.maxIndex() == 1);
    a.popBack();
    a.popBack();
    assert(a.size() == 0);
    assert(a.minIndex() == 0);
    assert(a.maxIndex() == -1);
    bool result = true;
    if (result) {
        std::cout << "NumericArray Tests Successful" << std::endl;
    }
}

void testLattice() {
    std::cout << "Running Lattice Tests" << std::endl;
    Lattice<int, int> a;
    Lattice<int, int> b(3);
    bool result = true;
    if (result) {
        std::cout << "Lattice Tests Successful" << std::endl;
    }
}

void testMatrix() {
    std::cout << "Running Matrix Tests" << std::endl;
    Matrix<int, int> a;
    Matrix<int, double> b(5, 5);
    double ep = 0.1;
    assert(-ep < b(3,4)  && b(3,4) < ep);
    b(3,4) = 2.0;
    assert(2.0 - ep < b(3,4) && b(3,4) < 2.0 + ep);
    std::cout << "Matrix Tests Successful" << std::endl;
}

void testNumericMatrix() {
    std::cout << "Running NumericMatrix Tests" << std::endl;
    NumericMatrix<int, int> a;
    NumericMatrix<int, double> b(3,4);
    b(1,0) = 2;
    b = -b;
    double ep = 0.1;
    assert(-2 - ep < b(1,0) && b(1,0) < -2 + ep);
    std::cout << "NumericMatrix Tests Successful" << std::endl;
}

void testMesher() {
    std::cout << "Running Mesher Tests" << std::endl;
    Mesher<int> a;
    Mesher<int> b(5,8,0,100);
    b.xArr(3);
    b.xArr(7);
    b.yArr(5);
    std::cout << "Mesher Tests Successful" << std::endl;
}
