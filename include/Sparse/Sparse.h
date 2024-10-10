/**
 * @file Sparse.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Sparse matrices
 * @date 2024-10-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_SPARSE_SPARSE
#define CLAY_SPARSE_SPARSE

#include "../Matrix.h"

typedef struct {
    
    /**
     * @brief Sparse's rows.
     * 
     */
    Natural N;

    /**
     * @brief Sparse's columns.
     * 
     */
    Natural M;

    /**
     * @brief Sparse's size.
     * 
     */
    Natural S;

    /**
     * @brief Sparse's indices.
     * 
     */
    Natural *indices;

    /**
     * @brief Sparse's elements.
     * 
     */
    Real *elements;

} Sparse;

typedef struct {

    /**
     * @brief Sparse's rows.
     * 
     */
    Natural N;

    /**
     * @brief Sparse's columns.
     * 
     */
    Natural M;

    /**
     * @brief Sparse's inner indices.
     * 
     */
    Natural *inner;

    /**
     * @brief Sparse's outer indices.
     * 
     */
    Natural *outer;

    /**
     * @brief Sparse's elements.
     * 
     */
    Real *elements;

} SparseCSR;

typedef struct {

    /**
     * @brief Sparse's rows.
     * 
     */
    Natural N;

    /**
     * @brief Sparse's columns.
     * 
     */
    Natural M;

    /**
     * @brief Sparse's inner indices.
     * 
     */
    Natural *inner;

    /**
     * @brief Sparse's outer indices.
     * 
     */
    Natural *outer;

    /**
     * @brief Sparse's elements.
     * 
     */
    Real *elements;

} SparseCSC;

// Construction.

[[nodiscard]] Sparse *newSparse(const Natural, const Natural);
[[nodiscard]] SparseCSR *newSparseCSR(const Sparse *);
[[nodiscard]] SparseCSC *newSparseCSC(const Sparse *);

void freeSparse(Sparse *);
void freeSparseCSR(SparseCSR *);
void freeSparseCSC(SparseCSC *);

// Access.

[[nodiscard]] Integer findSparseAt(const Sparse *, const Natural, const Natural);
Real getSparseAt(const Sparse *, const Natural, const Natural);
void setSparseAt(Sparse *, const Natural, const Natural, const Real);
void delSparseAt(Sparse *, const Natural, const Natural);

Real getSparseCSRAt(const SparseCSR *, const Natural, const Natural);
Real getSparseCSCAt(const SparseCSC *, const Natural, const Natural);

// Output.

void printSparse(const Sparse *);
void printSparseCSR(const SparseCSR *);
void printSparseCSC(const SparseCSC *);

#endif