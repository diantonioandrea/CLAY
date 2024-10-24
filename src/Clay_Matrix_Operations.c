/**
 * @file Clay_Matrix_Operations.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Matrix/Operations.h implementation.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

/**
 * @brief Matrix + real.
 * 
 * @param matrix Matrix.
 * @param real Real.
 */
void addMatrixScalar(Matrix *matrix, const Real real) {
    for(Natural j = 0; j < matrix->N * matrix->M; ++j)
        matrix->elements[j] += real;
}

/**
 * @brief Matrix - real.
 * 
 * @param matrix Matrix.
 * @param real Real.
 */
void subMatrixScalar(Matrix *matrix, const Real real) {
    for(Natural j = 0; j < matrix->N * matrix->M; ++j)
        matrix->elements[j] -= real;
}

/**
 * @brief Matrix * real.
 * 
 * @param matrix Matrix.
 * @param real Real.
 */
void mulMatrixScalar(Matrix *matrix, const Real real) {
    for(Natural j = 0; j < matrix->N * matrix->M; ++j)
        matrix->elements[j] *= real;
}

/**
 * @brief Matrix / real.
 * 
 * @param matrix Matrix.
 * @param real Real.
 */
void divMatrixScalar(Matrix *matrix, const Real real) {
    for(Natural j = 0; j < matrix->N * matrix->M; ++j)
        matrix->elements[j] /= real;
}

/**
 * @brief Real / matrix.
 * 
 * @param matrix Matrix.
 * @param real Real.
 */
void divScalarMatrix(Matrix *matrix, const Real real) {
    for(Natural j = 0; j < matrix->N * matrix->M; ++j)
        matrix->elements[j] = real / matrix->elements[j];
}

/**
 * @brief Matrix + matrix.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 */
void addMatrixMatrix(Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->N == matrix1->N);
    assert(matrix0->M == matrix1->M);
    #endif

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix0->elements[j] += matrix1->elements[j];
}

/**
 * @brief Matrix - matrix.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 */
void subMatrixMatrix(Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->N == matrix1->N);
    assert(matrix0->M == matrix1->M);
    #endif

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix0->elements[j] -= matrix1->elements[j];
}

/**
 * @brief Row swap.
 * 
 * @param matrix Matrix.
 * @param n0 Row index.
 * @param n1 Row index.
 */
void swapRows(Matrix *matrix, const Natural n0, const Natural n1) {
    #ifndef NDEBUG // Integrity check.
    assert(n0 < matrix->N);
    assert(n1 < matrix->N);
    #endif

    if(n0 != n1)
        for(Natural k = 0; k < matrix->M; ++k) {
            Real temp = matrix->elements[n0 * matrix->M + k];
            matrix->elements[n0 * matrix->M + k] = matrix->elements[n1 * matrix->M + k];
            matrix->elements[n1 * matrix->M + k] = temp;
        }
}

/**
 * @brief Column swap.
 * 
 * @param matrix Matrix.
 * @param m0 Column index.
 * @param m1 Column index.
 */
void swapColumns(Matrix *matrix, const Natural m0, const Natural m1) {
    #ifndef NDEBUG // Integrity check.
    assert(m0 < matrix->M);
    assert(m1 < matrix->M);
    #endif

    if(m0 != m1)
        for(Natural j = 0; j < matrix->N; ++j) {
            Real temp = matrix->elements[j * matrix->M + m0];
            matrix->elements[j * matrix->M + m0] = matrix->elements[j * matrix->M + m1];
            matrix->elements[j * matrix->M + m1] = temp;
        }
}

/**
 * @brief Partial row swap.
 * 
 * @param matrix Matrix.
 * @param n0 Row index.
 * @param n1 Row index.
 * @param m Column index.
 */
void swapRowsFrom(Matrix *matrix, const Natural n0, const Natural n1, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n0 < matrix->N);
    assert(n1 < matrix->N);
    assert(m <= matrix->M);
    #endif

    if((n0 != n1) && (m < matrix->M))
        for(Natural k = m; k < matrix->M; ++k) {
            Real temp = matrix->elements[n0 * matrix->M + k];
            matrix->elements[n0 * matrix->M + k] = matrix->elements[n1 * matrix->M + k];
            matrix->elements[n1 * matrix->M + k] = temp;
        }
}

/**
 * @brief Partial column swap.
 * 
 * @param matrix Matrix.
 * @param m0 Column index.
 * @param m1 Column index.
 * @param n Row index.
 */
void swapColumnsFrom(Matrix *matrix, const Natural m0, const Natural m1, const Natural n) {
    #ifndef NDEBUG // Integrity check.
    assert(m0 < matrix->M);
    assert(m1 < matrix->M);
    assert(n <= matrix->N);
    #endif

    if((m0 != m1) && (n < matrix->N))
        for(Natural j = n; j < matrix->N; ++j) {
            Real temp = matrix->elements[j * matrix->M + m0];
            matrix->elements[j * matrix->M + m0] = matrix->elements[j * matrix->M + m1];
            matrix->elements[j * matrix->M + m1] = temp;
        }
}

/**
 * @brief Partial row swap.
 * 
 * @param matrix Matrix.
 * @param n0 Row index.
 * @param n1 Row index.
 * @param m Column index.
 */
void swapRowsUntil(Matrix *matrix, const Natural n0, const Natural n1, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n0 < matrix->N);
    assert(n1 < matrix->N);
    assert(m <= matrix->M);
    #endif

    if((n0 != n1) && (m > 0))
        for(Natural k = 0; k < m; ++k) {
            Real temp = matrix->elements[n0 * matrix->M + k];
            matrix->elements[n0 * matrix->M + k] = matrix->elements[n1 * matrix->M + k];
            matrix->elements[n1 * matrix->M + k] = temp;
        }
}

/**
 * @brief Partial column swap.
 * 
 * @param matrix Matrix.
 * @param m0 Column index.
 * @param m1 Column index.
 * @param n Row index.
 */
void swapColumnsUntil(Matrix *matrix, const Natural m0, const Natural m1, const Natural n) {
    #ifndef NDEBUG // Integrity check.
    assert(m0 < matrix->M);
    assert(m1 < matrix->M);
    assert(n < matrix->N);
    #endif

    if((m0 != m1) && (n > 0))
        for(Natural j = 0; j < n; ++j) {
            Real temp = matrix->elements[j * matrix->M + m0];
            matrix->elements[j * matrix->M + m0] = matrix->elements[j * matrix->M + m1];
            matrix->elements[j * matrix->M + m1] = temp;
        }
}

/**
 * @brief Matrix + real.
 * 
 * @param matrix0 Matrix.
 * @param real Real.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *addReturnMatrixScalar(const Matrix *matrix0, const Real real) {
    Matrix *matrix1 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix1->elements[j] = matrix0->elements[j] + real;

    return matrix1;
}

/**
 * @brief Matrix - real.
 * 
 * @param matrix0 Matrix.
 * @param real Real.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *subReturnMatrixScalar(const Matrix *matrix0, const Real real) {
    Matrix *matrix1 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix1->elements[j] = matrix0->elements[j] - real;

    return matrix1;
}

/**
 * @brief Matrix * real.
 * 
 * @param matrix0 Matrix.
 * @param real Real.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *mulReturnMatrixScalar(const Matrix *matrix0, const Real real) {
    Matrix *matrix1 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix1->elements[j] = matrix0->elements[j] * real;

    return matrix1;
}

/**
 * @brief Matrix / real.
 * 
 * @param matrix0 Matrix.
 * @param real Real.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *divReturnMatrixScalar(const Matrix *matrix0, const Real real) {
    Matrix *matrix1 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix1->elements[j] = matrix0->elements[j] / real;

    return matrix1;
}

/**
 * @brief Real / matrix.
 * 
 * @param matrix0 Matrix.
 * @param real Real.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *divReturnScalarMatrix(const Matrix *matrix0, const Real real) {
    Matrix *matrix1 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix1->elements[j] = real / matrix0->elements[j];

    return matrix1;
}

/**
 * @brief Matrix + matrix.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *addReturnMatrixMatrix(const Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->N == matrix1->N);
    assert(matrix0->M == matrix1->M);
    #endif

    Matrix *matrix2 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix2->elements[j] = matrix0->elements[j] + matrix1->elements[j];

    return matrix2;
}

/**
 * @brief Matrix - matrix.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *subReturnMatrixMatrix(const Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->N == matrix1->N);
    assert(matrix0->M == matrix1->M);
    #endif

    Matrix *matrix2 = newMatrix(matrix0->N, matrix0->M);

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix2->elements[j] = matrix0->elements[j] - matrix1->elements[j];

    return matrix2;
}

/**
 * @brief Matrix * vector.
 * 
 * @param matrix Matrix.
 * @param vector0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnMatrixVector(const Matrix *matrix, const Vector *vector0) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix->M == vector0->N);
    #endif

    Vector *vector1 = newVector(matrix->N);

    for(Natural j = 0; j < matrix->N; ++j)
        for(Natural k = 0; k < matrix->M; ++k)
            vector1->elements[j] += matrix->elements[j * matrix->M + k] * vector0->elements[k];

    return vector1;
}

/**
 * @brief Transpose matrix * vector.
 * 
 * @param matrix Matrix.
 * @param vector0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnTransposeMatrixVector(const Matrix *matrix, const Vector *vector0) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix->N == vector0->N);
    #endif

    Vector *vector1 = newVector(matrix->M);

    for(Natural j = 0; j < matrix->M; ++j)
        for(Natural k = 0; k < matrix->N; ++k)
            vector1->elements[j] += matrix->elements[k * matrix->N + j] * vector0->elements[k];

    return vector1;
}

/**
 * @brief Vector * matrix.
 * 
 * @param vector0 Vector.
 * @param matrix Matrix.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnVectorMatrix(const Vector *vector0, const Matrix *matrix) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == matrix->N);
    #endif

    Vector *vector1 = newVector(matrix->M);

    for(Natural k = 0; k < matrix->M; ++k)
        for(Natural j = 0; j < matrix->N; ++j)
            vector1->elements[k] += vector0->elements[j] * matrix->elements[j * matrix->M + k];
    
    return vector1;
}

/**
 * @brief Matrix * matrix.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *mulReturnMatrixMatrix(const Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->M == matrix1->N);
    #endif

    Matrix *matrix2 = newMatrix(matrix0->N, matrix1->M);

    for(Natural j = 0; j < matrix0->N; ++j)
        for(Natural k = 0; k < matrix1->M; ++k) {
            Real product = 0.0L;

            for(Natural h = 0; h < matrix0->M; ++h)
                product += matrix0->elements[j * matrix0->M + h] * matrix1->elements[h * matrix1->M + k];

            matrix2->elements[j * matrix1->M + k] = product;
        }

    return matrix2;
}

/**
 * @brief Transpose matrix * matrix.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *mulReturnTransposeMatrixMatrix(const Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->N == matrix1->N);
    #endif

    Matrix *matrix2 = newMatrix(matrix0->M, matrix1->M);

    for(Natural j = 0; j < matrix0->M; ++j)
        for(Natural k = 0; k < matrix1->M; ++k) {
            Real product = 0.0L;

            for(Natural h = 0; h < matrix0->N; ++h)
                product += matrix0->elements[h * matrix0->N + j] * matrix1->elements[h * matrix1->M + k];

            matrix2->elements[j * matrix1->M + k] = product;
        }

    return matrix2;
}

/**
 * @brief Matrix * Householder reflector.
 * 
 * @param matrix Matrix.
 * @param vector Householder reflector.
 * @param d Depth.
 */
void mulMatrixHouseholder(Matrix *matrix, const Vector *vector, const Natural d) {
    #ifndef NDEBUG // Integrity check.
    assert(vector->N == matrix->N);
    assert(d < matrix->N);
    assert(d < matrix->M);
    #endif

    register Natural j, h, k;

    for(j = 0; j < matrix->N; ++j) {
        Real sum = 0.0L;

        for(h = d; h < matrix->M; ++h)
            sum += matrix->elements[j * matrix->M + h] * vector->elements[h];

        for(k = d; k < matrix->M; ++k)
            matrix->elements[j * matrix->M + k] -= 2.0L * vector->elements[k] * sum;
    }
}

/**
 * @brief Householder reflector * matrix.
 * 
 * @param vector Householder reflector.
 * @param matrix Matrix.
 * @param d Depth.
 */
void mulHouseholderMatrix(const Vector *vector, Matrix *matrix, const Natural d) {
    #ifndef NDEBUG // Integrity check.
    assert(vector->N == matrix->N);
    assert(d < matrix->N);
    assert(d < matrix->M);
    #endif

    register Natural j, h, k;

    for(k = d; k < matrix->M; ++k) {
        Real sum = 0.0L;

        for(h = d; h < matrix->N; ++h)
            sum += vector->elements[h] * matrix->elements[h * matrix->M + k];

        for(j = d; j < matrix->N; ++j)
            matrix->elements[j * matrix->M + k] -= 2.0L * vector->elements[j] * sum;
    }
}

/**
 * @brief Transpose.
 * 
 * @param matrix0 Matrix.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *transposeReturnMatrix(const Matrix *matrix0) {
    Matrix *matrix1 = newMatrix(matrix0->M, matrix0->N);

    for(Natural j = 0; j < matrix0->N; ++j)
        for(Natural k = 0; k < matrix0->M; ++k)
            matrix1->elements[k * matrix0->N + j] = matrix0->elements[j * matrix0->M + k];

    return matrix1;
}

/**
 * @brief Row getter.
 * 
 * @param matrix Matrix.
 * @param n Row index.
 * @return Vector* 
 */
[[nodiscard]] Vector *getRow(const Matrix *matrix, const Natural n) {
    #ifndef NDEBUG // Integrity check.
    assert(n < matrix->N);
    #endif

    Vector *vector = newVector(matrix->M);

    for(Natural k = 0; k < matrix->M; ++k)
        vector->elements[k] = matrix->elements[n * matrix->M + k];

    return vector;
}

/**
 * @brief Column getter.
 * 
 * @param matrix Matrix.
 * @param m Column index.
 * @return Vector* 
 */
[[nodiscard]] Vector *getColumn(const Matrix *matrix, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(m < matrix->M);
    #endif

    Vector *vector = newVector(matrix->N);

    for(Natural j = 0; j < matrix->N; ++j)
        vector->elements[j] = matrix->elements[j * matrix->M + m];

    return vector;
}

/**
 * @brief Partial row getter.
 * 
 * @param matrix Matrix.
 * @param n Row index.
 * @param m Column index.
 * @return Vector* 
 */
[[nodiscard]] Vector *getRowFrom(const Matrix *matrix, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < matrix->N);
    assert(m < matrix->M);
    #endif

    Vector *vector = newVector(matrix->M);

    for(Natural k = m; k < matrix->M; ++k)
        vector->elements[k] = matrix->elements[n * matrix->M + k];

    return vector;
} 

/**
 * @brief Partial column getter.
 * 
 * @param matrix Matrix.
 * @param m Column index.
 * @param n Row index.
 * @return Vector* 
 */
[[nodiscard]] Vector *getColumnFrom(const Matrix *matrix, const Natural m, const Natural n) {
    #ifndef NDEBUG // Integrity check.
    assert(n < matrix->N);
    assert(m < matrix->M);
    #endif

    Vector *vector = newVector(matrix->N);

    for(Natural j = n; j < matrix->N; ++j)
        vector->elements[j] = matrix->elements[j * matrix->M + m];

    return vector;
}

/**
 * @brief Diagonal check.
 * 
 * @param matrix Matrix.
 * @return true 
 * @return false 
 */
bool isDiagonal(const Matrix *matrix) {
    for(Natural j = 0; j < matrix->N; ++j)
        for(Natural k = 0; k < matrix->M; ++k)
            if((fabs(matrix->elements[j * matrix->M + k]) > TOLERANCE) && (j != k))
                return false;

    return true;
}

/**
 * @brief Lower triangular check.
 * 
 * @param matrix Matrix.
 * @return true 
 * @return false 
 */
bool isLowerTriangular(const Matrix *matrix) {
    for(Natural j = 0; j < matrix->N; ++j)
        for(Natural k = 0; k < j; ++k)
            if(fabs(matrix->elements[j * matrix->M + k]) > TOLERANCE)
                return false;

    return true;
}

/**
 * @brief Upper triangular check.
 * 
 * @param matrix Matrix.
 * @return true 
 * @return false 
 */
bool isUpperTriangular(const Matrix *matrix) {
    for(Natural j = 0; j < matrix->N; ++j)
        for(Natural k = j + 1; k < matrix->M; ++k)
            if(fabs(matrix->elements[j * matrix->M + k]) > TOLERANCE)
                return false;

    return true;
}

/**
 * @brief Symmetry check.
 * 
 * @param matrix Matrix.
 * @return true 
 * @return false 
 */
bool isSymmetric(const Matrix *matrix) {
    if(matrix->N != matrix->M)
        return false;

    for(Natural j = 0; j < matrix->N; ++j)
        for(Natural k = 0; k < j; ++k)
            if(fabs(matrix->elements[j * matrix->M + k] - matrix->elements[k * matrix->M + j]) > TOLERANCE)
                return false;

    return true;
}