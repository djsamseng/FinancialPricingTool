#ifndef BINOMIAL_METHOD_EUROPEAN_H
#define BINOMIAL_METHOD_EUROPEAN_H

#include "BinomialMethod.h"

template <class T>
class BinomialMethodEuropean : public BinomialMethod<T> {
    public:
        BinomialMethodEuropean(double rate, BinomialStrategy<T> *strategy) : BinomialMethod<T>(rate, strategy) {}
        T price(Option<T>* option);
};

template <class T>
T BinomialMethodEuropean<T>::price(Option<T>* opt) {
    this->calculatePayoff(opt);

    double probValue = this->_strategy->probValue();
    
    for (int i = this->_lattice.maxIndex() - 1; i >= this->_lattice.minIndex(); i--) {
        for (int j = this->_lattice[i].minIndex(); j <= this->_lattice[i].maxIndex(); j++) {
            this->_lattice[i][j] = T(this->_rate * (probValue * this->_lattice[i+1][j+1] + (1.0 - probValue) * this->_lattice[i+1][j]));
        }
    }
    int minRow = this->_lattice.minIndex();
    return this->_lattice[minRow][this->_lattice[minRow].minIndex()];
}

#endif
