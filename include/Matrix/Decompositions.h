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

Matrix * newMatrixLUP_L(const Matrix *);
Matrix * newMatrixLUP_U(const Matrix *);
Matrix * newMatrixLUP_P(const Matrix *);

void decomposeLUP(const Matrix *, Matrix *, Matrix *, Matrix *);

// QR.

Matrix * newMatrixQR_Q(const Matrix *);
Matrix * newMatrixQR_R(const Matrix *);

void decomposeQR(const Matrix *, Matrix *, Matrix *);

#endif