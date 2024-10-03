/**
 * @file Matrix.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Dynamically allocated matrices.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_MATRIX_MATRIX
#define CLAY_MATRIX_MATRIX

#include "../Vector/Vector.h"

typedef struct {

    /**
     * @brief Matrix's rows.
     * 
     */
    Natural N;

    /**
     * @brief Matrix's columns.
     * 
     */
    Natural M;

    /**
     * @brief Matrix's elements.
     * 
     */
    Real *elements;

} Matrix;

// Construction.

[[nodiscard]] Matrix *newMatrix(const Natural, const Natural);
[[nodiscard]] Matrix *newMatrixMatrix(const Matrix *);
[[nodiscard]] Matrix *newMatrixSquare(const Natural);
[[nodiscard]] Matrix *newMatrixSquareDiagonal(const Natural, const Real);
void freeMatrix(Matrix *);

// Copy.

void copyMatrix(Matrix *, const Matrix *);

// Access.

Real getMatrixAt(const Matrix *, const Natural, const Natural);
void setMatrixAt(Matrix *, const Natural, const Natural, const Real);

// Output.

void printMatrix(const Matrix *);

#endif