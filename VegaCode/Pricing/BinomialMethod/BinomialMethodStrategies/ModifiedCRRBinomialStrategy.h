#ifndef MODIFIED_CRR_BINOMIAL_STRATEGY_H
#define MODIFIED_CRR_BINOMIAL_STRATEGY_H

#include <cmath>

#include "BinomialStrategy.h"


template <class T>
class ModifiedCRRBinomialStrategy : public BinomialStrategy<T> {
    public:
        ModifiedCRRBinomialStrategy(double interest, double volatility, double delta, double asset_price, double strike_price, int time_steps);
        void build();
    private:
        double _asset_price;
        double _strike_price;
        int _time_steps;
};

template <class T>
ModifiedCRRBinomialStrategy<T>::ModifiedCRRBinomialStrategy(double interest, double volatility, double delta, double asset_price, double strike_price, int time_steps) : BinomialStrategy<T>(MultBinomialType, interest, volatility, delta), _asset_price(asset_price), _strike_price(strike_price), _time_steps(time_steps) {
    build();
}

template <class T>
void ModifiedCRRBinomialStrategy<T>::build() {
    double kN = log(_strike_price / _asset_price) / _time_steps;
    double vN = this->_volatility * sqrt(this->_delta);

    this->_up = exp(kN + vN);
    this->_down = exp(kN - vN);
    this->_probValue = (exp(this->_interest * this->_delta) - this->_down) / (this->_up - this->_down);
}
#endif
