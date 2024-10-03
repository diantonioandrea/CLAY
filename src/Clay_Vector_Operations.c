/**
 * @file Clay_Vector_Operations.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief include/Vector/Operations.h implementation.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

/**
 * @brief Vector + real.
 * 
 * @param vector Vector.
 * @param real Real.
 * @return Vector* 
 */
Vector *addVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j)
        vector->elements[j] += real;

    return vector;
}

/**
 * @brief Vector - real.
 * 
 * @param vector Vector.
 * @param real Real.
 * @return Vector* 
 */
Vector *subVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j)
        vector->elements[j] -= real;

    return vector;
}

/**
 * * @brief Vector * real.
 * 
 * @param vector Vector.
 * @param real Real.
 * @return Vector* 
 */
Vector *mulVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j)
        vector->elements[j] *= real;

    return vector;
}

/**
 * @brief Vector / real.
 * 
 * @param vector Vector.
 * @param real Real.
 * @return Vector* 
 */
Vector *divVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j) // No checks.
        vector->elements[j] /= real;

    return vector;
}

/**
 * @brief Real / vector.
 * 
 * @param vector Vector.
 * @param real Real.
 * @return Vector* 
 */
Vector *divScalarVector(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j) // No checks.
        vector->elements[j] = real / vector->elements[j];

    return vector;
}

/**
 * @brief Vector + vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
Vector *addVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] += vector1->elements[j];

    return vector0;
}

/**
 * @brief Vector - vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
Vector *subVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] -= vector1->elements[j];

    return vector0;
}

/**
 * @brief Vector * vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
Vector *mulVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] *= vector1->elements[j];

    return vector0;
}

/**
 * @brief Vector / vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
Vector *divVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j) // No checks.
        vector0->elements[j] /= vector1->elements[j];

    return vector0;
}