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

/**
 * @brief Solves Ax = b by LUP decomposition.
 * 
 * @param A Matrix
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnLUP(const Matrix *A, const Vector *b0) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    assert(A->N == b0->N);
    #endif

    const Natural N = A->N;

    Matrix *L = newMatrixLUP_L(A);
    Matrix *U = newMatrixLUP_U(A);
    Matrix *P = newMatrixLUP_P(A);

    decomposeLUP(A, L, U, P);

    Vector *b1 = mulReturnMatrixVector(P, b0);
    Vector *x = newVector(N);
    Vector *y = newVector(N);

    // Solves Ly = b1.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = 0; k < j; ++k)
            sum += L->elements[j * N + k] * y->elements[k];

        y->elements[j] = (b1->elements[j] - sum) / L->elements[j * (N + 1)];
    }

    // Solves Ux = y.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += U->elements[(j - 1) * N + k] * x->elements[k];
        
        x->elements[j - 1] = (y->elements[j - 1] - sum) / U->elements[(j - 1) * (N + 1)];
    }

    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(P);

    freeVector(b1);
    freeVector(y);

    return x;
}