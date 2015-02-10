#include "VegaVSAPI.h"
#include "Pricing\BinomialMethod\BinomialMethodDriver.h"

std::string VegaVSAPI::sayHello() {
	return "Hello from C++!";
}

void VegaVSAPI::calculateOption(OptionType optionType, BinomialStrategyType binomialStrategy, int numberSteps, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall) {
	BinomialMethodDriver<double> driver;
	driver.calculateOption(optionType, binomialStrategy, numberSteps, interestRate, volatility, strike, expiry, currentPrice, costOfCarry, isCall, _price, _delta, _vega);
}