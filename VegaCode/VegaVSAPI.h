#pragma once
#include <string>

#include "Utility\OptionType.h"
#include "Utility\BinomialStrategyType.h"


class VegaVSAPI {
public:
	std::string sayHello();
	void calculateOption(OptionType optionType, BinomialStrategyType binomialStrategy, int numberSteps, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall);
	double _price;
	double _delta;
	double _vega;
	
};