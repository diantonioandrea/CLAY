/**
 * @file Vector.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Dynamically allocated vectors.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_VECTOR_VECTOR
#define CLAY_VECTOR_VECTOR

#include "./Includes.h"

typedef struct {

    /**
     * @brief Vector's size.
     * 
     */
    Natural N;

    /**
     * @brief Vector's elements.
     * 
     */
    Real *elements;

} Vector;

// Construction.

Vector *newVector(const Natural);
void freeVector(Vector *);

// Access.

Real getVectorAt(const Vector *, const Natural);
void setVectorAt(Vector *, const Natural, const Real);

// Output.

void printVector(const Vector *);

#endif