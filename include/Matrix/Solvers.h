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

[[nodiscard]] Vector *solveReturnLUP(const Matrix *, const Vector *);

#endif