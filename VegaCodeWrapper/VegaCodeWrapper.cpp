// This is the main DLL file.

#include "stdafx.h"

#include "VegaCodeWrapper.h"
using namespace VegaCodeWrap;

VegaCodeWrapper::VegaCodeWrapper() {
	api = new VegaVSAPI();
}

VegaCodeWrapper::~VegaCodeWrapper() {
	delete api;
}

System::String^ VegaCodeWrapper::sayHello() {
	std::string str = api->sayHello();
	return gcnew String(str.c_str());
}



void VegaCodeWrapper::calculateOption(int optionType, int binomialStrategy, int numberSteps, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall) {
	api->calculateOption(static_cast<OptionType>(optionType), static_cast<BinomialStrategyType>(binomialStrategy), numberSteps, interestRate, volatility, strike, expiry, currentPrice, costOfCarry, isCall);
	_price = api->_price;
	_delta = api->_delta;
	_vega = api->_vega;
}

