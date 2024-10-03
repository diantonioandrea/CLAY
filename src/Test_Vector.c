/**
 * @file Test_Vector.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple vector testing.
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Clay.h>

int main(int argc, char **argv) {

    Vector *v0 = newVector(3);
    Vector *v1 = newVector(3);

    setVectorAt(v0, 0, 1.0L);
    setVectorAt(v0, 1, 2.0L);
    setVectorAt(v0, 2, 3.0L);

    setVectorAt(v1, 0, 4.0L);
    setVectorAt(v1, 1, 5.0L);
    setVectorAt(v1, 2, 6.0L);

    printVector(v0);
    printVector(v1);

    addVectorScalar(v0, 1.0L);
    addVectorVector(v1, v0);

    printVector(v0);
    printVector(v1);

    freeVector(v0);
    freeVector(v1);

    return 0;
}