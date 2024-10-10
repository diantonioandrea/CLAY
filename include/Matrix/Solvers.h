/**
 * @file Solvers.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Linear solvers.
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_MATRIX_SOLVERS
#define CLAY_MATRIX_SOLVERS

#include "./Decompositions.h"

// Triangular.

[[nodiscard]] Vector *solveReturnLowerTriangular(const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnUpperTriangular(const Matrix *, const Vector *);

[[nodiscard]] Vector *solveReturnReducedLowerTriangular(const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnReducedUpperTriangular(const Matrix *, const Vector *);

[[nodiscard]] Vector *solveReturnTransposeLowerTriangular(const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnTransposeUpperTriangular(const Matrix *, const Vector *);

// Gauss.

[[nodiscard]] Vector *solveReturnGauss(const Matrix *, const Vector *);

// Decompositions.

[[nodiscard]] Vector *solveReturnLUP(const Matrix *, const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnQR(const Matrix *, const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnLL(const Matrix *, const Vector *);

#endif