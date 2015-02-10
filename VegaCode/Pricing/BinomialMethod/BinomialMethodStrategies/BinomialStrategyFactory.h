#ifndef BINOMIAL_STRATEGY_FACTORY_H
#define BINOMIAL_STRATEGY_FACTORY_H

#include <assert.h>

#include "../../../Utility/BinomialStrategyType.h"
#include "CRRBinomialStrategy.h"
#include "EQPBinomialStrategy.h"
#include "JRBinomialStrategy.h"
#include "ModifiedCRRBinomialStrategy.h"
#include "TRGBinomialStrategy.h"

namespace BinomialStrategyFactory {
	template <class T>
	BinomialStrategy<T>* getBinomialStrategy(BinomialStrategyType strategyType, double interestRate, double volatility, double delta) {
		if (strategyType == CRRBinomialStrategyType) {
			return new CRRBinomialStrategy<T>(interestRate, volatility, delta);
		}
		else if (strategyType == EQPBinomialStrategyType) {
			return new EQPBinomialStrategy<T>(interestRate, volatility, delta);
		}
		else if (strategyType == JRBinomialStrategyType) {
			return new JRBinomialStrategy<T>(interestRate, volatility, delta);
		}
		else if (strategyType == ModifiedCRRBinomialStrategyType) {
			assert(false);
			return NULL;
		}
		else if (strategyType == TRGBinomialStrategyType) {
			return new TRGBinomialStrategy<T>(interestRate, volatility, delta);
		}
		else {
			assert(false);
			return NULL;
		}
	}
}

#endif