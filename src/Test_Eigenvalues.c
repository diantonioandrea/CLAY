/**
 * @file Test_Eigenvalues.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple eigenvalues testing.
 * @date 2024-10-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

int main(int argc, char **argv) {

    Matrix *A = newMatrix(2, 2);

    setMatrixAt(A, 0, 0, 4.0L);
    setMatrixAt(A, 0, 1, 1.0L);
    setMatrixAt(A, 1, 0, 1.0L);
    setMatrixAt(A, 1, 1, 3.0L);

    Vector *e = eigenvaluesReturnQR(A);
    printVector(e);

    freeMatrix(A);
    freeVector(e);

    return 0;
}