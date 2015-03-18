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
    BlackScholesIBVP<double>* ibvp = new BlackScholesIBVP<double>(opt, 0, 1, 0, 1);
    EEulerIBVPFDM<double> solver(ibvp, 10, 10);
    std::cout << "Explicit Euler: " << std::endl;
    print(solver.result());
    IEulerIBVPFDM<double> s2(ibvp, 10, 10);
    std::cout << "Implicit Euler: " << std::endl;
    print(s2.result());
    BlackScholesDriver<double> driver;
    NumericMatrix<int, double> s3 = driver.calculateOption(opt, static_cast<BlackScholesType>(0), 10, 10);
    print(s3);
    std::cout << "Black Scholes Tests Complete" << std::endl;
}
