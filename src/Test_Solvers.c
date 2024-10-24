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

int main(int argc, char **argv) {

    //  System.

    Matrix *A = newMatrixSquare(2);

    setMatrixAt(A, 0, 0, 4.0L);
    setMatrixAt(A, 0, 1, 1.0L);
    setMatrixAt(A, 1, 0, 1.0L);
    setMatrixAt(A, 1, 1, 3.0L);

    Vector *b = newVector(2);

    setVectorAt(b, 0, 1.0L);
    setVectorAt(b, 1, 2.0L);

    // LU.

    Matrix *LU = newMatrixCopy(A);
    Matrix *P = newMatrixLUP_P(A);

    decomposeLUP(LU, P);

    // QR.

    Matrix *Q = newMatrixHessenbergQR_Q(A);
    Matrix *R = newMatrixCopy(A);

    decomposeQR(Q, R);

    // Cholesky.

    Matrix *L = newMatrixCopy(A);

    decomposeLL(L);

    // Solvers.

    Vector *x0 = solveReturnGauss(A, b);
    Vector *x1 = solveReturnLUP(LU, P, b);
    Vector *x2 = solveReturnQR(Q, R, b);
    Vector *x3 = solveReturnLL(L, b);

    // Output.

    printVector(x0);
    printVector(x1);
    printVector(x2);
    printVector(x3);

    // Memory management.

    freeMatrix(A);

    freeMatrix(LU);
    freeMatrix(P);

    freeMatrix(Q);
    freeMatrix(R);

    freeMatrix(L);

    freeVector(b);
    freeVector(x0);
    freeVector(x1);
    freeVector(x2);
    freeVector(x3);

    return 0;
}