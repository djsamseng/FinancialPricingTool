// This is the main DLL file.

#include "stdafx.h"

#include "VegaCodeWrapper.h"

using namespace VegaCodeWrap;

VegaCodeWrapper::VegaCodeWrapper() {
	_option = NULL;
}

VegaCodeWrapper::~VegaCodeWrapper() {
	if (_option != NULL) {
		delete _option;
		_option = NULL;
	}
}

void VegaCodeWrapper::setOption(int optionType, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall) {
	if (_option != NULL) {
		delete _option;
		_option = NULL;
	}
	_option = OptionFactory::getOption<double>(static_cast<OptionType>(optionType));
	_option->set(interestRate, volatility, strike, expiry, currentPrice, costOfCarry, isCall);
}

void VegaCodeWrapper::calculateOptionBinomial(int binomialStrategy, int numberSteps) {
	if (_option != NULL) {
		BinomialMethodDriver<double> driver;
		driver.calculateOption(_option, static_cast<BinomialStrategyType>(binomialStrategy), numberSteps);
		_price = driver.price();
		_delta = driver.deltaR();
		_vega = driver.vega();
	}
}

void VegaCodeWrapper::calculateOptionBlackScholes(int strategyType, int tSteps, int xSteps) {
	if (_option != NULL) {
		BlackScholesDriver<double> driver;
		NumericMatrix<int, double> result = driver.calculateOption(_option, static_cast<BlackScholesType>(strategyType), tSteps, xSteps);
		_price = driver.price();
		_delta = driver.deltaR();
		_vega = driver.vega();
		_price_data = gcnew array < double, 2 >(result.numRows(), result.numCols());
		for (int i = 0; i <= result.maxRowIndex(); i++) {
			for (int j = 0; j <= result.maxColIndex(); j++) {
				_price_data[i, j] = result(i, j);
			}
		}
	}
}

