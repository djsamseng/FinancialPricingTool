#ifndef TRG_BINOMIAL_STRATEGY_H
#define TRG_BINOMIAL_STRATEGY_H

#include "BinomialStrategy.h"

template <class T>
class TRGBinomialStrategy : public BinomialStrategy<T> {
    public:
        TRGBinomialStrategy(double interest, double volatility, double delta);
        void build();
    private:
};

template <class T>
TRGBinomialStrategy<T>::TRGBinomialStrategy(double interest, double volatility, double delta) : BinomialStrategy<T>(ArithBinomialType, interest, volatility, delta) {
    build();
}

template <class T>
void TRGBinomialStrategy<T>::build() {
    double v = this->_interest - 0.5 * this->_volatility * this->_volatility;

    this->_up = this->_down = T(sqrt(this->_volatility * this->_volatility * this->_delta + v * v * this->_delta * this->_delta));
    this->_probValue = 0.5 + 0.5 * v * this->_delta / this->_up;
}

#endif
