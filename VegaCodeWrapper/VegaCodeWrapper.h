// VegaCodeWrapper.h

#pragma once
#include <string>
#include <iostream>
#include "..\VegaCode\Pricing\BinomialMethod\BinomialMethodDriver.h"
#include "..\VegaCode\Pricing\BlackScholes\BlackScholesDriver.h"
#include "..\VegaCode\Models\FinancialModels\OptionFactory.h"


using namespace System;

namespace VegaCodeWrap {

	public ref class VegaCodeWrapper
	{
		// TODO: Add your methods for this class here.
	public:
		VegaCodeWrapper();
		~VegaCodeWrapper();

		array<double, 2>^ _price_data;
		
		void setOption(int optionType, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall);
		void calculateOptionBinomial(int strategyType, int numberSteps);
		void calculateOptionBlackScholes(int strategyType, int tSteps, int xSteps);

		double _price;
		double _delta;
		double _vega;
		Option<double>* _option;

	private:
	};
}
