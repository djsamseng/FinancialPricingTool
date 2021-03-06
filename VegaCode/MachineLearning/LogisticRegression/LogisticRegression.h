#ifndef LOGISTIC_REGRESSION_H_
#define LOGISTIC_REGRESSION_H_

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

template <class T>
class LogisticRegression {
    public:
        LogisticRegression() : _alpha(0.1), _lambda(0), _max_iterations(500) {}
        void train(const MatrixXd& train, const VectorXd& correct);
        VectorXd hypothesis(const VectorXd& input);
    private:
        void normalize(MatrixXd& training);
        double sigmoid(double expTerm);
        void train(MatrixXd& training, const VectorXd& correct, int class_number);
        MatrixXd _coeff;
        VectorXd _avgs;
        VectorXd _range;
        double _alpha;
        double _lambda;
        int _max_iterations;
};

template <class T>
void LogisticRegression<T>::train(const MatrixXd& train, const VectorXd& correct) {
    MatrixXd training(train.rows(), train.cols() + 1);
    training << MatrixXd::Constant(train.rows(), 1, 1), train;
    normalize(training);
    int classes = correct.maxCoeff();
    assert(classes >= 1);
    _coeff = MatrixXd(classes + 1, training.cols());
    for (int i = 0; i < classes + 1; i++) {
        this->train(training, correct, i);
    }
}

template <class T>
void LogisticRegression<T>::train(MatrixXd& training, const VectorXd& correct, int class_number) {
    VectorXd *coeff = new VectorXd(VectorXd::Constant(training.cols(), 1));
    VectorXd *tmp = new VectorXd(training.cols());
    double total_error = 0;
    for (int count = 0; count < _max_iterations; count++) {
        //coefficient 0
        total_error = 0;
        double error0 = 0;
        for (int j = 0; j < training.rows(); j++) {
            int y = correct(j) == class_number ? 1 : 0;
            error0 += sigmoid(coeff->dot(training.row(j))) - y;
        }
        total_error += error0;
        (*tmp)(0) = (*coeff)(0) - _alpha * error0 / training.rows();
        //foreach coeff
        for (int i = 1; i < training.cols(); i++) {
            double error = 0;
            for (int j = 0; j < training.rows(); j++) {
                int y = correct(j) == class_number ? 1 : 0;
                error += (sigmoid(coeff->dot(training.row(j))) - y) * training(j, i);
            }
            (*tmp)(i) = (*coeff)(i) - _alpha * error / training.rows();
            total_error += error;
        }
        VectorXd *tmp2 = tmp;
        tmp = coeff;
        coeff = tmp2;
    }
    _coeff.row(class_number) = std::move(*coeff);
    delete coeff;
    delete tmp;
    cout << "In Sample Error: " << total_error << endl;
}

template <class T>
void LogisticRegression<T>::normalize(MatrixXd& training) {
    _avgs = training.colwise().sum();
    _avgs /= training.rows();
    VectorXd maxes = training.colwise().maxCoeff();
    VectorXd mins = training.colwise().minCoeff();
    _range = maxes - mins;
    for (int i = 0; i < _range.size(); i++) {
        if (_range(i) < 1) {
            _range(i) = 1;
        }
    }

    for (int i = 0; i < training.rows(); i++) {
        training.row(i) = (training.row(i) - _avgs.transpose()).array() / _range.transpose().array();
    }
    training.col(0) = MatrixXd::Constant(training.rows(), 1, 1);
}

template <class T>
VectorXd LogisticRegression<T>::hypothesis(const VectorXd& in) {
    VectorXd result(_coeff.rows());
    for (int i = 0; i < _coeff.rows(); i++) {
        VectorXd input(in.rows()+1, in.cols());
        input << MatrixXd::Constant(1,1,1), in;
        input = (input - _avgs).array() / _range.array();
        input(0) = 1;
        double expTerm = _coeff.row(i).dot(input.col(0).transpose());
        result(i) = T(sigmoid(expTerm));
    }
    return result;
}

template <class T>
double LogisticRegression<T>::sigmoid(double expTerm) {
    return 1 / (1 + exp(-expTerm));
}



#endif
