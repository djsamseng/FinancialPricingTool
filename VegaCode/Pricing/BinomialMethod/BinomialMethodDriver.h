#ifndef BINOMIAL_METHOD_DRIVER_H
#define BINOMIAL_METHOD_DRIVER_H


#include "BinomialMethodFactory.h"
#include "BinomialMethodStrategies/BinomialStrategy.h"
#include "BinomialMethodStrategies\BinomialStrategyFactory.h"
#include "../../Models/FinancialModels/Option.h"
#include "../../Models/FinancialModels/OptionFactory.h"

template <class T>
class BinomialMethodDriver {
    public:
        BinomialMethodDriver() {}
        void calculateOption(Option<T>* option, BinomialStrategyType binomialStrategy, int numberSteps);
        const T& price() const { return _price; }
        const T& delta() const { return _deltaR; }
        const T& vega() const { return _vega; }
        const T& rho() const { return _rho; }
    private:
        T _price, _deltaR, _vega, _rho;
};

template <class T>
void BinomialMethodDriver<T>::calculateOption(Option<T>* option, BinomialStrategyType binomialStrategy, int numberSteps) {
	double delta = option->expiry() / double(numberSteps);
	double discount_rate = exp(-1 * option->interestRate() * delta);

	BinomialStrategy<T> *strategy = BinomialStrategyFactory::getBinomialStrategy<T>(binomialStrategy, option->interestRate(), option->volatility(), delta);
	BinomialMethod<T> *solver = BinomialMethodFactory::getBinomialMethod<T>(option->optionType(), discount_rate, strategy);

	solver->constructLattice(numberSteps, option->currentPrice(), option);
	_price = solver->price();
	_deltaR = solver->delta();
	_vega = solver->vega(option->interestRate(), strategy, option);
    _rho = solver->rho(option->interestRate(), strategy, option);

	delete strategy;
	delete solver;
}

#endif
