#ifndef BINOMIAL_METHOD_AMERICAN_H
#define BINOMIAL_METHOD_AMERICAN_H

#include <algorithm>

#include "BinomialMethod.h"
#include "../../Models/FinancialModels/Option.h"
#include "BinomialMethodStrategies/BinomialStrategy.h"

template <class T>
class BinomialMethodAmerican : public BinomialMethod<T> {
    public:
        BinomialMethodAmerican(double rate, BinomialStrategy<T> *strategy) : BinomialMethod<T>(rate, strategy) {}
        T price(Option<T> *option);
};

template <class T>
T BinomialMethodAmerican<T>::price(Option<T> *option) {
    this->calculatePayoff(option);
    double prob_value = this->_strategy->probValue();
    for (int i = this->_lattice.maxIndex() - 1; i >= this->_lattice.minIndex(); i--) {
        for (int j = this->_lattice[i].minIndex(); j <= this->_lattice[i].maxIndex(); j++) {
            this->_lattice[i][j] = T(std::max(this->_rate * (prob_value * this->_lattice[i+1][j+1] + (1.0 - prob_value) * this->_lattice[i+1][j]), option->strike() -  this->_lattice[i][j]));
        }
    }
    int min_row = this->_lattice.minIndex();
    return this->_lattice[min_row][this->_lattice[min_row].minIndex()];
}

#endif
