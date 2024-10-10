/**
 * @file Solvers.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Sparse linear solvers.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_SPARSE_SOLVERS
#define CLAY_SPARSE_SOLVERS

#include "./Operations.h"

// Triangular.

[[nodiscard]] Vector *solveReturnSparseCSRLowerTriangular(const SparseCSR *, const Vector *);
[[nodiscard]] Vector *solveReturnSparseCSRUpperTriangular(const SparseCSR *, const Vector *);

#endif