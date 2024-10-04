/**
 * @file Test_LUP.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple LUP testing.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

int main(int argc, char **argv) {

    Matrix *A = newMatrixSquare(3);

    setMatrixAt(A, 0, 0, 0.0L);
    setMatrixAt(A, 0, 1, 5.0L);
    setMatrixAt(A, 0, 2, 22.0L / 3.0L);
    setMatrixAt(A, 1, 0, 4.0L);
    setMatrixAt(A, 1, 1, 2.0L);
    setMatrixAt(A, 1, 2, 1.0L);
    setMatrixAt(A, 2, 0, 2.0L);
    setMatrixAt(A, 2, 1, 7.0L);
    setMatrixAt(A, 2, 2, 9.0L);

    Matrix *L = newMatrixLUP_L(A);
    Matrix *U = newMatrixLUP_U(A);
    Matrix *P = newMatrixLUP_P(A);

    decomposeLUP(A, L, U, P);

    Matrix *LU = mulReturnMatrixMatrix(L, U);
    Matrix *PA = mulReturnMatrixMatrix(P, A);

    printf("LU.\n");
    printMatrix(LU);

    printf("\nPA.\n");
    printMatrix(PA);

    freeMatrix(A);
    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(P);

    return 0;
}