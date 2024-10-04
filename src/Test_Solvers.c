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
    setMatrixAt(A, 0, 1, 6.0L);
    setMatrixAt(A, 1, 0, 6.0L);
    setMatrixAt(A, 1, 1, 3.0L);

    Matrix *L = newMatrixLUP_L(A);
    Matrix *U = newMatrixLUP_U(A);
    Matrix *P = newMatrixLUP_P(A);

    decomposeLUP(A, L, U, P);

    Matrix *Q = newMatrixQR_Q(A);
    Matrix *R = newMatrixQR_R(A);

    decomposeQR(A, Q, R);

    Vector *b = newVector(2);

    setVectorAt(b, 0, 1.0L);
    setVectorAt(b, 1, 2.0L);

    Vector *x0 = solveReturnGauss(A, b);
    Vector *x1 = solveReturnLUP(L, U, P, b);
    Vector *x2 = solveReturnQR(Q, R, b);

    printVector(x0);
    printVector(x1);
    printVector(x2);

    freeMatrix(A);

    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(P);

    freeMatrix(Q);
    freeMatrix(R);

    freeVector(b);
    freeVector(x0);
    freeVector(x1);
    freeVector(x2);

    return 0;
}