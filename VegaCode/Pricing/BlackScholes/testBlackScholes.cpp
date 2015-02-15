#include <iostream>
#include <assert.h>

#include "../../Models/FinancialModels/OptionFactory.h"
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
    opt->setExpiry(4);
    opt->setCurrentPrice(2);
    opt->setStrike(1);
    BlackScholesIBVP<double>* ibvp = new BlackScholesIBVP<double>(opt, 0, 4, 0, 5);
    EEulerIBVPFDM<double> solver(ibvp, 4, 5);
    std::cout << "Explicit Euler: " << std::endl;
    print(solver.result());
    IEulerIBVPFDM<double> s2(ibvp, 4, 5);
    std::cout << "Implicit Euler: " << std::endl;
    print(s2.result());
    std::cout << "Black Scholes Tests Complete" << std::endl;
}