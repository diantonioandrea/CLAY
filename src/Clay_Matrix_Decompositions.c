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

    return newMatrixUniformDiagonal(A->N, 1.0L);
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

    return newMatrixUniformDiagonal(A->N, 1.0L);
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

// QR.

/**
 * @brief Q matrix initialization.
 * 
 * @param A Matrix.
 * @return Matrix* 
 */
Matrix * newMatrixQR_Q(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N >= A->M);
    #endif

    return newMatrixSquare(A->N);
}

/**
 * @brief R matrix initialization.
 * 
 * @param A Matrix.
 * @return Matrix* 
 */
Matrix * newMatrixQR_R(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N >= A->M);
    #endif

    return newMatrix(A->N, A->M);
}

/**
 * @brief A = QR decomposition.
 * 
 * @param A A matrix.
 * @param Q Q matrix.
 * @param R R matrix.
 */
void decomposeQR(const Matrix *A, Matrix *Q, Matrix *R) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N >= A->M);
    #endif

    const Natural N = A->N;
    const Natural M = A->M;

    Matrix *P = newMatrixUniformDiagonal(M, 1.0L);

    for(Natural j = 0; j < M; ++j) {
        
        // Vectors.
        Vector *xj = returnColumn(A, j);
        Vector *zj = newVector(N);
        Vector *ej = newVector(N);

        Real beta = ((xj->elements[j] >= 0.0L) ? 1.0L : -1.0L) * norm2ReturnVector(xj);
        ej->elements[j] = 1.0L;

        zj->elements[j] = beta + xj->elements[j];

        for(Natural k = j + 1; k < N; ++k)
            zj->elements[k] = xj->elements[k];

        // Householder vector.
        Vector *wj = divReturnVectorScalar(zj, norm2ReturnVector(zj));

        // Householder matrix.
        Matrix *Pj = newMatrixUniformDiagonal(N, 1.0L);
        Matrix *Wj = newMatrixRankOne(wj, wj);
        mulMatrixScalar(Wj, 2.0L);
        subMatrixMatrix(Pj, Wj);

        *P = *mulReturnMatrixMatrix(P, Pj);
        
        // Q matrix.
        Vector *qj = mulReturnMatrixVector(P, ej);

        for(Natural k = 0; k < M; ++k)
            Q->elements[k * M + j] = qj->elements[k];

        freeVector(xj);
        freeVector(zj);
        freeVector(wj);
        freeVector(ej);
        freeVector(qj);

        freeMatrix(Pj);
        freeMatrix(Wj);
    }

    Matrix *QT = transposeReturnMatrix(Q);
    *R = *mulReturnMatrixMatrix(QT, A);

    freeMatrix(P);
    freeMatrix(QT);
}