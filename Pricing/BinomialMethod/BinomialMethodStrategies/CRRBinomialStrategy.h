#ifndef CRR_BINOMIAL_STRATEGY_H
#define CRR_BINOMIAL_STRATEGY_H

#include <cmath>

#include "BinomialStrategy.h"

template <class T>
class CRRBinomialStrategy : public BinomialStrategy<T> {
    public:
        CRRBinomialStrategy(double interest, double volatility, double delta);
        void build();
    private:
};
template <class T>
CRRBinomialStrategy<T>::CRRBinomialStrategy(double interest, double volatility, double delta) : BinomialStrategy<T>(MultBinomialType, interest, volatility, delta) {
    build();
}

template <class T>
void CRRBinomialStrategy<T>::build() {
    this->_up = T(exp((this->_interest - 0.5 * this->_volatility * this->_volatility) * this->_delta + this->_volatility * sqrt(this->_delta)));
    this->_down = T(exp((this->_interest - 0.5 * this->_volatility * this->_volatility) * this->_delta - this->_volatility * sqrt(this->_delta)));
    this->_probValue = 0.5;
}
#endif 
