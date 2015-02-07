#ifndef OPTION_H
#define OPTION_H

#include "../../DataStructures/PropertySet.h"
#include "Derivative.h"

template <class T>
class Option : public Derivative<T> {
    public:
        Option() : Derivative<T>() {}
        virtual ~Option() {}

        virtual T price() const = 0;
        virtual T payoff(const T& price) const = 0;
    private:
        PropertySet<std::string, T> _properties;
};

#endif
