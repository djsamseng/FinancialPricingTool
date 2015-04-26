#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

template <class T>
class LinearRegression {
    public:
        LinearRegression() : _max_iter(10000), _error(1), _alpha(0.1) {}
        void train(const vector<vector<T> >& training, const vector<T>& correct);
        T hypothesis(const vector<T>& input);
    private:
        void normalize(const vector<vector<T> >& training, vector<vector<T> >& train);

        vector<T> _coeff;
        double _alpha;
        int _max_iter;
        T _error;
};

template <class T>
void LinearRegression<T>::train(const vector<vector<T> >& training, const vector<T>& correct) {
    
    assert(training.size() > 0);

    _coeff = vector<T>(training[0].size() + 1, 1);
    vector<vector<T> > train;
    normalize(training, train);
    assert(train[0][0] == 1);
    
    for (int i = 0; i < train.size(); i++) {
        for (int j = 0; j < train[i].size(); j++) {
            cout << train[i][j] << " ";
        }
        cout << endl;
    }


    _coeff = vector<T>(train[0].size(), 0);
    vector<T> temp_coeff(train[0].size(), 0);

    for (int counter = 0; counter < 10; counter++) {
        //_coeff[i] = _coeff[i] - _alpha ( d/dcoeffi ( J(coeff) ) )
        for (int i = 0; i < temp_coeff.size(); i++) {//foreach coefficients
            int error = 0;
            for (int j = 0; j < train.size(); j++) {//foreach training example
                int sum = 0;
                for (int k = 0; k < train[j].size(); k++) {//foreach feature
                    sum += train[j][k] * _coeff[k];
                }
                error += (sum - correct[j]) * train[j][i];
            }
            temp_coeff[i] = _coeff[i] - _alpha * error;
        }
        for (int i = 0; i < temp_coeff.size(); i++) {
            _coeff[i] = temp_coeff[i];
        }
    }
}

template <class T>
void LinearRegression<T>::normalize(const vector<vector<T> >& training, vector<vector<T> >& train) {
    vector<T> max_values(training[0].size() + 1, 1); //Handle all negative values
    vector<T> min_values(training[0].size() + 1, 1); //Handle all values > 1
    vector<T> avg(training[0].size() + 1, 0);
    for (int i = 0; i < training.size(); i++) {
        for (int j = 0; j < training[i].size(); j++) {
            if (training[i][j] > max_values[j+1]) {
                max_values[j+1] = training[i][j];
            }
            if (training[i][j] < min_values[j+1]) {
                min_values[j+1] = training[i][j];
            }
            avg[j+1] += training[i][j];
        }
    }
    
    for (int i = 0; i < avg.size(); i++) {
        avg[i] = avg[i] / training.size();
    }
    for (int i = 0; i < training.size(); i++) {
        vector<T> temp(training[i].size() + 1, 1);
        for (int j = 0; j < training[i].size(); j++) {
            int range = max_values[j+1] - min_values[j+1];
            range = range <= 1 ? 1 : range;
            temp[j+1] = (training[i][j] - avg[j+1]) / range;
        }
        train.push_back(temp);
    }
}
template <class T>
T LinearRegression<T>::hypothesis(const vector<T>& input) {
    assert(input.size() + 1 == _coeff.size());
    T result = _coeff[0];
    for (int i = 0; i < input.size(); i++) {
        result += _coeff[i + 1] * input[i];
    }
    return result;
}

#endif
