#ifndef E_EULER_IBVP_FDM_H
#define E_EULER_IBVP_FDM_H

#include "IBVPFDM.h"

template <class T>
class EEulerIBVPFDM : public IBVPFDM<T> {
    public:
        EEulerIBVPFDM(IBVP<T>* ibvp, int tSteps, int xSteps) : IBVPFDM<T>(ibvp, tSteps, xSteps) {}
        void calculateBoundaryConditions(NumericMatrix<int, T>& mat, int t);
        void calculateSolution(NumericMatrix<int, T>& mat, NumericArray<int, T>& xArr, int t);
    private:
        void initInitialConditions(NumericMatrix<int, T>& mat, NumericArray<int, T>& xArr);
};

template <class T>
void EEulerIBVPFDM<T>::initInitialConditions(NumericMatrix<int, T>& mat, NumericArray<int, T>& xArr) {
    mat(mat.minRowIndex(), mat.minColIndex()) = this->_ibvp->leftBC(0.0);
    mat(mat.minRowIndex(), mat.maxColIndex()) = this->_ibvp->rightBC(0.0);
    for (int i = mat.minColIndex(); i <= mat.maxColIndex(); i++) {
        mat(mat.minColIndex(), i) = this->_ibvp->initialC(xArr[i]);
    }
}

template <class T>
void EEulerIBVPFDM<T>::calculateBoundaryConditions(NumericMatrix<int, T>& mat, int t) {
    mat(t, mat.minColIndex()) = this->_ibvp->leftBC(t);
    mat(t, mat.maxColIndex()) = this->_ibvp->rightBC(t);
}

template <class T>
void EEulerIBVPFDM<T>::calculateSolution(NumericMatrix<int, T>& mat, NumericArray<int, T>& xArr, int t) {
    double k = (this->_ibvp->maxT() - this->_ibvp->minT()) / double(this->_t_steps);
    double h = (this->_ibvp->maxX() - this->_ibvp->minX()) / double(this->_x_steps);
    for (int i = mat.minColIndex() + 1; i <= mat.maxColIndex() - 1; i++) {
        T sigma = this->_ibvp->diffusion(xArr[i], t);
        T mew = this->_ibvp->convection(xArr[i], t);
        T zero_term = this->_ibvp->zeroTerm(xArr[i], t);
        
        T alpha = k * sigma - 0.5 * k * h * mew;
        T beta = h * h - 2 * k * sigma + k * h * h * zero_term;
        T gamma = k * sigma + 0.5 * k * h * mew;

        mat(t+1, i) = alpha * mat(t, i-1) + beta * mat(t, i) + gamma * mat(t, i+1) / (h * h) - k * this->_ibvp->rightHandSide(xArr[i], t);
    }
}
#endif
