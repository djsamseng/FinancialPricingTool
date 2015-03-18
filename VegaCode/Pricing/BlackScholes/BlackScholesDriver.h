#ifndef BLACK_SCHOLES_DRIVER_H
#define BLACK_SCHOLES_DRIVER_H

#include "BlackScholesIBVP.h"
#include "EEulerIBVPFDM.h"
#include "IEulerIBVPFDM.h"
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
	BlackScholesIBVP<T>* ibvp = new BlackScholesIBVP<T>(option, 0, option->expiry(), 0, 2 * option->currentPrice());
    if (strategy == EEulerBlackScholesType) {
        EEulerIBVPFDM<T> solver(ibvp, tSteps, xSteps);
        return solver.result();
    } else {
        IEulerIBVPFDM<T> solver(ibvp, tSteps, xSteps);
        return solver.result();
    }
}

#endif
