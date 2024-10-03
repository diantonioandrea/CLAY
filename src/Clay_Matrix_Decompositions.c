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
#include <string.h>

/**
 * @brief PA = LU decomposition.
 * 
 * @param A Matrix.
 * @param L L matrix.
 * @param U U matrix.
 * @param P P matrix.
 */
void decomposeLUP(const Matrix *A, Matrix *L, Matrix *U, Matrix *P) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    #endif

    *L = *newMatrixSquareDiagonal(A->N, 1.0L);
    *P = *newMatrixSquareDiagonal(A->N, 1.0L);
    *U = *newMatrixCopy(A);

    for(Natural j = 0; j < A->N; ++j) {

        // Pivoting.
        Natural pivot = j;

        for(Natural k = j + 1; k < A->N; ++k)
            if(fabs(getMatrixAt(U, k, j)) > fabs(getMatrixAt(U, pivot, j)))
                pivot = k;

        if(j != pivot) {

            // U and P swaps.
            swapRows(U, j, pivot);
            swapRows(P, j, pivot);

            // L swaps.
            for(Natural k = 0; k < j; ++k) {
                Real temp = getMatrixAt(L, j, k);
                setMatrixAt(L, j, k, getMatrixAt(L, pivot, k));
                setMatrixAt(L, pivot, k, temp);
            }
        }

        // Elimination and update.
        for(Natural k = j + 1; k < A->N; ++k) {
            setMatrixAt(L, k, j, getMatrixAt(U, k, j) / getMatrixAt(U, j, j));

            for(Natural h = 0; h < A->M; ++h) {
                setMatrixAt(U, k, h, getMatrixAt(U, k, h) - getMatrixAt(L, k, j) * getMatrixAt(U, j, h));
            }
        }
    }
}