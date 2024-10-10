/**
 * @file Clay_Sparse_Solvers.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Sparse/Solvers.h implementation.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

/**
 * @brief Solves Lx = b by forward substitution.
 * 
 * @param L Lower triangular sparse matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnSparseCSRLowerTriangular(const SparseCSR *L, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(L->N == L->M);
    assert(L->N <= b->N);
    #endif

    const Natural N = L->N;

    Vector *x = newVector(N);

    // Forward substitution.

    for(Natural j = 0; j < N; ++j) {
        Real sum = 0.0L;

        for(Natural k = L->inner[j]; k < L->inner[j + 1] - 1; ++k)
            sum += L->elements[k] * x->elements[L->outer[k]];

        x->elements[j] = (b->elements[j] - sum) / L->elements[L->inner[j + 1] - 1];
    }

    return x;
}

/**
 * @brief Solves Ux = b by backward substitution.
 * 
 * @param U Upper triangular sparse matrix.
 * @param b Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *solveReturnSparseCSRUpperTriangular(const SparseCSR *U, const Vector *b) {
    #ifndef NDEBUG // Integrity check.
    assert(U->N == U->M);
    assert(U->N <= b->N);
    #endif

    const Natural N = U->N;

    Vector *x = newVector(N);

    // Backward substitution.

    for(Natural j = N; j > 0; --j) {
        Real sum = 0.0L;

        for(Natural k = U->inner[j - 1] + 1; k < U->inner[j]; ++k)
            sum += U->elements[k] * x->elements[U->outer[k]];

        x->elements[j - 1] = (b->elements[j - 1] - sum) / U->elements[U->inner[j - 1]];
    }

    return x;
}