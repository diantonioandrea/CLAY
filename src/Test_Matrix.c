/**
 * @file Test_Matrix.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple matrix testing.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

int main(int argc, char **argv) {

    Matrix *m0 = newMatrix(2, 2);
    Matrix *m1 = newMatrix(2, 2);

    Vector *v0 = newVector(2);

    setMatrixAt(m0, 0, 0, 1.0L);
    setMatrixAt(m0, 0, 1, 2.0L);
    setMatrixAt(m0, 1, 0, 3.0L);
    setMatrixAt(m0, 1, 1, 4.0L);

    setMatrixAt(m1, 0, 0, 5.0L);
    setMatrixAt(m1, 0, 1, 6.0L);
    setMatrixAt(m1, 1, 0, 7.0L);
    setMatrixAt(m1, 1, 1, 8.0L);

    setVectorAt(v0, 0, 1.0L);
    setVectorAt(v0, 1, 2.0L);

    Matrix *m2 = mulReturnMatrixMatrix(m0, m1);
    Matrix *m3 = transposeReturnMatrix(m0);

    Vector *v1 = mulReturnMatrixVector(m1, v0);
    Vector *v2 = mulReturnVectorMatrix(v0, m1);

    printMatrix(m0);
    printMatrix(m1);
    printMatrix(m2);
    printMatrix(m3);

    printVector(v1);
    printVector(v2);

    freeMatrix(m0);
    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(m3);

    freeVector(v0);
    freeVector(v1);
    freeVector(v2);

    return 0;
}