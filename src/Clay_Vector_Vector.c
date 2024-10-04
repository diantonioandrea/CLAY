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
 * @brief Vector copy constructor.
 * 
 * @param vector0 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *newVectorCopy(const Vector *vector0) {
    Vector *vector1 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector1->elements[j] = vector0->elements[j];

    return vector1;
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
 * @brief Vector copy.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 */
void copyVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] = vector1->elements[j];
}

/**
 * @brief Vector getter.
 * 
 * @param vector Vector.
 * @param n Index.
 * @return Real Real.
 */
Real getVectorAt(const Vector *vector, const Natural n) {
    #ifndef NDEBUG // Integrity check.
    assert(n < vector->N);
    #endif

    return vector->elements[n];
}

/**
 * @brief Vector setter.
 * 
 * @param vector Vector.
 * @param n Index.
 * @param real Real.
 */
void setVectorAt(Vector *vector, const Natural n, const Real real) {
    #ifndef NDEBUG // Integrity check.
    assert(n < vector->N);
    #endif
    
    vector->elements[n] = real;
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