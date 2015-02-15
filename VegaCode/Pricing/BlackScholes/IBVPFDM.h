#ifndef IBVP_FDM_H
#define IBVP_FDM_H

#include "IBVP.h"
#include "../../DataStructures/Mesher.h"
#include "../../DataStructures/NumericMatrix.h"

template <class T>
class IBVPFDM {
    public:
        IBVPFDM(IBVP<T>* ibvp, int tSteps, int xSteps) : _ibvp(ibvp), _t_steps(tSteps), _x_steps(xSteps) { init(); }
        NumericMatrix<int, T> result();
        virtual void calculateBoundaryConditions(NumericMatrix<int, T>& mat, int t) = 0;
        virtual void calculateSolution(NumericMatrix<int, T>& mat, const NumericArray<int, T>& xArr, int t) = 0;
    protected:
        IBVP<T>* _ibvp;
        int _t_steps;
        int _x_steps;
        double _t_size;
        double _x_size;
        Mesher<T> _mesher;
        
        void initInitialConditions(NumericMatrix<int, T>& mat, const NumericArray<int, T>& xArr);
    private:
        void init();
};

template <class T>
void IBVPFDM<T>::initInitialConditions(NumericMatrix<int, T>& mat, const NumericArray<int, T>& xArr) {
    mat(mat.minRowIndex(), mat.minColIndex()) = this->_ibvp->leftBC(0.0);
    mat(mat.minRowIndex(), mat.maxColIndex()) = this->_ibvp->rightBC(0.0);
    for (int i = mat.minColIndex(); i <= mat.maxColIndex() - 1; i++) {
        mat(mat.minRowIndex(), i) = this->_ibvp->initialC(xArr[i]);
    }
}

template <class T>
NumericMatrix<int, T> IBVPFDM<T>::result() {
    _mesher = Mesher<T>(_ibvp->minX(), _ibvp->maxX(), _ibvp->minT(), _ibvp->maxT());
    NumericArray<int, T> xArr = _mesher.xArr(_x_steps);
    NumericMatrix<int, T> result(_t_steps + 1, _x_steps + 1);
    initInitialConditions(result, xArr);
    for (int t = _ibvp->minT(); t < _ibvp->maxT(); t++) {
        calculateBoundaryConditions(result, t);
        calculateSolution(result, xArr, t);
    }
    return result;
}

template <class T>
void IBVPFDM<T>::init() {
    _t_size = (this->_ibvp->maxT() - this->_ibvp->minT()) / double(this->_t_steps);
    _x_size = (this->_ibvp->maxX() - this->_ibvp->minX()) / double(this->_x_steps);
}
#endif
