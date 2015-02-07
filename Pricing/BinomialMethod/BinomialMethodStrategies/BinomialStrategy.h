#ifndef BINOMIAL_STRATEGY_H
#define BINOMIAL_STRATEGY_H

enum BinomialType {
    MultBinomialType = 0,
    ArithBinomialType = 1
};

template <class T>
class BinomialStrategy {
    public:
        BinomialStrategy() : _binomial_type(MultBinomialType) {}
        BinomialStrategy(BinomialType binomial_type) : _binomial_type(binomial_type) {}
        BinomialStrategy(BinomialType binomial_type, double interest, double volatility, double delta) : _binomial_type(binomial_type), _interest(interest), _volatility(volatility), _delta(delta) {}
        const T& upValue() const { return _up; }
        const T& downValue() const { return _down; }
        double probValue() const { return _probValue; }
        double volatility() const { return _volatility; }
        double interest() const { return _interest; }
        double delta() const { return _delta; }
        BinomialType binomialType() { return _binomial_type; }

        void setUpValue(const T& up) { _up = up; }
        void setDownValue(const T& down) { _down = down; }
        void setProbValue(double probValue) { _probValue = probValue; }
        void setVolatility(double volatility) { _volatility = volatility; }
        void setInterest(double interest) { _interest = interest; }
        void setDelta(double delta) { _delta = delta; }
        void setBinomialType(BinomialType binomial_type) { _binomial_type = binomial_type; }

    protected:
        T _up;
        T _down;
        double _probValue;
        double _volatility;
        double _interest;
        double _delta;

        BinomialType _binomial_type;
};
#endif
