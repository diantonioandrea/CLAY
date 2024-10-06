/**
 * @file Base.h
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Base header.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLAY_BASE_BASE
#define CLAY_BASE_BASE

#include "./Includes.h"

// Types.
typedef size_t Natural;
typedef ptrdiff_t Integer;
typedef long double Real;

// Constants.

// Tolerance.
#ifndef TOLERANCE
#define TOLERANCE 1E-14
#endif

// Iterative methods.

// QR algorithm.
#ifndef QR_ITER_MAX
#define QR_ITER_MAX 256
#endif

#endif