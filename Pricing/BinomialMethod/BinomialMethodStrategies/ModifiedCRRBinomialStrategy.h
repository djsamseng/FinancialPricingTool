#ifndef MODIFIED_CRR_BINOMIAL_STRATEGY_H
#define MODIFIED_CRR_BINOMIAL_STRATEGY_H

#include <cmath>

#include "BinomialStrategy.h"


template <class T>
class ModifiedCRRBinomialStrategy : public BinomialStrategy<T> {
    public:
        ModifiedCRRBinomialStrategy(double interest, double volatility, double delta, double asset_price, double strike_price, int time_steps);
    private:
};

template <class T>
ModifiedCRRBinomialStrategy<T>::ModifiedCRRBinomialStrategy(double interest, double volatility, double delta, double asset_price, double strike_price, int time_steps) : BinomialStrategy<T>(MultBinomialType, interest, volatility, delta) {
    double kN = log(strike_price / asset_price) / time_steps;
    double vN = this->_volatility * sqrt(this->_delta);

    this->_up = exp(kN + vN);
    this->_down = exp(kN - vN);
    this->_probValue = (exp(this->_interest * this->_delta) - this->_down) / (this->_up - this->_down);
}
#endif
