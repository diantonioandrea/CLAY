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
            printf("%.2Lf ", matrix->elements[j * matrix->M + k]);
        
        printf("%.2Lf\n", matrix->elements[(j + 1) * matrix->M - 1]);
    }
}