/**
 * @file Clay_Sparse_Operations.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Sparse/Operations.h implementation.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

/**
 * @brief Sparse * vector.
 * 
 * @param sparse Sparse matrix.
 * @param vector0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnSparseCSRVector(const SparseCSR *sparse, const Vector *vector0) {
    #ifndef NDEBUG // Integrity check.
    assert(sparse->M == vector0->N);
    #endif

    Vector *vector1 = newVector(sparse->N);

    for(Natural j = 0; j < sparse->N; ++j)
        for(Natural k = sparse->inner[j]; k < sparse->inner[j + 1]; ++k)
            vector1->elements[j] += sparse->elements[k] * vector0->elements[sparse->outer[k]];

    return vector1;
}

/**
 * @brief Vector * sparse.
 * 
 * @param vector0 Vector.
 * @param sparse Sparse matrix.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnVectorSparseCSR(const Vector *vector0, const SparseCSR *sparse) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == sparse->N);
    #endif

    Vector *vector1 = newVector(sparse->M);

    for(Natural j = 0; j < sparse->N; ++j)
        for(Natural k = sparse->inner[j]; k < sparse->inner[j + 1]; ++k)
            vector1->elements[sparse->outer[k]] += vector0->elements[j] * sparse->elements[k];
    
    return vector1;
}

/**
 * @brief Sparse * vector.
 * 
 * @param sparse Sparse matrix.
 * @param vector0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnSparseCSCVector(const SparseCSC *sparse, const Vector *vector0) {
    #ifndef NDEBUG // Integrity check.
    assert(sparse->M == vector0->N);
    #endif

    Vector *vector1 = newVector(sparse->N);

    for(Natural k = 0; k < sparse->M; ++k)
        for(Natural j = sparse->inner[k]; j < sparse->inner[k + 1]; ++j)
            vector1->elements[sparse->outer[j]] += sparse->elements[j] * vector0->elements[k];

    return vector1;
}

/**
 * @brief Vector * sparse.
 * 
 * @param vector0 Vector.
 * @param sparse Sparse matrix.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnVectorSparseCSC(const Vector *vector0, const SparseCSC *sparse) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == sparse->N);
    #endif

    Vector *vector1 = newVector(sparse->M);

    for(Natural k = 0; k < sparse->M; ++k)
        for(Natural j = sparse->inner[k]; j < sparse->inner[k + 1]; ++j)
            vector1->elements[k] += vector0->elements[sparse->outer[j]] * sparse->elements[j];

    return vector1;
}