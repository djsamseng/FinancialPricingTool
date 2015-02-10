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

