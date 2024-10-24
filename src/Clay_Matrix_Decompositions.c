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
 * @brief P matrix initialization.
 * 
 * @param A Matrix.
 * @return Matrix* 
 */
Matrix *newMatrixLUP_P(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N == A->M);
    #endif

    return newMatrixUniformDiagonal(A->N, 1.0L);
}

/**
 * @brief PA = LU decomposition.
 * 
 * @param LU LU Matrix.
 * @param P P matrix.
 */
void decomposeLUP(Matrix *LU, Matrix *P) {
    #ifndef NDEBUG // Integrity check.
    assert(LU->N == LU->M);
    #endif

    const Natural N = LU->N;
    for(Natural j = 0; j < N; ++j) {

        // Pivoting.
        Natural pivot = j;

        for(Natural k = j + 1; k < N; ++k)
            if(fabs(LU->elements[k * N + j]) > fabs(LU->elements[pivot * N + j]))
                pivot = k;

        // Swaps.
        swapRows(LU, j, pivot);
        swapRows(P, j, pivot);

        #ifndef NDEBUG // Integrity check.
        assert(fabs(LU->elements[j * (N + 1)]) > TOLERANCE);
        #endif

        // Elimination and update.
        for(Natural k = j + 1; k < N; ++k) {
            Real Ljk = LU->elements[k * N + j] / LU->elements[j * (N + 1)];

            for(Natural h = 0; h < N; ++h)
                LU->elements[k * N + h] -= Ljk * LU->elements[j * N + h];

            LU->elements[k * N + j] = Ljk;
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
Matrix *newMatrixQR_Q(const Matrix *A) {
    #ifndef NDEBUG // Integrity check.
    assert(A->N >= A->M);
    #endif

    return newMatrixUniformDiagonal(A->N, 1.0L);
}

/**
 * @brief Q matrix initialization.
 * 
 * @param A Hessenmberg matrix.
 * @return Matrix* 
 */
Matrix *newMatrixHessenbergQR_Q(const Matrix *A) {
    return newMatrixUniformDiagonal(A->N, 1.0L);
}

/**
 * @brief R matrix initialization.
 * 
 * @param A Hessenberg matrix.
 * @return Matrix* 
 */
Matrix *newMatrixHessenbergQR_R(const Matrix *A) {
    return newMatrixCopy(A);
}

/**
 * @brief Householder matrix.
 * 
 * @param vector Vector.
 * @return Matrix* 
 */
Matrix *newMatrixHouseholder(const Vector *vector) {
    Matrix *matrix = newMatrixSquare(vector->N);

    for(Natural j = 0; j < vector->N; ++j)
        for(Natural k = 0; k < vector->N; ++k)
            matrix->elements[j * vector->N + k] = ((j == k) ? 1.0L : 0.0L) - 2.0L * vector->elements[j] * vector->elements[k];

    return matrix;
}

/**
 * @brief A = QR in-place decomposition.
 * 
 * @param Q Q matrix.
 * @param R R matrix.
 */
void decomposeQR(Matrix *Q, Matrix *R) {
    #ifndef NDEBUG // Integrity check.
    assert(R->N >= R->M);
    #endif

    const Natural N = R->N;
    const Natural M = R->M;
    Real s = 0.0L;

    Matrix *Pj = newMatrixSquare(N);
    Vector *xj = newVector(N), *zj = newVector(N), *ej = newVector(N), *wj = newVector(N);

    for(Natural j = 0; j < M; ++j) {

        if(j > 0) {
            ej->elements[j - 1] = 0.0L;
            zj->elements[j - 1] = 0.0L;
        }
        
        // Vectors.
        *xj = *getColumn(R, j);

        for(Natural h = 0; h < j; ++h)
            xj->elements[h] = 0.0L;

        s = ((xj->elements[j] >= 0.0L) ? 1.0L : -1.0L) * norm2ReturnVector(xj);
        zj->elements[j] = s + xj->elements[j];
        ej->elements[j] = 1.0L;

        for(Natural k = j + 1; k < N; ++k)
            zj->elements[k] = xj->elements[k];

        // Householder matrix.
        *wj = *divReturnVectorScalar(zj, norm2ReturnVector(zj));
        *Pj = *newMatrixHouseholder(wj);
        
        // Q matrix.
        *Q = *mulReturnMatrixMatrix(Q, Pj);

        // R matrix.
        *R = *mulReturnMatrixMatrix(Pj, R);
    }

    freeVector(xj);
    freeVector(zj);
    freeVector(wj);
    freeVector(ej);

    freeMatrix(Pj);
}

/**
 * @brief Hessenberg A = QR in-place decomposition.
 * 
 * @param Q Q matrix.
 * @param R R matrix.
 */
void decomposeHessenbergQR(Matrix *Q, Matrix *R) {
    #ifndef NDEBUG // Integrity check.
    assert(R->N >= R->M);
    #endif

    const Natural N = R->N;
    const Natural M = R->M;

    Matrix *Gj = newMatrixUniformDiagonal(N, 1.0L);
    Real c = 0.0L, s = 0.0L, g = 0.0L;

    for(Natural j = 0; j < M - 1; ++j) {

        // Rotation coefficients.
        c = R->elements[j * (M + 1)];
        s = R->elements[j * (M + 1) + M];
        g = sqrt(c * c + s * s);

        c /= g;
        s /= g;

        // Rotation.
        Gj->elements[j * (N + 1)] = c;
        Gj->elements[(j + 1) * (N + 1)] = c;
        Gj->elements[j * N + j + 1] = s;
        Gj->elements[(j + 1) * N + j] = -s;

        // Q and R update.
        *R = *mulReturnMatrixMatrix(Gj, R);
        *Q = *mulReturnMatrixMatrix(Q, Gj);

        // Rotation reset.
        Gj->elements[j * (N + 1)] = 1.0L;
        Gj->elements[j * N + j + 1] = 0.0L;
        Gj->elements[(j + 1) * N + j] = 0.0L;
    }

    *Q = *transposeReturnMatrix(Q);

    freeMatrix(Gj);
}

// Cholesky.

/**
 * @brief A = LLT in-place decomposition. Fails on non-SPD matrices.
 * 
 * @param L L matrix.
 */
void decomposeLL(Matrix *L) {
    #ifndef NDEBUG // Integrity check.
    assert(isSymmetric(L));
    #endif

    const Natural N = L->N;
    Real sum = 0.0L;

    for(Natural j = 0; j < N; ++j) {
        for(Natural k = 0; k < j; ++k) {
            sum = 0.0L;

            for(Natural h = 0; h < k; ++h)
                sum += L->elements[j * N + h] * L->elements[k * N + h];

            L->elements[j * N + k] = (L->elements[j * N + k] - sum) / L->elements[k * (N + 1)];
        }

        sum = 0.0L;

        for(Natural h = 0; h < j; ++h)
            sum += L->elements[j * N + h] * L->elements[j * N + h];

        #ifndef NDEBUG // Integrity check.
        assert(L->elements[j * (N + 1)] - sum > TOLERANCE);
        #endif

        L->elements[j * (N + 1)] = sqrt(L->elements[j * (N + 1)] - sum);
    }

    for(Natural j = 0; j < N; ++j)
        for(Natural k = j + 1; k < N; ++k)
            L->elements[j * N + k] = 0.0L;
}