#ifndef OPTION_FACTORY_H
#define OPTION_FACTORY_H

#include <assert.h>

#include "../../Utility/OptionType.h"
#include "Option.h"
#include "AmericanOption.h"
#include "EuropeanOption.h"

namespace OptionFactory {
	template <class T>
	Option<T>* getOption(OptionType optionType) {
		if (optionType == AmericanOptionType) {
			return new AmericanOption<T>();
		} else if (optionType == EuropeanOptionType) {
			return new EuropeanOption<T>();
		} else {
			assert(false);
			return NULL;
		}
	}
}

#endif