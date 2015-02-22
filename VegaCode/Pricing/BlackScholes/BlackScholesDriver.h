#ifndef BLACK_SCHOLES_DRIVER_H
#define BLACK_SCHOLES_DRIVER_H

#include "BlackScholesIBVP.h"
#include "EEulerIBVPFDM.h"
#include "../../Utility/BlackScholesType.h"

template <class T>
class BlackScholesDriver {
    public:
        BlackScholesDriver() {}
		NumericMatrix<int, T> calculateOption(Option<T>* option, BlackScholesType strategy, int tSteps, int xSteps);
		T price, deltaR, vega;
};

template <class T>
NumericMatrix<int, T> BlackScholesDriver<T>::calculateOption(Option<T>* option, BlackScholesType strategy, int tSteps, int xSteps) {
	price = 0;
	deltaR = 0;
	vega = 0;
	BlackScholesIBVP<T>* ibvp = new BlackScholesIBVP<T>(option, 0, 1, 0, 1);
	EEulerIBVPFDM<T> solver(ibvp, tSteps, xSteps);
	return solver.result();
	
}

#endif
