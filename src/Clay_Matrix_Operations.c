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
        for(Natural k = 0; k < matrix1->M; ++k)
            for(Natural h = 0; h < matrix0->M; ++h)
                matrix2->elements[j * matrix1->M + k] += matrix0->elements[j * matrix0->M + h] * matrix1->elements[h * matrix1->M + k];

    return matrix2;
}