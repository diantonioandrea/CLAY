/**
 * @file Clay_Vector_Vector.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Vector/Vector.h implementation.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

/**
 * @brief Vector constructor.
 * 
 * @param N Size.
 * @return Vector* 
 */
Vector *newVector(const Natural N) {
    #ifndef NDEBUG // Integrity check.
    assert(N > 0);
    #endif

    Vector *vector = (Vector *) malloc(sizeof(Vector));

    vector->N = N;
    vector->elements = (Real *) calloc(N, sizeof(Real));

    return vector;
}

/**
 * @brief Vector destructor.
 * 
 * @param vector 
 */
void freeVector(Vector *vector) {
    free(vector->elements);
    free(vector);
}

/**
 * @brief Vector getter.
 * 
 * @param vector Vector.
 * @param index Index.
 * @return Real Real.
 */
Real getVectorAt(const Vector *vector, const Natural index) {
    #ifndef NDEBUG // Integrity check.
    assert(index < vector->N);
    #endif

    return vector->elements[index];
}

/**
 * @brief Vector setter.
 * 
 * @param vector Vector.
 * @param index Index.
 * @param real Real.
 */
void setVectorAt(Vector *vector, const Natural index, const Real real) {
    #ifndef NDEBUG // Integrity check.
    assert(index < vector->N);
    #endif
    
    vector->elements[index] = real;
}

/**
 * @brief Vector output.
 * 
 * @param vector Vector.
 */
void printVector(const Vector *vector) {
    for(Natural j = 0; j < vector->N - 1; ++j)
        printf("%.2Lf ", vector->elements[j]);

    printf("%.2Lf\n", vector->elements[vector->N - 1]);
}