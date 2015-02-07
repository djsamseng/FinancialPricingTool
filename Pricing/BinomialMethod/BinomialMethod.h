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
    //Workflow: Constructor, buildLattice, calculatePayoff, price
    public:
        BinomialMethod(double rate, BinomialStrategy<T> *strategy);
        
        void buildLattice(int size, const T& initialUp);
        void calculatePayoff(Option<T>* option);
        T price();
        
        const NumericArray<int, T>& operator[](int index) const { return _lattice[index]; }
        NumericArray<int, T>& operator[](int index);

        const Array<int, NumericArray<int, T> >& lattice() const { return _lattice; }
           
        void printLattice() const { _lattice.print(); }
    private:
        Lattice<int, T> _lattice;
        BinomialStrategy<T> *_strategy;
        double _rate;//discounting
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
void BinomialMethod<T>::calculatePayoff(Option<T> *opt) {
    int last = _lattice.maxIndex();
    for (int i = _lattice[last].minIndex(); i <= _lattice[last].maxIndex(); i++) {
        _lattice[last][i] = opt->payoff(_lattice[last][i]);
    }
}

template <class T>
T BinomialMethod<T>::price() {
    if (_strategy->binomialType() == ArithBinomialType) {
        std::cerr << "Not yet implemented" << std::endl;
        assert(false);
    }
    double probValue = _strategy->probValue();
    
    for (int i = _lattice.maxIndex() - 1; i >= _lattice.minIndex(); i--) {
        for (int j = _lattice[i].minIndex(); j <= _lattice[i].maxIndex(); j++) {
            _lattice[i][j] = T(_rate * (probValue * _lattice[i+1][j+1] + (1.0 - probValue) * _lattice[i+1][j]));
        }
    }
    int minRow = _lattice.minIndex();
    return _lattice[minRow][_lattice[minRow].minIndex()];
}


template <class T>
NumericArray<int, T>& BinomialMethod<T>::operator[](int index) {
    if (index != _lattice.maxIndex()) {
        std::cerr << "Cannot modify non last index" << std::endl;
        assert(false);
    }
    return _lattice[_lattice.maxIndex()];
}

#endif
