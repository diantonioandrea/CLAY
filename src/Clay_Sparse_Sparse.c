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

    sparse->N = sparse0->N;
    sparse->M = sparse0->M;

    sparse->inner = (Natural *) malloc((sparse->N + 1) * sizeof(Natural));
    sparse->outer = (Natural *) malloc(sparse0->S * sizeof(Natural));
    sparse->elements = (Real *) malloc(sparse0->S * sizeof(Real));

    Natural index = 0;

    for(Natural j = 1; j <= sparse->N; ++j) {
        for(; (sparse0->indices[index] < j * sparse->M) && (index < sparse0->S); ++index) {
            sparse->outer[index] = sparse0->indices[index] % sparse->M;
            sparse->elements[index] = sparse0->elements[index];
        }

        sparse->inner[j] = index;
    }

    sparse->inner[0] = 0;
    sparse->inner[sparse->N] = sparse0->S;

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

    sparse->N = sparse0->N;
    sparse->M = sparse0->M;

    sparse->inner = (Natural *) calloc(sparse0->M + 1, sizeof(Natural));
    sparse->outer = (Natural *) calloc(sparse0->S, sizeof(Natural));
    sparse->elements = (Real *) calloc(sparse0->S, sizeof(Real));

    Natural index = 0;

    for(Natural k = 1; k <= sparse->M; ++k) {
        for(Natural h = 0; h < sparse0->S; ++h)
            if(sparse0->indices[h] % sparse->M == k - 1) {
                sparse->outer[index] = sparse0->indices[h] / sparse->M;
                sparse->elements[index] = sparse0->elements[h];
                ++index;
            }

        sparse->inner[k] = index;
    }

    sparse->inner[0] = 0;
    sparse->inner[sparse->M] = sparse0->S;

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
Integer findSparseAt(const Sparse *sparse, const Natural n, const Natural m) {
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

    for(Natural k = sparse->inner[n]; k < sparse->inner[n + 1]; ++k)
        if(sparse->outer[k] == m)
            return sparse->elements[k];

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

    for(Natural j = sparse->inner[m]; j < sparse->inner[m + 1]; ++j)
        if(sparse->outer[j] == n)
            return sparse->elements[j];

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
        const Natural k = sparse->indices[i] % sparse->M;

        printf("(%zu, %zu): %.4Lf\n", j, k, sparse->elements[i]);
    }
}

/**
 * @brief Sparse matrix output.
 * 
 * @param sparse Sparse matrix.
 */
void printSparseCSR(const SparseCSR *sparse) {
    for(Natural j = 0; j < sparse->N; ++j)
        for(Natural k = sparse->inner[j]; k < sparse->inner[j + 1]; ++k)
            printf("(%zu, %zu): %.4Lf\n", j, sparse->outer[k], sparse->elements[k]);
}

/**
 * @brief Sparse matrix output.
 * 
 * @param sparse Sparse matrix.
 */
void printSparseCSC(const SparseCSC *sparse) {
    for(Natural k = 0; k < sparse->M; ++k)
        for(Natural j = sparse->inner[k]; j < sparse->inner[k + 1]; ++j)
            printf("(%zu, %zu): %.4Lf\n", sparse->outer[j], k, sparse->elements[j]);
}