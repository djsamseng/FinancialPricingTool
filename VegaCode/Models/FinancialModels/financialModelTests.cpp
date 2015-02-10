#include <iostream>
#include <assert.h>
#include <cmath>
#include "EuropeanOption.h"



void testEuropeanOption() {
    std::cout << "Testing European Option" << std::endl;
    EuropeanOption<double> a;
    double err = 0.1;
    assert(abs(a.isCall() - 0) < err);
    a.setIsCall(1.0);
    assert(abs(a.isCall() - 1) < err);
    assert(abs(a.price() - 2.13) < err);
    a.setIsCall(0.0);
    a.setCurrentPrice(100);
    a.setStrike(95);
    a.setExpiry(0.5);
    a.setInterestRate(0.1);
    a.setVolatility(0.2);
    a.setCostOfCarry(0.05);
    assert(abs(a.price() - 2.46) < err);
    std::cout << "European Option Tests Complete" << std::endl;

}
