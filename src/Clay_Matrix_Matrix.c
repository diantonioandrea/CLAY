/**
 * @file Clay_Matrix_Matrix.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Matrix/Matrix.h implementation.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

/**
 * @brief Matrix constructor.
 * 
 * @param N Rows.
 * @param M Columns.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *newMatrix(const Natural N, const Natural M) {
    #ifndef NDEBUG // Integrity check.
    assert(N > 0);
    assert(M > 0);
    #endif

    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));

    matrix->N = N;
    matrix->M = M;
    matrix->elements = (Real *) calloc(N * M, sizeof(Real));

    return matrix;
}

[[nodiscard]] Matrix *newMatrixCopy(const Matrix *matrix0) {
    Matrix *matrix1 = (Matrix *) malloc(sizeof(Matrix));

    matrix1->N = matrix0->N;
    matrix1->M = matrix0->M;
    matrix1->elements = (Real *) malloc(matrix0->N * matrix0->M * sizeof(Real));

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix1->elements[j] = matrix0->elements[j];

    return matrix1;
}

/**
 * @brief Square matrix constructor.
 * 
 * @param N Rows and columns.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *newMatrixSquare(const Natural N) {
    #ifndef NDEBUG // Integrity check.
    assert(N > 0);
    #endif

    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));

    matrix->N = N;
    matrix->M = N;
    matrix->elements = (Real *) calloc(N * N, sizeof(Real));

    return matrix;
}

/**
 * @brief Uniform diagonal matrix constructor.
 * 
 * @param N Rows and columns.
 * @param real Real.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *newMatrixUniformDiagonal(const Natural N, const Real real) {
    #ifndef NDEBUG // Integrity check.
    assert(N > 0);
    #endif

    Matrix *matrix = newMatrixSquare(N);

    for(Natural j = 0; j < N; ++j)
        matrix->elements[j * (N + 1)] = real;

    return matrix;
}

/**
 * @brief Rank-one matrix constructor.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Matrix* 
 */
[[nodiscard]] Matrix *newMatrixRankOne(const Vector *vector0, const Vector *vector1) {
    Matrix *matrix = newMatrix(vector0->N, vector1->N);

    for(Natural j = 0; j < vector0->N; ++j)
        for(Natural k = 0; k < vector1->N; ++k)
            matrix->elements[j * vector1->N + k] = vector0->elements[j] * vector1->elements[k];

    return matrix;
}

/**
 * @brief Matrix destructor.
 * 
 * @param matrix Matrix.
 */
void freeMatrix(Matrix *matrix) {
    free(matrix->elements);
    free(matrix);
}

/**
 * @brief Matrix copy.
 * 
 * @param matrix0 Matrix.
 * @param matrix1 Matrix.
 */
void copyMatrix(Matrix *matrix0, const Matrix *matrix1) {
    #ifndef NDEBUG // Integrity check.
    assert(matrix0->N == matrix1->N);
    assert(matrix0->M == matrix1->M);
    #endif

    for(Natural j = 0; j < matrix0->N * matrix0->M; ++j)
        matrix0->elements[j] = matrix1->elements[j];
}

/**
 * @brief Matrix getter.
 * 
 * @param matrix Matrix.
 * @param n Row index.
 * @param m Column index.
 * @return Real 
 */
Real getMatrixAt(const Matrix *matrix, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < matrix->N);
    assert(m < matrix->M);
    #endif

    return matrix->elements[n * matrix->M + m];
}

/**
 * @brief Matrix setter.
 * 
 * @param matrix Matrix.
 * @param n Row index.
 * @param m Column index.
 * @param real Real.
 */
void setMatrixAt(Matrix *matrix, const Natural n, const Natural m, const Real real) {
    #ifndef NDEBUG // Integrity check.
    assert(n < matrix->N);
    assert(m < matrix->M);
    #endif

    matrix->elements[n * matrix->M + m] = real;
}

/**
 * @brief Matrix output.
 * 
 * @param matrix Matrix.
 */
void printMatrix(const Matrix *matrix) {
    for(Natural j = 0; j < matrix->N; ++j) {
        for(Natural k = 0; k < matrix->M - 1; ++k)
            printf("%.4Lf ", matrix->elements[j * matrix->M + k]);
        
        printf("%.4Lf\n", matrix->elements[(j + 1) * matrix->M - 1]);
    }
}