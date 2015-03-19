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
        virtual ~BinomialMethod() {} 
         

        virtual void constructLattice(int size, const T& initial_price, Option<T>* option) = 0;
        virtual T price() const = 0;
        T delta() const;
        T gamma() const;
        T vega(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const;
        T rho(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const;
         
        const DS::Array<int, NumericArray<int, T> >& lattice() const { return _lattice; }
           
        void printLattice() const { _lattice.print(); }
    protected:
        Lattice<int, std::pair<T, T> > _lattice;
        BinomialStrategy<T> *_strategy;
        double _rate;//discounting
        
        void buildLattice(int size, const T& initialUp);
        void calculatePayoff(Option<T> *option);
        virtual BinomialMethod<T>* copy() const = 0; //Copies type strategy and rate but not lattice

        T delta(int offset) const;

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

template <class T>
T BinomialMethod<T>::delta() const {
    return delta(0);    
}

template <class T>
T BinomialMethod<T>::delta(int offset) const {
    int time_index = this->_lattice.minIndex() + 1 + offset;
    assert(time_index <= this->_lattice.maxIndex());

    int down_index = this->_lattice[time_index].minIndex();
    assert(down_index + 1 <= this->_lattice[time_index].maxIndex());
    assert(time_index == 1 + offset && down_index == 0);
    return (this->_lattice[time_index][down_index + 1].second - this->_lattice[time_index][down_index].second) / (this->_lattice[time_index][down_index + 1].first - this->_lattice[time_index][down_index].first);

}

template <class T>
T BinomialMethod<T>::gamma() const {
    int time_index = this->_lattice.minIndex() + 1;
    int down_index = this->_lattice[time_index].minIndex();
    return (delta(1) - delta(0)) / (this->_lattice[time_index][down_index + 1].first - this->_lattice[time_index][down_index].first);
}


template <class T>
T BinomialMethod<T>::vega(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const {
    double delta_volatility = 0.01;
    double original_volatility = strategy->volatility();

    strategy->setVolatility(original_volatility + delta_volatility);
    strategy->build();
    
    BinomialMethod<T> *other = this->copy();
    int min_index = this->_lattice.minIndex();
    
    other->constructLattice(this->_lattice.size(), this->_lattice[min_index][this->_lattice[min_index].minIndex()].first, option);
    T price_high = other->price();
    
    strategy->setVolatility(original_volatility - delta_volatility);
    strategy->build();
    other->constructLattice(this->_lattice.size(), this->_lattice[min_index][this->_lattice[min_index].minIndex()].first, option);
    T price_low = other->price();

    strategy->setVolatility(original_volatility);
    strategy->build();
    delete other;
    return (price_high - price_low) / (2 * delta_volatility);
}

template <class T>
T BinomialMethod<T>::rho(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const {
    double delta_rate = 0.01;
    double original_rate = option->interestRate();
    strategy->setInterest(original_rate + delta_rate);
    strategy->build();
    
    BinomialMethod<T> *other = this->copy();
    int min_index = this->_lattice.minIndex();
    
    other->constructLattice(this->_lattice.size(), this->_lattice[min_index][this->_lattice[min_index].minIndex()].first, option);
    T price_high = other->price();
    
    strategy->setVolatility(original_rate - delta_rate);
    strategy->build();
    other->constructLattice(this->_lattice.size(), this->_lattice[min_index][this->_lattice[min_index].minIndex()].first, option);
    T price_low = other->price();

    strategy->setInterest(original_rate);
    strategy->build();
    delete other;
    return (price_high - price_low) / (2 * delta_rate);
}



#endif
