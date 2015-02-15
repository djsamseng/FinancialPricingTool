#ifndef LU_TRIDIAGONAL_SOLVER_H
#define LU_TRIDIAGONAL_SOLVER_H

template <class I, class V>
class LUTridiagonalSolver {
    public:
        static NumericArray<I, V> solve(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C, const NumericArray<I, V>& RHS); 
    private:
        static bool isDiagonallyDominant(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C);
        static void calculateBetaGamma(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C, const NumericArray<I, V>& RHS, NumericArray<I, V>& beta, NumericArray<I, V>& gamma); 
        static void calculateZU(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C, const NumericArray<I, V>& RHS, const NumericArray<I, V>& beta, const NumericArray<I, V>& gamma, NumericArray<I, V>& Z, NumericArray<I, V>& U); 

};

template <class I, class V>
bool LUTridiagonalSolver<I, V>::isDiagonallyDominant(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C) {
    if (abs(B[0]) < abs(C[0])) {
        return false;
    }
    if (abs(B[B.maxIndex()]) < abs(A[A.maxIndex()])) {
        return false;
    }
    for (I i = 1; i <= B.maxIndex() - 1; i++) {
        if (abs(B[i]) < abs(A[i]) + abs(C[i])) {
            return false;
        }
    }
    return true;
}


template <class I, class V>
NumericArray<I, V> LUTridiagonalSolver<I, V>::solve(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C, const NumericArray<I, V>& RHS) {
    assert(isDiagonallyDominant(A, B, C));
    assert(A.minIndex() == 0);
    NumericArray<I, V> beta(A.size());
    NumericArray<I, V> gamma(A.size() - 1);
    calculateBetaGamma(A, B, C, RHS, beta, gamma);
    NumericArray<I, V> Z(A.size());
    NumericArray<I, V> U(A.size());
    calculateZU(A, B, C, RHS, beta, gamma, Z, U);
    return U;
}

template <class I, class V>
void LUTridiagonalSolver<I, V>::calculateBetaGamma(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C, const NumericArray<I, V>& RHS, NumericArray<I, V>& beta, NumericArray<I, V>& gamma) {
    beta[0] = B[0];
    gamma[0] = C[0] / beta[0];
    for (I i = 1; i <= gamma.maxIndex(); i++) {
       beta[i] = B[i] - (A[i] * gamma[i-1]);
       gamma[i] = C[i] / beta[i];
    }
    beta[beta.maxIndex()] = B[B.maxIndex()] - A[A.maxIndex()] * gamma[gamma.maxIndex()];
}

template <class I, class V>
void LUTridiagonalSolver<I, V>::calculateZU(const NumericArray<I, V>& A, const NumericArray<I, V>& B, const NumericArray<I, V>& C, const NumericArray<I, V>& RHS, const NumericArray<I, V>& beta, const NumericArray<I, V>& gamma, NumericArray<I, V>& Z, NumericArray<I, V>& U) {
    Z[0] = RHS[0] / beta[0];
    for (I i = 1; i <= A.maxIndex(); i++) {
        Z[i] = (RHS[i] - A[i] * Z[i-1]) / beta[i];
    }
    U[U.maxIndex()] = Z[Z.maxIndex()];
    for (I i = U.maxIndex() - 1; i >= U.minIndex(); i--) {
        U[i] = Z[i] - gamma[i] * U[i + 1];
    }
}

#endif
