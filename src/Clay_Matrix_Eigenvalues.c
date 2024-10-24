/**
 * @file Clay_Matrix_Eigenvalues.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Matrix/Eigenvalues.h implementation.
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

// QR.

/**
 * @brief Evaluates A's eigenvalues.
 * 
 * @param A Matrix.
 * @return Vector* 
 */
Vector *eigenvaluesReturnQR(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(isSymmetric(A));
    #endif

    const Natural N = A->N;

    Matrix *Q = newMatrixQR_Q(A);
    Matrix *R = newMatrixCopy(A);

    Vector *e = newVector(N);

    for(Natural j = 0; j < QR_ITER_MAX; ++j) {
        decomposeQR(Q, R);
        *R = *mulReturnMatrixMatrix(R, Q);

        if(isUpperTriangular(R))
            break;
    }

    for(Natural j = 0; j < N; ++j)
        e->elements[j] = R->elements[j * (N + 1)];

    freeMatrix(Q);
    freeMatrix(R);

    return e;
}