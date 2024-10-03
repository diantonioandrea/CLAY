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

    setMatrixAt(m0, 0, 0, 1.0L);
    setMatrixAt(m0, 0, 1, 2.0L);
    setMatrixAt(m0, 1, 0, 3.0L);
    setMatrixAt(m0, 1, 1, 4.0L);

    printMatrix(m0);

    freeMatrix(m0);

    return 0;
}