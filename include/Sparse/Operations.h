/**
 * @file Operations.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Sparse matrix operations.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_SPARSE_OPERATIONS
#define CLAY_SPARSE_OPERATIONS

#include "./Sparse.h"

[[nodiscard]] Vector *mulReturnSparseCSRVector(const SparseCSR *, const Vector *);
[[nodiscard]] Vector *mulReturnVectorSparseCSR(const Vector *, const SparseCSR *);

[[nodiscard]] Vector *mulReturnSparseCSCVector(const SparseCSC *, const Vector *);
[[nodiscard]] Vector *mulReturnVectorSparseCSC(const Vector *, const SparseCSC *);

#endif