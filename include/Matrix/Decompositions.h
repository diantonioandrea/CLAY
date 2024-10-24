/**
 * @file Decompositions.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Matrix decompositions.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_MATRIX_DECOMPOSITIONS
#define CLAY_MATRIX_DECOMPOSITIONS

#include "./Operations.h"

// LUP.

Matrix *newMatrixLUP_P(const Matrix *);

void decomposeLUP(Matrix *, Matrix *);

// QR.

Matrix *newMatrixQR_Q(const Matrix *);
Matrix *newMatrixHessenbergQR_Q(const Matrix *);

Matrix *newMatrixHouseholder(const Vector *);

void decomposeQR(Matrix *, Matrix *);
void decomposeHessenbergQR(Matrix *, Matrix *);

// Cholesky.

void decomposeLL(Matrix *);

#endif