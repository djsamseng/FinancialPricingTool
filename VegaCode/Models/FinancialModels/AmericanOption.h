#ifndef AMERICAN_OPTION_H
#define AMERICAN_OPTION_H

#include <cmath>

#include "../../DataStructures/PropertySet.h"
#include "../../Math/NormalDistribution.h"
#include "Option.h"

template <class T>
class AmericanOption : public Option<T> {
    public:
        AmericanOption() : Option<T>(AmericanOptionType) {}
        virtual ~AmericanOption() {}
    
        T payoff(const T&) const;

    private:
};


template <class T>
T AmericanOption<T>::payoff(const T& price) const {
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


#endif
