#ifndef BINOMIAL_METHOD_EUROPEAN_H
#define BINOMIAL_METHOD_EUROPEAN_H

#include "BinomialMethod.h"

template <class T>
class BinomialMethodEuropean : public BinomialMethod<T> {
    public:
        BinomialMethodEuropean(double rate, BinomialStrategy<T> *strategy) : BinomialMethod<T>(rate, strategy) {}
        void constructLattice(int size, const T& initial_price, Option<T>* option);
        T price() const;
        BinomialMethod<T>* copy() const;
};

template <class T>
void BinomialMethodEuropean<T>::constructLattice(int size, const T& initial_price, Option<T>* option) {
    this->buildLattice(size, initial_price);
    this->calculatePayoff(option);

    double probValue = this->_strategy->probValue();
    
    for (int i = this->_lattice.maxIndex() - 1; i >= this->_lattice.minIndex(); i--) {
        for (int j = this->_lattice[i].minIndex(); j <= this->_lattice[i].maxIndex(); j++) {
            this->_lattice[i][j].second = T(this->_rate * (probValue * this->_lattice[i+1][j+1].second + (1.0 - probValue) * this->_lattice[i+1][j].second));
        }
    }
}

template <class T>
T BinomialMethodEuropean<T>::price() const {
    int minRow = this->_lattice.minIndex();
    return this->_lattice[minRow][this->_lattice[minRow].minIndex()].second;
}

template <class T>
BinomialMethod<T>* BinomialMethodEuropean<T>::copy() const {
    return new BinomialMethodEuropean<T>(this->_rate, this->_strategy);
}

#endif
