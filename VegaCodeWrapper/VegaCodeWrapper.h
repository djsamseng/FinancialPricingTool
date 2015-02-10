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
	private:
		VegaVSAPI *api;
	};
}
