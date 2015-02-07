#include <iostream>
#include <assert.h>

#include "Pricing.cpp"

void testPricing() {
    std::cout << "Testing Pricing (FV, PV)" << std::endl;
    double err = 0.1;
    assert(abs(Pricing::futureValue(50.0, 1, 0.01) - 50.05) < err);
    std::cout << "Pricing Testing (FV, PV) Complete" << std::endl;
}
    

int main() {
    testPricing();
    return 0;
}
