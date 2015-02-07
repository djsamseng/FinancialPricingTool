#ifndef BINOMIAL_METHOD_H
#define BINOMIAL_METHOD_H

#include <iostream>
#include <cmath>
#include <assert.h>

#include "BinomialMethodStrategies/BinomialStrategy.h"
#include "../../DataStructures/NumericArray.h"
#include "../../DataStructures/Lattice.h"
#include "../../Models/FinancialModels/Option.h"

template <class T>
class BinomialMethod {
    //Workflow: Constructor, buildLattice, price
    public:
        BinomialMethod(double rate, BinomialStrategy<T> *strategy);
        
        void buildLattice(int size, const T& initialUp);
        virtual T price(Option<T>* option) = 0;
        
        const NumericArray<int, T>& operator[](int index) const { return _lattice[index]; }
        NumericArray<int, T>& operator[](int index);

        const Array<int, NumericArray<int, T> >& lattice() const { return _lattice; }
           
        void printLattice() const { _lattice.print(); }
    protected:
        Lattice<int, T> _lattice;
        BinomialStrategy<T> *_strategy;
        double _rate;//discounting

        void calculatePayoff(Option<T> *option);
};

template <class T>
BinomialMethod<T>::BinomialMethod(double rate, BinomialStrategy<T> *strategy) {
    _strategy = strategy;
    _rate = rate;
}

template <class T>
void BinomialMethod<T>::buildLattice(int size, const T& initial_underlying_price) {
    _lattice = Lattice<int, T>(size);
    
    double up = _strategy->upValue();
    double down = _strategy->downValue();

    int minRow = _lattice.minIndex();
    _lattice[minRow][_lattice[minRow].minIndex()] = initial_underlying_price;

    for (int i = _lattice.minIndex() + 1; i <= _lattice.maxIndex(); i++) {
        for (int j = _lattice[i].minIndex(); j < _lattice[i].maxIndex(); j++) {
            _lattice[i][j] = T(down * _lattice[i-1][j]);
            _lattice[i][j+1] = T(up * _lattice[i-1][j]);
        }
    }
}

template <class T>
NumericArray<int, T>& BinomialMethod<T>::operator[](int index) {
    if (index != _lattice.maxIndex()) {
        std::cerr << "Cannot modify non last index" << std::endl;
        assert(false);
    }
    return _lattice[_lattice.maxIndex()];
}

template <class T>
void BinomialMethod<T>::calculatePayoff(Option<T> *option) {
    int last = this->_lattice.maxIndex();
    for (int i = this->_lattice[last].minIndex(); i <= this->_lattice[last].maxIndex(); i++) {
        this->_lattice[last][i] = option->payoff(this->_lattice[last][i]);
    }

    if (this->_strategy->binomialType() == ArithBinomialType) {
        std::cerr << "Not yet implemented" << std::endl;
        assert(false);
    }
}
#endif
