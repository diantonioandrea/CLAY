/**
 * @file Clay_Matrix_Decompositions.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Matrix/Decompositions.h implementation.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

// LUP.

/**
 * @brief L matrix initialization.
 * 
 * @param A Matrix.
 * @return Matrix* 
 */
Matrix * newMatrixLUP_L(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    #endif

    return newMatrixSquareDiagonal(A->N, 1.0L);
}

/**
 * @brief U matrix initialization.
 * 
 * @param A Matrix.
 * @return Matrix* 
 */
Matrix * newMatrixLUP_U(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    #endif
    
    return newMatrixCopy(A);
}

/**
 * @brief P matrix initialization.
 * 
 * @param A Matrix.
 * @return Matrix* 
 */
Matrix * newMatrixLUP_P(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    #endif

    return newMatrixSquareDiagonal(A->N, 1.0L);
}

/**
 * @brief PA = LU decomposition.
 * 
 * @param A A Matrix.
 * @param L L matrix.
 * @param U U matrix.
 * @param P P matrix.
 */
void decomposeLUP(const Matrix *A, Matrix *L, Matrix *U, Matrix *P) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    #endif

    const Natural N = A->N;
    for(Natural j = 0; j < N; ++j) {

        // Pivoting.
        Natural pivot = j;

        for(Natural k = j + 1; k < N; ++k)
            if(fabs(U->elements[k * N + j]) > fabs(U->elements[pivot * N + j]))
                pivot = k;

        // Swaps.
        swapRows(U, j, pivot);
        swapRows(P, j, pivot);
        swapRowsUntil(L, j, pivot, j);

        // Elimination and update.
        for(Natural k = j + 1; k < N; ++k) {
            L->elements[k * N + j] = U->elements[k * N + j] / U->elements[j * (N + 1)];

            for(Natural h = 0; h < N; ++h)
                U->elements[k * N + h] -= L->elements[k * N + j] * U->elements[j * N + h];
        }
    }
}