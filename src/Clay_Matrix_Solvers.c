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

// Triangular.

/**
 * @brief Solves Lx = b by forward substitution.
 * 
 * @param L Lower triangular matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnLowerTriangular(const Matrix *L, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(L->N == L->M);
    assert(L->N <= b->N);
    #endif

    const Natural N = L->N;

    Vector *x = newVector(N);

    // Forward substitution.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = 0; k < j; ++k)
            sum += L->elements[j * N + k] * x->elements[k];

        x->elements[j] = (b->elements[j] - sum) / L->elements[j * (N + 1)];
    }

    return x;
}

/**
 * @brief Solves Ux = b by backward substitution.
 * 
 * @param U Upper triangular matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnUpperTriangular(const Matrix *U, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(U->N == U->M);
    assert(U->N <= b->N);
    #endif

    const Natural N = U->N;

    Vector *x = newVector(N);

    // Backward substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += U->elements[(j - 1) * N + k] * x->elements[k];
        
        x->elements[j - 1] = (b->elements[j - 1] - sum) / U->elements[(j - 1) * (N + 1)];
    }

    return x;
}

/**
 * @brief Solves Lx = b by forward substitution with no division.
 * 
 * @param L Lower triangular matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnReducedLowerTriangular(const Matrix *L, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(L->N == L->M);
    assert(L->N <= b->N);
    #endif

    const Natural N = L->N;

    Vector *x = newVector(N);

    // Forward substitution.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = 0; k < j; ++k)
            sum += L->elements[j * N + k] * x->elements[k];

        x->elements[j] = b->elements[j] - sum;
    }

    return x;
}

/**
 * @brief Solves Ux = b by backward substitution with no division.
 * 
 * @param U Upper triangular matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnReducedUpperTriangular(const Matrix *U, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(U->N == U->M);
    assert(U->N <= b->N);
    #endif

    const Natural N = U->N;

    Vector *x = newVector(N);

    // Backward substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += U->elements[(j - 1) * N + k] * x->elements[k];
        
        x->elements[j - 1] = b->elements[j - 1] - sum;
    }

    return x;
}

/**
 * @brief Solves LTx = b by backward substitution with no explicit transposition.
 * 
 * @param L Lower triangular matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnTransposeLowerTriangular(const Matrix *L, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(L->N == L->M);
    assert(L->N <= b->N);
    #endif

    const Natural N = L->N;

    Vector *x = newVector(N);

    // Backward substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = j; k < N; ++k)
            sum += L->elements[k * N + j - 1] * x->elements[k];
        
        x->elements[j - 1] = (b->elements[j - 1] - sum) / L->elements[(j - 1) * (N + 1)];
    }

    return x;
}

/**
 * @brief Solves UTx = b by backward substitution with no explicit transposition.
 * 
 * @param U Upper triangular matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnTransposeUpperTriangular(const Matrix *U, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(U->N == U->M);
    assert(U->N <= b->N);
    #endif

    const Natural N = U->N;

    Vector *x = newVector(N);

    // Forward substitution.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = 0; k < j; ++k)
            sum += U->elements[k * N + j] * x->elements[k];

        x->elements[j] = (b->elements[j] - sum) / U->elements[j * (N + 1)];
    }

    return x;
}

// Gauss.

/**
 * @brief Solves Ax = b by gaussian elimination.
 * 
 * @param A0 Matrix.
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnGauss(const Matrix *A0, const Vector *b0) {
    const Natural N = A0->N;

    Matrix *A1 = newMatrixCopy(A0);
    Vector *b1 = newVectorCopy(b0);

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

    Vector *x = solveReturnUpperTriangular(A1, b1);

    freeMatrix(A1);
    freeVector(b1);

    return x;
}

// Decompositions.

/**
 * @brief Solves LUx = Pb by forward and back substitution.
 * 
 * @param LU Matrix.
 * @param P Matrix.
 * @param b0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnLUP(const Matrix *LU, const Matrix *P, const Vector *b0) {
    Vector *b1 = mulReturnMatrixVector(P, b0);

    Vector *y = solveReturnReducedLowerTriangular(LU, b1);
    Vector *x = solveReturnUpperTriangular(LU, y);

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
    Vector *b1 = mulReturnTransposeMatrixVector(Q, b0);

    Vector *x = solveReturnUpperTriangular(R, b1);

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
    Vector *y = solveReturnLowerTriangular(L, b);
    Vector *x = solveReturnTransposeLowerTriangular(L, y);

    freeVector(y);

    return x;
}