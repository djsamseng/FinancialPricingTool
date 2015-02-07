#include <iostream>
#include <assert.h>
#include <cmath>

#include "../Pricing/BinomialMethod/binomialMethodTests.cpp"
#include "../Models/FinancialModels/financialModelTests.cpp"
#include "../DataStructures/dataStructuresTests.cpp"



int main() {
    testBinomialStrategies();
    testBinomialMethod();
    testEuropeanOption();
    testNumericArray();
    testLattice();
    return 0;
}
