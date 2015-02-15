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
       
        virtual void constructLattice(int size, const T& initial_price, Option<T>* option) = 0;
        virtual T price() const = 0;
        virtual T delta() const = 0;
        virtual T vega(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const = 0;
        
        const DS::Array<int, NumericArray<int, T> >& lattice() const { return _lattice; }
           
        void printLattice() const { _lattice.print(); }
    protected:
        Lattice<int, std::pair<T, T> > _lattice;
        BinomialStrategy<T> *_strategy;
        double _rate;//discounting
        
        void buildLattice(int size, const T& initialUp);
        void calculatePayoff(Option<T> *option);
};

template <class T>
BinomialMethod<T>::BinomialMethod(double rate, BinomialStrategy<T> *strategy) {
    _strategy = strategy;
    _rate = rate;
}

template <class T>
void BinomialMethod<T>::buildLattice(int size, const T& initial_underlying_price) {
    _lattice = Lattice<int, std::pair<T, T> >(size);
    
    double up = _strategy->upValue();
    double down = _strategy->downValue();

    int minRow = _lattice.minIndex();
    _lattice[minRow][_lattice[minRow].minIndex()].first = initial_underlying_price;

    for (int i = _lattice.minIndex() + 1; i <= _lattice.maxIndex(); i++) {
        for (int j = _lattice[i].minIndex(); j < _lattice[i].maxIndex(); j++) {
            _lattice[i][j].first = T(down * _lattice[i-1][j].first);
            _lattice[i][j+1].first = T(up * _lattice[i-1][j].first);
        }
    }
}

template <class T>
void BinomialMethod<T>::calculatePayoff(Option<T> *option) {
    int last = this->_lattice.maxIndex();
    for (int i = this->_lattice[last].minIndex(); i <= this->_lattice[last].maxIndex(); i++) {
        this->_lattice[last][i].second = option->payoff(this->_lattice[last][i].first);
    }

    if (this->_strategy->binomialType() == ArithBinomialType) {
        std::cerr << "Not yet implemented" << std::endl;
        assert(false);
    }
}

#endif
