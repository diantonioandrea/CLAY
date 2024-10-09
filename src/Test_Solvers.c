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

    Matrix *A = newMatrixSquare(2);

    setMatrixAt(A, 0, 0, 4.0L);
    setMatrixAt(A, 0, 1, 1.0L);
    setMatrixAt(A, 1, 0, 1.0L);
    setMatrixAt(A, 1, 1, 3.0L);

    // LU.

    Matrix *L = newMatrixLUP_L(A);
    Matrix *U = newMatrixLUP_U(A);
    Matrix *P = newMatrixLUP_P(A);

    decomposeLUP(A, L, U, P);

    // In-place LU.

    Matrix *LU = newMatrixCopy(A);
    Matrix *HP = newMatrixLUP_P(A);

    decomposeHereLUP(LU, HP);

    // QR.

    Matrix *Q = newMatrixHessenbergQR_Q(A);
    Matrix *R = newMatrixHessenbergQR_R(A);

    decomposeHessenbergQR(A, Q, R);

    // Cholesky.

    Matrix *C = newMatrixLL_L(A);

    decomposeLL(A, C);

    // RHS.

    Vector *b = newVector(2);

    setVectorAt(b, 0, 1.0L);
    setVectorAt(b, 1, 2.0L);

    // Solvers.

    Vector *x0 = solveReturnGauss(A, b);
    Vector *x1 = solveReturnLUP(L, U, P, b);
    Vector *x2 = solveReturnLUP(L, U, P, b);
    Vector *x3 = solveReturnQR(Q, R, b);
    Vector *x4 = solveReturnLL(C, b);

    printVector(x0);
    printVector(x1);
    printVector(x2);
    printVector(x3);
    printVector(x4);

    freeMatrix(A);

    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(P);

    freeMatrix(LU);
    freeMatrix(HP);

    freeMatrix(Q);
    freeMatrix(R);

    freeMatrix(C);

    freeVector(b);
    freeVector(x0);
    freeVector(x1);
    freeVector(x2);
    freeVector(x3);

    return 0;
}