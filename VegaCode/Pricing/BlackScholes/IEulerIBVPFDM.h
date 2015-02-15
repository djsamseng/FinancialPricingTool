#ifndef I_EULER_IBVP_FDM_H
#define I_EULER_IBVP_FDM_H

#include "IBVPFDM.h"
#include "../../Math/LUTridiagonalSolver.h"

template <class T>
class IEulerIBVPFDM : public IBVPFDM<T>{
    public:
        IEulerIBVPFDM(IBVP<T>* ibvp, int tSteps, int xSteps) : IBVPFDM<T>(ibvp, tSteps, xSteps) {}
    private:
        void calculateBoundaryConditions(NumericMatrix<int, T>& mat, int t);
        void calculateSolution(NumericMatrix<int, T>& mat, const NumericArray<int, T>& xArr, int t);

};

template <class T>
void IEulerIBVPFDM<T>::calculateBoundaryConditions(NumericMatrix<int, T>& mat, int t) {
    assert(t + 1 <= mat.maxRowIndex());
    mat(t + 1, mat.minColIndex()) = this->_ibvp->leftBC(t + 1);
    mat(t + 1, mat.maxColIndex()) = this->_ibvp->rightBC(t + 1);
}
template <class T>
void IEulerIBVPFDM<T>::calculateSolution(NumericMatrix<int, T>& mat, const NumericArray<int, T>& xArr, int t) {
    double k = this->_t_size;
    double h = this->_x_size;
    
    NumericArray<int, T> A(this->_x_steps - 1);
    NumericArray<int, T> B(this->_x_steps - 1);
    NumericArray<int, T> C(this->_x_steps - 1);
    NumericArray<int, T> RHS(this->_x_steps - 1);
    
    assert(mat.minColIndex() == 0);
    assert(RHS.maxIndex() == mat.maxColIndex() - 2);
    
    for (int i = RHS.minIndex(); i <= RHS.maxIndex(); i++) {
        T sigma = this->_ibvp->diffusion(xArr[i+1], t + 1);
        T mew = this->_ibvp->convection(xArr[i+1], t + 1);
        double zero_term = (this->_ibvp->zeroTerm(xArr[i+1], t + 1));
        
        A[i] = k * sigma - 0.5 * k * h * mew;
        B[i] = -1 * h * h - 2 * k * sigma + k * h * h * zero_term;
        C[i] = k * sigma + 0.5 * k * h * mew;

        RHS[i] = h * h * (k * this->_ibvp->rightHandSide(xArr[i + 1], t + 1) - mat(t, i + 1));
    }
    
    RHS[0] = h * h * (k * this->_ibvp->rightHandSide(xArr[1], t + 1) - mat(t, 1)) - A[0] * mat(t + 1, 0);
    
    assert(RHS.maxIndex() == this->_x_steps - 2);
    assert(mat.maxColIndex() == this->_x_steps);
   
    RHS[RHS.maxIndex()] = h * h * (k * this->_ibvp->rightHandSide(xArr[xArr.maxIndex() - 1], t + 1) - mat(t, mat.maxColIndex() - 1)) - C[C.maxIndex()] * mat(t + 1, mat.maxColIndex());

    NumericArray<int, T> U = LUTridiagonalSolver<int, T>::solve(A, B, C, RHS);
    assert(mat.minColIndex() == U.minIndex());
    
    for (int i = mat.minColIndex() + 1; i <= mat.maxColIndex() - 1; i++) {
        mat(t + 1, i) = U[i - 1];
    }
}

#endif
