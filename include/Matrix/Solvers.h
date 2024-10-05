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

[[nodiscard]] Vector *solveReturnGauss(const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnLUP(const Matrix *, const Matrix *, const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnQR(const Matrix *, const Matrix *, const Vector *);
[[nodiscard]] Vector *solveReturnLL(const Matrix *, const Vector *);

#endif