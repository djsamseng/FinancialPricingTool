#ifndef BINOMIAL_METHOD_FACTORY_H
#define BINOMIAL_METHOD_FACTORY_H

#include <assert.h>

#include "BinomialMethod.h"
#include "BinomialMethodAmerican.h"
#include "BinomialMethodEuropean.h"
#include "BinomialMethodStrategies\BinomialStrategy.h"
#include "../../Utility/OptionType.h"

namespace BinomialMethodFactory {
	template < class T >
	BinomialMethod<T>* getBinomialMethod(OptionType optionType, double discount, BinomialStrategy<T>* strategy) {
		if (optionType == AmericanOptionType) {
			return new BinomialMethodAmerican<T>(discount, strategy);
		}
		else if (optionType == EuropeanOptionType) {
			return new BinomialMethodEuropean<T>(discount, strategy);
		}
		else {
			assert(false);
			return NULL;
		}
	}
}


#endif