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
 */
void addVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j)
        vector->elements[j] += real;
}

/**
 * @brief Vector - real.
 * 
 * @param vector Vector.
 * @param real Real.
 */
void subVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j)
        vector->elements[j] -= real;
}

/**
 * * @brief Vector * real.
 * 
 * @param vector Vector.
 * @param real Real.
 */
void mulVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j)
        vector->elements[j] *= real;
}

/**
 * @brief Vector / real.
 * 
 * @param vector Vector.
 * @param real Real.
 */
void divVectorScalar(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j) // No checks.
        vector->elements[j] /= real;
}

/**
 * @brief Real / vector.
 * 
 * @param vector Vector.
 * @param real Real.
 */
void divScalarVector(Vector *vector, const Real real) {
    for(Natural j = 0; j < vector->N; ++j) // No checks.
        vector->elements[j] = real / vector->elements[j];
}

/**
 * @brief Vector + vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 */
void addVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] += vector1->elements[j];
}

/**
 * @brief Vector - vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 */
void subVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] -= vector1->elements[j];
}

/**
 * @brief Vector * vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 */
void mulVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j)
        vector0->elements[j] *= vector1->elements[j];
}

/**
 * @brief Vector / vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 */
void divVectorVector(Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    for(Natural j = 0; j < vector0->N; ++j) // No checks.
        vector0->elements[j] /= vector1->elements[j];
}

/**
 * @brief Vector + real.
 * 
 * @param vector0 Vector.
 * @param real Real.
 * @return Vector* 
 */
[[nodiscard]] Vector *addReturnVectorScalar(const Vector *vector0, const Real real) {
    Vector *vector1 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector1->elements[j] = vector0->elements[j] + real;

    return vector1;
}

/**
 * @brief Vector - real.
 * 
 * @param vector0 Vector.
 * @param real Real.
 * @return Vector* 
 */
[[nodiscard]] Vector *subReturnVectorScalar(const Vector *vector0, const Real real) {
    Vector *vector1 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector1->elements[j] = vector0->elements[j] - real;

    return vector1;
}

/**
 * @brief Vector * real.
 * 
 * @param vector0 Vector.
 * @param real Real.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnVectorScalar(const Vector *vector0, const Real real) {
    Vector *vector1 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector1->elements[j] = vector0->elements[j] * real;

    return vector1;
}

/**
 * @brief Vector / real.
 * 
 * @param vector0 Vector.
 * @param real Real.
 * @return Vector* 
 */
[[nodiscard]] Vector *divReturnVectorScalar(const Vector *vector0, const Real real) {
    Vector *vector1 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector1->elements[j] = vector0->elements[j] / real;

    return vector1;
}

/**
 * @brief Real / vector.
 * 
 * @param vector0 Vector.
 * @param real Real.
 * @return Vector* 
 */
[[nodiscard]] Vector *divReturnScalarVector(const Vector *vector0, const Real real) {
    Vector *vector1 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector1->elements[j] = real / vector0->elements[j];

    return vector1;
}

/**
 * @brief Vector + vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *addReturnVectorVector(const Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    Vector *vector2 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector2->elements[j] = vector0->elements[j] + vector1->elements[j];

    return vector2;
}

/**
 * @brief Vector - vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *subReturnVectorVector(const Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    Vector *vector2 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector2->elements[j] = vector0->elements[j] - vector1->elements[j];

    return vector2;
}

/**
 * @brief Vector * vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *mulReturnVectorVector(const Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    Vector *vector2 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector2->elements[j] = vector0->elements[j] * vector1->elements[j];

    return vector2;
}

/**
 * @brief Vector / vector.
 * 
 * @param vector0 Vector.
 * @param vector1 Vector.
 * @return Vector* 
 */
[[nodiscard]] Vector *divReturnVectorVector(const Vector *vector0, const Vector *vector1) {
    #ifndef NDEBUG // Integrity check.
    assert(vector0->N == vector1->N);
    #endif

    Vector *vector2 = newVector(vector0->N);

    for(Natural j = 0; j < vector0->N; ++j)
        vector2->elements[j] = vector0->elements[j] / vector1->elements[j];

    return vector2;
}