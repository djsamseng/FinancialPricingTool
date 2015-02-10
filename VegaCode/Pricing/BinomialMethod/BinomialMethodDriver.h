#ifndef BINOMIAL_METHOD_DRIVER_H
#define BINOMIAL_METHOD_DRIVER_H


#include "BinomialMethod.h"
#include "BinomialMethodFactory.h"
#include "BinomialMethodStrategies/BinomialStrategy.h"
#include "BinomialMethodStrategies\BinomialStrategyFactory.h"
#include "../../Models/FinancialModels/Option.h"
#include "../../Models/FinancialModels/OptionFactory.h"

template <class T>
class BinomialMethodDriver {
public:
	BinomialMethodDriver() {}
	void calculateOption(OptionType optionType, BinomialStrategyType binomialStrategy, int numberSteps, double interestRate, double volatility, const T& strike, double expiry, const T& currentPrice, const T& costOfCarry, bool isCall, T& price, T& deltaR, T& vega);
};

template <class T>
void BinomialMethodDriver<T>::calculateOption(OptionType optionType, BinomialStrategyType binomialStrategy, int numberSteps, double interestRate, double volatility, const T& strike, double expiry, const T& currentPrice, const T& costOfCarry, bool isCall, T& price, T& deltaR, T& vega) {
	Option<T> *option = OptionFactory::getOption<T>(optionType);
	option->setInterestRate(interestRate);
	option->setVolatility(volatility);
	option->setStrike(strike);
	option->setExpiry(expiry);
	option->setCurrentPrice(currentPrice);
	option->setCostOfCarry(costOfCarry);
	option->setIsCall(isCall);

	double delta = option->expiry() / double(numberSteps);
	double discount_rate = exp(-1 * option->interestRate() * delta);

	BinomialStrategy<T> *strategy = BinomialStrategyFactory::getBinomialStrategy<T>(binomialStrategy, interestRate, volatility, delta);
	BinomialMethod<T> *solver = BinomialMethodFactory::getBinomialMethod<T>(optionType, discount_rate, strategy);

	solver->constructLattice(numberSteps, currentPrice, option);
	price = solver->price();
	deltaR = solver->delta();
	vega = solver->vega(interestRate, strategy, option);

	delete option;
	delete strategy;
	delete solver;
}

#endif