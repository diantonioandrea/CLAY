/**
 * @file Test_Solvers.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple solvers testing.
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

#include <Clay.h>

int main(int argc, char **argv) {

    Matrix *A = newMatrixSquare(2);

    setMatrixAt(A, 0, 0, 4.0L);
    setMatrixAt(A, 0, 1, 1.0L);
    setMatrixAt(A, 1, 0, 1.0L);
    setMatrixAt(A, 1, 1, 3.0L);

    Matrix *L = newMatrixLUP_L(A);
    Matrix *U = newMatrixLUP_U(A);
    Matrix *P = newMatrixLUP_P(A);

    decomposeLUP(A, L, U, P);

    Vector *b = newVector(2);

    setVectorAt(b, 0, 1.0L);
    setVectorAt(b, 1, 2.0L);

    Vector *x0 = solveReturnLUP(L, U, P, b);
    Vector *x1 = solveReturnGauss(A, b);

    printVector(x0);
    printVector(x1);

    freeMatrix(A);

    freeVector(b);
    freeVector(x0);
    freeVector(x1);

    return 0;
}