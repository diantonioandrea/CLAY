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

[[nodiscard]] Vector *solveReturnGauss(const Matrix *A0, const Vector *b0) {
    #ifndef NDEBUG // Integrity check.
    assert(A0->N == A0->M);
    #endif

    const Natural N = A0->N;

    Matrix *A1 = newMatrixCopy(A0);
    Matrix *P0 = newMatrixSquareDiagonal(N, 1.0L);

    Vector *b1 = newVectorCopy(b0);
    Vector *x0 = newVector(N);

    // Gaussian elimination.

    for(Natural j = 0; j < N; ++j) {

        // Pivoting.
        Natural pivot = j;

        for(Natural k = j + 1; k < N; ++k)
            if(fabs(A1->elements[k * N + j]) > fabs(A1->elements[pivot * N + j]))
                pivot = k;

        swapRows(A1, j, pivot);
        swapRows(P0, j, pivot);
        swapElements(b1, j, pivot);

        for(Natural k = j + 1; k < N; ++k) {
            Real temp = A1->elements[k * N + j] / A1->elements[j * (N + 1)];

            for(Natural h = 0; h < N; ++h)
                A1->elements[k * N + h] -= temp * A1->elements[j * N + h];

            b1->elements[k] -= temp * b1->elements[j];
        }   
    }

    Matrix *P1 = transposeReturnMatrix(P0);

    // Back substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += A1->elements[(j - 1) * N + k] * x0->elements[k];

        x0->elements[j - 1] = (b1->elements[j - 1] - sum) / A1->elements[(j - 1) * (N + 1)];
    }

    Vector *x1 = mulReturnMatrixVector(P1, x0);

    freeMatrix(A1);
    freeMatrix(P0);
    freeMatrix(P1);

    freeVector(b1);
    freeVector(x0);

    return x1;
}

/**
 * @brief Solves LUx = Pb.
 * 
 * @param L Matrix.
 * @param U Matrix.
 * @param P Matrix.
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnLUP(const Matrix *L, const Matrix *U, const Matrix *P, const Vector *b0) {
    const Natural N = L->N;

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

    freeVector(b1);
    freeVector(y);

    return x;
}