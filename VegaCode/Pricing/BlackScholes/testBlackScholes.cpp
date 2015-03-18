#include <iostream>
#include <assert.h>

#include "../../Models/FinancialModels/OptionFactory.h"
#include "BlackScholesDriver.h"
#include "BlackScholesIBVP.h"
#include "EEulerIBVPFDM.h"
#include "IEulerIBVPFDM.h"
#include "../../Utility/OptionPropertyKeyType.h"
#include "../../DataStructures/PropertySet.h"
#include "../../../Testing/testFunctions.cpp"

void testBlackScholes() {
    std::cout << "Testing Black Scholes" << std::endl;
    Option<double>* opt = OptionFactory::getOption<double>(EuropeanOptionType);
    opt->setIsCall(true);
    opt->setExpiry(1.0);
    opt->setStrike(0.5);
    opt->setInterestRate(0.05);
    opt->setVolatility(0.2);
    opt->setCurrentPrice(1);
    
    BlackScholesDriver<double> driver;
    NumericMatrix<int, double> s = driver.calculateOption(opt, static_cast<BlackScholesType>(0), 10, 10);
    std::cout << "Explicit Euler" << std::endl;
    print(s);

    opt->setStrike(150);
    opt->setCurrentPrice(150);
    s = driver.calculateOption(opt, static_cast<BlackScholesType>(1), 10, 10);
    std::cout << "Explicit Euler" << std::endl;
    print(s);

    delete opt;
    std::cout << "Black Scholes Tests Complete" << std::endl;
}
