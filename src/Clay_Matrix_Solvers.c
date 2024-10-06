/**
 * @file Clay_Matrix_Solvers.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Matrix/Solvers.h implementation.
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

// Direct.

/**
 * @brief Solves Ax = b by gaussian elimination.
 * 
 * @param A0 Matrix.
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnGauss(const Matrix *A0, const Vector *b0) {
    #ifndef NDEBUG // Integrity check.
    assert(A0->N == A0->M);
    assert(A0->N == b0->N);
    #endif

    const Natural N = A0->N;

    Matrix *A1 = newMatrixCopy(A0);

    Vector *b1 = newVectorCopy(b0);
    Vector *x = newVector(N);

    // Gaussian elimination.

    for(Natural j = 0; j < N; ++j) {

        // Pivoting.
        Natural pivot = j;

        for(Natural k = j + 1; k < N; ++k)
            if(fabs(A1->elements[k * N + j]) > fabs(A1->elements[pivot * N + j]))
                pivot = k;

        swapRows(A1, j, pivot);
        swapElements(b1, j, pivot);

        for(Natural k = j + 1; k < N; ++k) {
            Real temp = A1->elements[k * N + j] / A1->elements[j * (N + 1)];

            for(Natural h = 0; h < N; ++h)
                A1->elements[k * N + h] -= temp * A1->elements[j * N + h];

            b1->elements[k] -= temp * b1->elements[j];
        }   
    }

    // Back substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += A1->elements[(j - 1) * N + k] * x->elements[k];

        x->elements[j - 1] = (b1->elements[j - 1] - sum) / A1->elements[(j - 1) * (N + 1)];
    }

    freeMatrix(A1);
    freeVector(b1);

    return x;
}

/**
 * @brief Solves LUx = Pb by forward and back substitution.
 * 
 * @param L Matrix.
 * @param U Matrix.
 * @param P Matrix.
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnLUP(const Matrix *L, const Matrix *U, const Matrix *P, const Vector *b0) {
    #ifndef NDEBUG // Integrity check.
    assert(L->N == b0->N);
    #endif

    const Natural N = L->N;

    Vector *b1 = mulReturnMatrixVector(P, b0);
    Vector *x = newVector(N);
    Vector *y = newVector(N);

    // Solves Ly = b1 by forward substitution.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = 0; k < j; ++k)
            sum += L->elements[j * N + k] * y->elements[k];

        y->elements[j] = (b1->elements[j] - sum) / L->elements[j * (N + 1)];
    }

    // Solves Ux = y by back substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += U->elements[(j - 1) * N + k] * x->elements[k];
        
        x->elements[j - 1] = (y->elements[j - 1] - sum) / U->elements[(j - 1) * (N + 1)];
    }

    freeVector(b1);
    freeVector(y);

    return x;
}

/**
 * @brief Solves QR = b by back substitution.
 * 
 * @param Q Matrix.
 * @param R Matrix.
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnQR(const Matrix *Q, const Matrix *R, const Vector *b0) {
    #ifndef NDEBUG // Integrity check.
    assert(Q->N == b0->N);
    #endif
    
    const Natural M = R->M;

    Vector *b1 = mulReturnTransposeMatrixVector(Q, b0);
    Vector *x = newVector(M);

    // Solves Rx = QTb by back substitution.

    for(Natural j = M; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < M; ++k)
            sum += R->elements[(j - 1) * M + k] * x->elements[k];

        x->elements[j - 1] = (b1->elements[j - 1] - sum) / R->elements[(j - 1) * (M + 1)];
    }

    freeVector(b1);

    return x;
}

/**
 * @brief Solves LLTx = b by forward and back substitution.
 * 
 * @param L Matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnLL(const Matrix *L, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(L->N == b->N);
    #endif

    const Natural N = L->N;

    Vector *x = newVector(N);
    Vector *y = newVector(N);

    // Solves Ly = b by forward substitution.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = 0; k < j; ++k)
            sum += L->elements[j * N + k] * y->elements[k];

        y->elements[j] = (b->elements[j] - sum) / L->elements[j * (N + 1)];
    }

    // Solves LTx = y by back substitution.
    // No explicit evaluation of LT.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += L->elements[k * N + (j - 1)] * x->elements[k];
        
        x->elements[j - 1] = (y->elements[j - 1] - sum) / L->elements[(j - 1) * (N + 1)];
    }

    freeVector(y);

    return x;
}