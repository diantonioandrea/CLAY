/**
 * @file Operations.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Matrix operations.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_MATRIX_OPERATIONS
#define CLAY_MATRIX_OPERATIONS

#include "./Matrix.h"

void addMatrixScalar(Matrix *, const Real);
void subMatrixScalar(Matrix *, const Real);
void mulMatrixScalar(Matrix *, const Real);
void divMatrixScalar(Matrix *, const Real);
void divScalarMatrix(Matrix *, const Real);
void addMatrixMatrix(Matrix *, const Matrix *);
void subMatrixMatrix(Matrix *, const Matrix *);

[[nodiscard]] Matrix *addReturnMatrixScalar(const Matrix *, const Real);
[[nodiscard]] Matrix *subReturnMatrixScalar(const Matrix *, const Real);
[[nodiscard]] Matrix *mulReturnMatrixScalar(const Matrix *, const Real);
[[nodiscard]] Matrix *divReturnMatrixScalar(const Matrix *, const Real);
[[nodiscard]] Matrix *divReturnScalarMatrix(const Matrix *, const Real);
[[nodiscard]] Matrix *addReturnMatrixMatrix(const Matrix *, const Matrix *);
[[nodiscard]] Matrix *subReturnMatrixMatrix(const Matrix *, const Matrix *);

[[nodiscard]] Vector *mulReturnMatrixVector(const Matrix *, const Vector *);
[[nodiscard]] Vector *mulReturnVectorMatrix(const Vector *, const Matrix *);
[[nodiscard]] Matrix *mulReturnMatrixMatrix(const Matrix *, const Matrix *);

#endif