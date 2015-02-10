#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

namespace NormalDistribution {
    
template <class T>
static T cdf(const T& x) {
    double n1 = 0.4361836;
    double n2 = -0.1201676;
    double n3 = 0.9372980;
    
    double k = 1.0 / (1.0 + 0.33267 * x);
    double A = 1.0 / sqrt(2.0 * 3.1415);
    
    if (x >= 0.0) {
        return 1.0 -  A * exp(-x * x * 0.5) * (n1 * k + n2 * k * k + n3 * k * k * k);
    } else {
        return 1.0 - cdf(-x);
    }
}
}

#endif
