#ifndef BINOMIAL_METHOD_AMERICAN_H
#define BINOMIAL_METHOD_AMERICAN_H

#include <algorithm>
#include <map>
#include <assert.h>

#include "BinomialMethod.h"
#include "../../Models/FinancialModels/Option.h"
#include "BinomialMethodStrategies/BinomialStrategy.h"

template <class T>
class BinomialMethodAmerican : public BinomialMethod<T> {
    public:
        BinomialMethodAmerican(double rate, BinomialStrategy<T> *strategy) : BinomialMethod<T>(rate, strategy) {}
        void constructLattice(int size, const T& initial_price, Option<T>* option);
        T price() const;
        BinomialMethod<T>* copy() const;

};

template <class T>
void BinomialMethodAmerican<T>::constructLattice(int size, const T& initial_price, Option<T>* option) {
    this->buildLattice(size, initial_price);
    this->calculatePayoff(option);

    double prob_value = this->_strategy->probValue();
    for (int i = this->_lattice.maxIndex() - 1; i >= this->_lattice.minIndex(); i--) {
        for (int j = this->_lattice[i].minIndex(); j <= this->_lattice[i].maxIndex(); j++) {
            this->_lattice[i][j].second = T(std::max(this->_rate * (prob_value * this->_lattice[i+1][j+1].second + (1.0 - prob_value) * this->_lattice[i+1][j].second), option->strike() -  this->_lattice[i][j].first));
        }
    }
}

template <class T>
T BinomialMethodAmerican<T>::price() const {
    int min_index = this->_lattice.minIndex();
    return this->_lattice[min_index][this->_lattice[min_index].minIndex()].second;
}

template <class T>
BinomialMethod<T>* BinomialMethodAmerican<T>::copy() const {
    return new BinomialMethodAmerican<T>(this->_rate, this->_strategy);
}
#endif
