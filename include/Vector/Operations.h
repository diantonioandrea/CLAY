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

void addVectorScalar(Vector *, const Real);
void subVectorScalar(Vector *, const Real);
void mulVectorScalar(Vector *, const Real);
void divVectorScalar(Vector *, const Real);
void divScalarVector(Vector *, const Real);
void addVectorVector(Vector *, const Vector *);
void subVectorVector(Vector *, const Vector *);
void mulVectorVector(Vector *, const Vector *);
void divVectorVector(Vector *, const Vector *);

[[nodiscard]] Vector *addReturnVectorScalar(const Vector *, const Real);
[[nodiscard]] Vector *subReturnVectorScalar(const Vector *, const Real);
[[nodiscard]] Vector *mulReturnVectorScalar(const Vector *, const Real);
[[nodiscard]] Vector *divReturnVectorScalar(const Vector *, const Real);
[[nodiscard]] Vector *divReturnScalarVector(const Vector *, const Real);
[[nodiscard]] Vector *addReturnVectorVector(const Vector *, const Vector *);
[[nodiscard]] Vector *subReturnVectorVector(const Vector *, const Vector *);
[[nodiscard]] Vector *mulReturnVectorVector(const Vector *, const Vector *);
[[nodiscard]] Vector *divReturnVectorVector(const Vector *, const Vector *);

Real dotReturnVectorVector(const Vector *, const Vector *);

#endif