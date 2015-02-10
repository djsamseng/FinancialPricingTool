#ifndef BINOMIAL_METHOD_EUROPEAN_H
#define BINOMIAL_METHOD_EUROPEAN_H

#include "BinomialMethod.h"

template <class T>
class BinomialMethodEuropean : public BinomialMethod<T> {
    public:
        BinomialMethodEuropean(double rate, BinomialStrategy<T> *strategy) : BinomialMethod<T>(rate, strategy) {}
        void constructLattice(int size, const T& initial_price, Option<T>* option);
        T price() const;
        T delta() const;
        T vega(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const;
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
T BinomialMethodEuropean<T>::delta() const {
    int time_index = this->_lattice.minIndex() + 1;
    assert(time_index <= this->_lattice.maxIndex());

    int down_index = this->_lattice[time_index].minIndex();
    assert(down_index + 1 <= this->_lattice[time_index].maxIndex());
    assert(time_index == 1 && down_index == 0);
    return (this->_lattice[time_index][down_index + 1].second - this->_lattice[time_index][down_index].second) / (this->_lattice[time_index][down_index + 1].first - this->_lattice[time_index][down_index].first);
}

template <class T>
T BinomialMethodEuropean<T>::vega(double rate, BinomialStrategy<T> *strategy, Option<T> *option) const {
    double delta_volatility = 0.1;
    double original_volatility = strategy->volatility();

    strategy->setVolatility(original_volatility + delta_volatility);
    strategy->build();
    
    BinomialMethodEuropean<T> other = BinomialMethodEuropean<T>(rate, strategy);
    int min_index = this->_lattice.minIndex();
    
    other.constructLattice(this->_lattice.size(), this->_lattice[min_index][this->_lattice[min_index].minIndex()].first, option);
    T price_high = other.price();
    
    strategy->setVolatility(original_volatility - delta_volatility);
    strategy->build();
    other.constructLattice(this->_lattice.size(), this->_lattice[min_index][this->_lattice[min_index].minIndex()].first, option);
    T price_low = other.price();

    strategy->setVolatility(original_volatility);
    strategy->build();
    return (price_high - price_low) / delta_volatility;
}
#endif
