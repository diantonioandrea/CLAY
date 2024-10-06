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
 * @param A0 Matrix.
 * @return Vector* 
 */
Vector *eigenvaluesReturnQR(const Matrix *A0) {
    #ifndef NDEBUG // Integrity check.
    assert(isSymmetric(A0));
    #endif

    const Natural N = A0->N;

    Matrix *A1 = newMatrixCopy(A0);
    Matrix *Q = newMatrixQR_Q(A0);
    Matrix *R = newMatrixQR_R(A0);

    Vector *e = newVector(N);

    for(Natural j = 0; j < QR_ITER_MAX; ++j) {
        decomposeQR(A1, Q, R);
        *A1 = *mulReturnMatrixMatrix(R, Q);

        if(isUpperTriangular(A1))
            break;
    }

    for(Natural j = 0; j < N; ++j)
        e->elements[j] = A1->elements[j * (N + 1)];

    freeMatrix(A1);
    freeMatrix(Q);
    freeMatrix(R);

    return e;
}