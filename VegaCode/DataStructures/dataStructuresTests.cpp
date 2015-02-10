#include <iostream>
#include <assert.h>

#include "Property.h"
#include "PropertySet.h"
#include "Lattice.h"
#include "NumericArray.h"

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
