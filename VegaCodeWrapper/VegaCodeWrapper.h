// VegaCodeWrapper.h

#pragma once

#include "C:\Users\Sengs\Documents\Projects\Vega\VegaCode\VegaVSAPI.h"
#include <string>
#include <iostream>

using namespace System;

namespace VegaCodeWrap {

	public ref class VegaCodeWrapper
	{
		// TODO: Add your methods for this class here.
	public:
		VegaCodeWrapper();
		~VegaCodeWrapper();
		System::String^ sayHello();
		double _price;
		double _delta;
		double _vega;
		void calculateOption(int optionType, int binomialStrategy, int numberSteps, double interestRate, double volatility, double strike, double expiry, double currentPrice, double costOfCarry, bool isCall);
	private:
		VegaVSAPI *api;
	};
}
