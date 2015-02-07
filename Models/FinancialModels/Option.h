#ifndef OPTION_H
#define OPTION_H

#include <assert.h>

#include "../../DataStructures/PropertySet.h"
#include "Derivative.h"

template <class T>
class Option : public Derivative<T> {
    public:
        Option() : Derivative<T>() { initializeProperties(); }
        virtual ~Option() {}
        
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


        virtual T price() const { assert(false); return T(); }
        virtual T payoff(const T& price) const = 0;
    private:
        PropertySet<int, T> _properties;//interest rate, voltatility, strike price, expiry date, current underlying price, cost of carry
        void initializeProperties();

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
void Option<T>::initializeProperties() {
    _properties.add(INTEREST_RATE, T() + 0.08);
    _properties.add(VOLATILITY, T() + 0.30);
    _properties.add(STRIKE, T() + 65.0);
    _properties.add(EXPIRY, T() + 0.25);
    _properties.add(CURRENT_PRICE, T() + 60.0);
    _properties.add(COST_OF_CARRY, T() + 0.08);
    _properties.add(CALL, T());
}


#endif
