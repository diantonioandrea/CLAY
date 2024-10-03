/**
 * @file Operations.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Vector operations.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_VECTOR_OPERATIONS
#define CLAY_VECTOR_OPERATIONS

#include "./Vector.h"

Vector *addVectorScalar(Vector *, const Real);
Vector *subVectorScalar(Vector *, const Real);
Vector *mulVectorScalar(Vector *, const Real);
Vector *divVectorScalar(Vector *, const Real);
Vector *divScalarVector(Vector *, const Real);
Vector *addVectorVector(Vector *, const Vector *);
Vector *subVectorVector(Vector *, const Vector *);
Vector *mulVectorVector(Vector *, const Vector *);
Vector *divVectorVector(Vector *, const Vector *);

#endif