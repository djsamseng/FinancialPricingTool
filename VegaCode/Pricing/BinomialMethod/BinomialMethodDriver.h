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
	T price, deltaR, vega;
};

template <class T>
void BinomialMethodDriver<T>::calculateOption(Option<T>* option, BinomialStrategyType binomialStrategy, int numberSteps) {
	double delta = option->expiry() / double(numberSteps);
	double discount_rate = exp(-1 * option->interestRate() * delta);

	BinomialStrategy<T> *strategy = BinomialStrategyFactory::getBinomialStrategy<T>(binomialStrategy, option->interestRate(), option->volatility(), delta);
	BinomialMethod<T> *solver = BinomialMethodFactory::getBinomialMethod<T>(option->optionType(), discount_rate, strategy);

	solver->constructLattice(numberSteps, option->currentPrice(), option);
	price = solver->price();
	deltaR = solver->delta();
	vega = solver->vega(option->interestRate(), strategy, option);

	delete strategy;
	delete solver;
}

#endif
