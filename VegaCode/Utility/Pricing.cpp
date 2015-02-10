#include <cmath>

namespace Pricing {
    
    template <class T>
    T futureValue(const T& pv, int t, double r) {
        return pv * exp(r * t);
    }

    template <class T>
    T presentValue(const T& fv, int t, double r) {
        return fv * exp(-r * t);
    }
}
