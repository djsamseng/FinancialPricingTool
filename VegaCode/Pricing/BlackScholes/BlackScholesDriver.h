#ifndef BLACK_SCHOLES_DRIVER_H
#define BLACK_SCHOLES_DRIVER_H

template <class T>
class BlackScholesDriver {
    public:
        BlackScholesDriver() {}
        void calculateOption(OptionType optionType, int numTSteps, int numXSteps, double ir, double vol, const T& strike, const T& curPrice, const T& carry, bool isCall);
};

#endif
