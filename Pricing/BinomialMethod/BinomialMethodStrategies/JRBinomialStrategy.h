#ifndef JR_BINOMIAL_STRATEGY_H
#define JR_BINOMIAL_STRATEGY_H

#include "BinomialStrategy.h"

template <class T>
class JRBinomialStrategy : public BinomialStrategy<T> {
    public:
        JRBinomialStrategy(double interest, double volatility, double delta);
    private:
};

template <class T>
JRBinomialStrategy<T>::JRBinomialStrategy(double interest, double volatility, double delta) : BinomialStrategy<T>(MultBinomialType, interest, volatility, delta) {
    this->_up = T(exp(this->_volatility * sqrt(this->_delta)));
    this->_down = T(exp(-1 * this->_volatility * sqrt(this->_delta)));
    this->_probValue = 0.5 + (this->_interest - 0.5 * this->_volatility * this->_volatility) * sqrt(this->_delta) / (2 * this->_volatility);
}
#endif
