#include <iostream>
#include <assert.h>
#include <cmath>

#include "../Pricing/BinomialMethod/binomialMethodTests.cpp"
#include "../Pricing/BlackScholes/testBlackScholes.cpp"
#include "../Models/FinancialModels/financialModelTests.cpp"
#include "../DataStructures/dataStructuresTests.cpp"


int main() {
    testBinomialStrategies();
    testBinomialMethod();
    testEuropeanOption();
    testNumericArray();
    testLattice();
    testMatrix();
    testNumericMatrix();
    testMesher();
    testPricing();
    testBlackScholes();
    return 0;
}
