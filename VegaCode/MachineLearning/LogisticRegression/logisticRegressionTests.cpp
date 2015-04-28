#include <Eigen/Dense>
#include <iostream>
#include <assert.h>

#include "LogisticRegression.h"

using namespace std;
using namespace Eigen;

void logisticRegressionTests() {
    MatrixXd m(2,2);
    m << 1, 4,
        5, -2;
    VectorXd v(2);
    v << 0, 1;
    LogisticRegression<double> lr;
    lr.train(m, v);
    VectorXd input(2);
    input << 1, 4;
    cout << "Probability of classification as 1 = " << lr.hypothesis(input) << endl;
}

int main() {
    logisticRegressionTests();
    return 0;
}
