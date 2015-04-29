#include <Eigen/Dense>
#include <iostream>
#include <assert.h>

#include "LogisticRegression.h"

using namespace std;
using namespace Eigen;

void logisticRegressionTests() {
    MatrixXd m(3,2);
    m << 1, 4,
        5, -2,
        5, 2;
    VectorXd v(3);
    v << 0, 1, 2;
    LogisticRegression<double> lr;
    lr.train(m, v);
    VectorXd input(2);
    input << 5, -2;
    cout << "Probabilities: " << endl << lr.hypothesis(input) << endl;
}

int main() {
    logisticRegressionTests();
    return 0;
}
