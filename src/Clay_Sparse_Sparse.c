/**
 * @file Clay_Sparse_Sparse.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief 
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

// Construction.

/**
 * @brief Sparse matrix constructor.
 * 
 * @param N Rows.
 * @param M Columns.
 * @return Sparse* 
 */
[[nodiscard]] Sparse *newSparse(const Natural N, const Natural M) {
    #ifndef NDEBUG // Integrity check.
    assert(N > 0);
    assert(M > 0);
    #endif

    Sparse *sparse = (Sparse *) malloc(sizeof(Sparse));

    sparse->N = N;
    sparse->M = M;
    sparse->S = 0;

    sparse->indices = (Natural *) calloc(sparse->N, sizeof(Natural));
    sparse->elements = (Real *) calloc(sparse->N, sizeof(Real));

    return sparse;
}

/**
 * @brief Sparse matrix CSR constructor.
 * 
 * @param sparse0 Sparse matrix.
 * @return SparseCSR* 
 */
[[nodiscard]] SparseCSR *newSparseCSR(const Sparse *sparse0) {
    SparseCSR *sparse = (SparseCSR *) malloc(sizeof(SparseCSR));

    // [!]

    return sparse;
}

/**
 * @brief Sparse matrix CSC constructor.
 * 
 * @param sparse0 Sparse matrix.
 * @return SparseCSC* 
 */
[[nodiscard]] SparseCSC *newSparseCSC(const Sparse *sparse0) {
    SparseCSC *sparse = (SparseCSC *) malloc(sizeof(SparseCSC));

    // [!]

    return sparse;
}

/**
 * @brief Sparse matrix destructor.
 * 
 * @param sparse 
 */
void freeSparse(Sparse *sparse) {
    free(sparse->indices);
    free(sparse->elements);
    free(sparse);
}

/**
 * @brief Sparse matrix destructor.
 * 
 * @param sparse 
 */
void freeSparseCSR(SparseCSR *sparse) {
    free(sparse->inner);
    free(sparse->outer);
    free(sparse->elements);
    free(sparse);
}

/**
 * @brief Sparse matrix destructor.
 * 
 * @param sparse 
 */
void freeSparseCSC(SparseCSC *sparse) {
    free(sparse->inner);
    free(sparse->outer);
    free(sparse->elements);
    free(sparse);
}

// Access.

/**
 * @brief Sparse matrix finder.
 * 
 * @param sparse Sparse matrix.
 * @param n Row index.
 * @param m Column index.
 * @return Integer 
 */
[[nodiscard]] Integer findSparseAt(const Sparse *sparse, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < sparse->N);
    assert(m < sparse->M);
    #endif

    const Natural target = n * sparse->M + m;
    Integer a = 0, b = sparse->S - 1, c;

    if(sparse->S == 0)
        return -1;
    else if((target < sparse->indices[a]) || (target > sparse->indices[b]))
        return -1;

    do {
        c = (a + b) / 2;
        const Natural index = sparse->indices[c];

        if(index == target)
            return c;
        
        if(index < target)
            a = c + 1;
        else
            b = c - 1;

    } while(a <= b);

    return -1;
}

/**
 * @brief Sparse matrix getter.
 * 
 * @param sparse Sparse matrix.
 * @param n Row index.
 * @param m Column index.
 * @return Real 
 */
Real getSparseAt(const Sparse *sparse, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < sparse->N);
    assert(m < sparse->M);
    #endif

    const Integer s = findSparseAt(sparse, n, m);

    if(s > -1)
        return sparse->elements[s];

    return 0.0L;
}

/**
 * @brief Sparse matrix setter.
 * 
 * @param sparse Sparse matrix.
 * @param n Row index.
 * @param m Column index.
 * @param real Real.
 */
void setSparseAt(Sparse *sparse, const Natural n, const Natural m, const Real real) {
    #ifndef NDEBUG // Integrity check.
    assert(n < sparse->N);
    assert(m < sparse->M);
    #endif

    if(fabs(real) <= TOLERANCE)
        return;

    const Natural target = n * sparse->M + m;
    const Integer s = findSparseAt(sparse, n, m);

    if(s != -1) {
        sparse->elements[s] = real;
        return;
    }

    ++sparse->S;

    sparse->indices = (Natural *) realloc(sparse->indices, sparse->S * sizeof(Natural));
    sparse->elements = (Real *) realloc(sparse->elements, sparse->S * sizeof(Real));

    Natural k = sparse->S - 1;

    for(; (sparse->indices[k - 1] > target) && (k > 0); --k) {
        sparse->indices[k] = sparse->indices[k - 1];
        sparse->elements[k] = sparse->elements[k - 1];
    }

    sparse->indices[k] = target;
    sparse->elements[k] = real;
}

/**
 * @brief Sparse matrix deleter.
 * 
 * @param sparse Sparse matrix.
 * @param n Row index.
 * @param m Column index.
 */
void delSparseAt(Sparse *sparse, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < sparse->N);
    assert(m < sparse->M);
    #endif

    if(sparse->S == 0)
        return;

    const Integer s = findSparseAt(sparse, n, m);

    if(s == -1)
        return;

    --sparse->S;

    for(Natural k = s; k < sparse->S; ++k) {
        sparse->indices[k] = sparse->indices[k + 1];
        sparse->elements[k] = sparse->elements[k + 1];
    }
}

/**
 * @brief Sparse matrix getter.
 * 
 * @param sparse Sparse matrix.
 * @param n Row index.
 * @param m Column index.
 * @return Real 
 */
Real getSparseCSRAt(const SparseCSR *sparse, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < sparse->N);
    assert(m < sparse->M);
    #endif

    // [!]

    return 0.0L;
}

/**
 * @brief Sparse matrix getter.
 * 
 * @param sparse Sparse matrix.
 * @param n Row index.
 * @param m Column index.
 * @return Real 
 */
Real getSparseCSCAt(const SparseCSC *sparse, const Natural n, const Natural m) {
    #ifndef NDEBUG // Integrity check.
    assert(n < sparse->N);
    assert(m < sparse->M);
    #endif

    // [!]

    return 0.0L;
}

// Output.

/**
 * @brief Sparse matrix output.
 * 
 * @param sparse Sparse matrix.
 */
void printSparse(const Sparse *sparse) {
    for(Natural i = 0; i < sparse->S; ++i) {
        const Natural j = sparse->indices[i] / sparse->M;
        const Natural k = sparse->indices[i] % sparse->N;

        printf("%zu. (%zu, %zu): %.4Lf\n", i, j, k, sparse->elements[i]);
    }
}

/**
 * @brief Sparse matrix output.
 * 
 * @param sparse Sparse matrix.
 */
void printSparseCSR(const SparseCSR *sparse) {

}

/**
 * @brief Sparse matrix output.
 * 
 * @param sparse Sparse matrix.
 */
void printSparseCSC(const SparseCSC *sparse) {

}