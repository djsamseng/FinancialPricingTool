#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include <cmath>

#include "../../DataStructures/PropertySet.h"
#include "../../Math/NormalDistribution.h"
#include "Option.h"

template <class T>
class EuropeanOption : public Option<T> {
        public:
        EuropeanOption() : Option<T>() {}
        virtual ~EuropeanOption() {}

    
        T payoff(const T&) const;

        T price() const;
        T delta() const;
    private:
        T putPrice() const;
        T putDelta() const;
        T callPrice() const;
        T callDelta() const;
};


template <class T>
T EuropeanOption<T>::payoff(const T& price) const {
    if (this->isCall()) {
        if (price > this->strike()) {
            return price - this->strike();
        } else {
            return 0;
        }
    } else {
        if (price < this->strike()) {
            return this->strike() - price;
        } else {
            return 0;
        }
    }
}

template <class T>
T EuropeanOption<T>::price() const {
    if (this->isCall()) {
        return callPrice();
    } else {
        return putPrice();
    }
}

template <class T>
T EuropeanOption<T>::delta() const {
    if (this->isCall()) {
        return callDelta();
    } else {
        return putDelta();
    }
}

template <class T>
T EuropeanOption<T>::putPrice() const {
    double tmp =  this->volatility() * sqrt(this->expiry());
    double d1 = (log(this->currentPrice() / this->strike()) + this->costOfCarry() + this->volatility() * this->volatility() * 0.5 * this->expiry()) / tmp;
    double d2 = d1 - tmp;
    return (this->strike() * exp(-this->interestRate() * this->expiry()) * NormalDistribution::cdf(-d2)) - this->currentPrice() * exp((this->costOfCarry() - this->interestRate()) * this->expiry()) * NormalDistribution::cdf(-d1);
}

template <class T>
T EuropeanOption<T>::callPrice() const {
    double tmp = this->volatility() * sqrt(this->expiry());
    double d1 = (log(this->currentPrice() / this->strike()) + this->costOfCarry() + this->volatility() * this->volatility() * 0.5 * this->expiry()) / tmp;
    double d2 = d1 - tmp;
    return (this->currentPrice() * exp((this->costOfCarry() - this->interestRate()) * this->expiry()) * NormalDistribution::cdf(d1)) - this->strike() * exp((this->costOfCarry() - this->interestRate()) * this->expiry()) * NormalDistribution::cdf(d2);
}

template <class T>
T EuropeanOption<T>::putDelta() const {
    double tmp = this->volatility() * sqrt(this->expiry());
    double d1 = (log(this->currentPrice() / this->strike()) + (this->costOfCarry() + this->volatility() * this->volatility() * 0.5) * this->expiry()) / tmp;
    return exp((this->costOfCarry() - this->interestRate()) * this->expiry()) * (NormalDistribution::cdf(d1) - 1.0);
}

template <class T>
T EuropeanOption<T>::callDelta() const {
    double tmp = this->volatility() * sqrt(this->expiry());
    double d1 = (log(this->currentPrice() / this->strike()) + (this->costOfCarry() + this->volatility() * this->volatility() * 0.5) * this->expiry()) / tmp;
    return exp((this->costOfCarry() - this->interestRate()) * this->expiry()) * NormalDistribution::cdf(d1);

}


#endif
