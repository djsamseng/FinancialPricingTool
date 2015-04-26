#include <iostream>

#include "LinearRegression.h"

using namespace std;

void linearRegressionTest() {
    LinearRegression<double> regress;
    vector<vector<double> > training;
    for (int i = 0; i < 5; i++) {
        vector<double> tmp;
        for (int j = 0; j < 3; j++) {
            tmp.push_back(double(rand() % 5));
        }
        training.push_back(tmp);
    }
    vector<double> correct(training.size(), 5);
    regress.train(training, correct);
    vector<double> h;
    for (int i = 0; i < 3; i++) {
        h.push_back(double(rand() % 5));
    }
    cout << "Hypothesis: " << regress.hypothesis(h) << endl;
}

int main() {
    linearRegressionTest();
    return 0;
}
