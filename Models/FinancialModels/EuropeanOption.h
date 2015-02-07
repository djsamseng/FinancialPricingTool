#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include <cmath>

#include "../../DataStructures/PropertySet.h"
#include "../../Math/NormalDistribution.h"
#include "Option.h"

template <class T>
class EuropeanOption : public Option<T> {
        public:
        EuropeanOption() : Option<T>() { initializeProperties(); }
        virtual ~EuropeanOption() {}

        const T& interestRate() const { return _properties[INTEREST_RATE]; }
        const T& volatility() const { return _properties[VOLATILITY]; }
        const T& strike() const { return _properties[STRIKE]; }
        const T& expiry() const { return _properties[EXPIRY]; }
        const T& currentPrice() const { return _properties[CURRENT_PRICE]; }//current underlying price
        const T& costOfCarry() const { return _properties[COST_OF_CARRY]; }
        bool isCall() const { return _properties[CALL] == 1 ? true : false; }

        void setInterestRate(const T& val) { _properties[INTEREST_RATE] = val; }
        void setVolatility(const T& val) { _properties[VOLATILITY] = val; }
        void setStrike(const T& val) { _properties[STRIKE] = val; }
        void setExpiry(const T& val) { _properties[EXPIRY] = val; }
        void setCurrentPrice(const T& val) { _properties[CURRENT_PRICE] = val; }
        void setCostOfCarry(const T& val) { _properties[COST_OF_CARRY] = val; }
        void setIsCall(bool isCall) { _properties[CALL] = isCall ? 1 : 0; }
    
        T payoff(const T&) const;

        T price() const;
        T delta() const;
    private:
        PropertySet<int, T> _properties;//interest rate, voltatility, strike price, expiry date, current underlying price, cost of carry
        void initializeProperties();
        T putPrice() const;
        T putDelta() const;
        T callPrice() const;
        T callDelta() const;
        
        enum PROPERTY_KEYS { 
            INTEREST_RATE = 0,
            VOLATILITY = 1,
            STRIKE = 2,
            EXPIRY = 3,
            CURRENT_PRICE = 4,
            COST_OF_CARRY = 5,
            CALL = 6
        };

};

template <class T>
void EuropeanOption<T>::initializeProperties() {
    _properties.add(INTEREST_RATE, T() + 0.08);
    _properties.add(VOLATILITY, T() + 0.30);
    _properties.add(STRIKE, T() + 65.0);
    _properties.add(EXPIRY, T() + 0.25);
    _properties.add(CURRENT_PRICE, T() + 60.0);
    _properties.add(COST_OF_CARRY, T() + 0.08);
    _properties.add(CALL, T());
}

template <class T>
T EuropeanOption<T>::payoff(const T& price) const {
    if (isCall()) {
        if (price > strike()) {
            return price - strike();
        } else {
            return 0;
        }
    } else {
        if (price < strike()) {
            return strike() - price;
        } else {
            return 0;
        }
    }
}

template <class T>
T EuropeanOption<T>::price() const {
    if (isCall()) {
        return callPrice();
    } else {
        return putPrice();
    }
}

template <class T>
T EuropeanOption<T>::delta() const {
    if (isCall()) {
        return callDelta();
    } else {
        return putDelta();
    }
}

template <class T>
T EuropeanOption<T>::putPrice() const {
    double tmp =  volatility() * sqrt(expiry());
    double d1 = (log(currentPrice() / strike()) + costOfCarry() + volatility() * volatility() * 0.5 * expiry()) / tmp;
    double d2 = d1 - tmp;
    return (strike() * exp(-interestRate() * expiry()) * NormalDistribution::cdf(-d2)) - currentPrice() * exp((costOfCarry() - interestRate()) * expiry()) * NormalDistribution::cdf(-d1);
}

template <class T>
T EuropeanOption<T>::callPrice() const {
    double tmp = volatility() * sqrt(expiry());
    double d1 = (log(currentPrice() / strike()) + costOfCarry() + volatility() * volatility() * 0.5 * expiry()) / tmp;
    double d2 = d1 - tmp;
    return (currentPrice() * exp((costOfCarry() - interestRate()) * expiry()) * NormalDistribution::cdf(d1)) - strike() * exp((costOfCarry() - interestRate()) * expiry()) * NormalDistribution::cdf(d2);
}

template <class T>
T EuropeanOption<T>::putDelta() const {
    double tmp = volatility() * sqrt(expiry());
    double d1 = (log(currentPrice() / strike()) + (costOfCarry() + volatility() * volatility() * 0.5) * expiry()) / tmp;
    return exp((costOfCarry() - interestRate()) * expiry()) * (NormalDistribution::cdf(d1) - 1.0);
}

template <class T>
T EuropeanOption<T>::callDelta() const {
    double tmp = volatility() * sqrt(expiry());
    double d1 = (log(currentPrice() / strike()) + (costOfCarry() + volatility() * volatility() * 0.5) * expiry()) / tmp;
    return exp((costOfCarry() - interestRate()) * expiry()) * NormalDistribution::cdf(d1);

}


#endif
