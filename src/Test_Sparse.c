/**
 * @file Test_Sparse.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple sparse testing.
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

int main(int argc, char **argv) {

    Sparse *s0 = newSparse(2, 3);

    setSparseAt(s0, 0, 1, 2.0L);
    setSparseAt(s0, 0, 0, 1.0L);
    setSparseAt(s0, 1, 0, 3.0L);
    setSparseAt(s0, 1, 1, 4.0L);
    setSparseAt(s0, 1, 2, 5.0L);

    SparseCSR *s1 = newSparseCSR(s0);
    SparseCSC *s2 = newSparseCSC(s0);

    Vector *v0 = newVector(3);

    setVectorAt(v0, 0, 1.0L);
    setVectorAt(v0, 1, 2.0L);
    setVectorAt(v0, 2, 3.0L);

    Vector *v1 = mulReturnSparseCSRVector(s1, v0);
    Vector *v2 = mulReturnSparseCSCVector(s2, v0);

    printSparseCSR(s1);
    printSparseCSC(s2);

    printVector(v1);
    printVector(v2);

    freeSparse(s0);

    freeSparseCSR(s1);
    freeSparseCSC(s2);

    freeVector(v0);
    freeVector(v1);
    freeVector(v2);

    return 0;
}