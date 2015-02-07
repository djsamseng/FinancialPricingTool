#ifndef EQP_BINOMIAL_STRATEGY_H
#define EQP_BINOMIAL_STRATEGY_H

#include "BinomialStrategy.h"

template <class T>
class EQPBinomialStrategy : public BinomialStrategy<T> {
    public:
        EQPBinomialStrategy(double interest, double volatility, double delta);
    private:
};

template <class T>
EQPBinomialStrategy<T>::EQPBinomialStrategy(double interest, double volatility, double delta) : BinomialStrategy<T>(ArithBinomialType, interest, volatility, delta) {
    double v = this->_interest - 0.5 * this->_volatility * this->_volatility;
    double a = v * this->_delta;
    double b = 0.5 * sqrt(4 * this->_volatility * this->_volatility * this->_delta - 3 * v * v * this->_delta * this->_delta);

    this->_up = T(0.5 * a + b);
    this->_down = T(1.5 * a - b);
    this->_probValue = 0.5;
}
#endif
