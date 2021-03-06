#ifndef BLACK_SCHOLES_IBVP_H
#define BLACK_SCHOLES_IBVP_H

#include "../../Models/FinancialModels/Option.h"
#include "IBVP.h"
template <class T>
class BlackScholesIBVP : public IBVP<T> {
    public:
        BlackScholesIBVP(Option<T>* option, int minT, int maxT, int minX, int maxX) : IBVP<T>(minT, maxT, minX, maxX), _option(option) {}
        const T diffusion(const T& t, const T& x) const;
        const T convection(const T& t, const T& x) const;
         T zeroTerm(const T& t, const T& x) const;
        const T rightHandSide(const T& t, const T& x) const;
        const T rightBC(const T& t, const T& x) const;
        const T leftBC(const T& t, const T& x) const;
        const T initialC(const T& x) const;
        
    private:
        Option<T>* _option;
};

template <class T>
const T BlackScholesIBVP<T>::diffusion(const T& t, const T& x) const {
    double v = _option->volatility();
    return 0.5 * v * v * x * x;
}

template <class T>
const T BlackScholesIBVP<T>::convection(const T& t, const T& x) const {
    return _option->interestRate() * x;
}

template <class T>
T BlackScholesIBVP<T>::zeroTerm(const T& t, const T& x) const {
    return -1.0 * _option->interestRate();
}

template <class T>
const T BlackScholesIBVP<T>::rightHandSide(const T& t, const T& x) const {
    return 0.0;
}

template <class T>
const T BlackScholesIBVP<T>::rightBC(const T& t, const T& x) const {
    if (_option->isCall()) {
        return x - _option->strike() * exp(-1 * _option->interestRate() * (_option->expiry() - t));
    } else {
        return 0.0;
    }
}


template <class T>
const T BlackScholesIBVP<T>::leftBC(const T& t, const T& x) const {
    if (_option->isCall()) {
        return 0.0;
    } else {
        return _option->strike() * exp(_option->interestRate() * (_option->expiry() - t));
    }
}

template <class T>
const T BlackScholesIBVP<T>::initialC(const T& x) const {
    return _option->payoff(x);
}



#endif
