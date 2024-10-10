/**
 * @file Test_Sparse_Solvers.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple sparse solvers testing.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

int main(int argc, char **argv) {

    //  System.

    Sparse *A0 = newSparse(2, 2);

    setSparseAt(A0, 0, 0, 4.0L);
    setSparseAt(A0, 0, 1, 1.0L);
    setSparseAt(A0, 1, 1, 3.0L);

    SparseCSR *A1 = newSparseCSR(A0);

    Vector *b = newVector(2);

    setVectorAt(b, 0, 1.0L);
    setVectorAt(b, 1, 2.0L);

    // Solvers.

    Vector *x0 = solveReturnSparseCSRUpperTriangular(A1, b);
    Vector *c0 = mulReturnSparseCSRVector(A1, x0);

    // Output.

    printVector(x0);
    printVector(c0);

    // Memory management.

    freeSparse(A0);
    freeSparseCSR(A1);

    freeVector(b);
    freeVector(x0);
    freeVector(c0);

    return 0;
}