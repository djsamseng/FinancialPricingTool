#ifndef IBVP_FDM_H
#define IBVP_FDM_H

#include "IBVP.h"
#include "../../DataStructures/Mesher.h"
#include "../../DataStructures/NumericMatrix.h"

template <class T>
class IBVPFDM {
    public:
        IBVPFDM(IBVP<T>* ibvp, int tSteps, int xSteps) : _ibvp(ibvp), _t_steps(tSteps), _x_steps(xSteps) {}
        NumericMatrix<int, T> result();
        virtual void calculateBoundaryConditions(NumericMatrix<int, T>& mat, int t) = 0;
        virtual void calculateSolution(NumericMatrix<int, T>& mat, NumericArray<int, T>& xArr, int t) = 0;
    protected:
        IBVP<T>* _ibvp;
        int _t_steps;
        int _x_steps;

        Mesher<T> _mesher;
        
        virtual void initInitialConditions(NumericMatrix<int, T>& mat, NumericArray<int, T>& xArr) = 0;
};

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

#endif
