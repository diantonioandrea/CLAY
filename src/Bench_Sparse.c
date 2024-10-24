/**
 * @file Bench_Sparse.c
 * @author Andrea Di Antonio (github.com/diantonioandrea)
 * @brief Simple sparse benchmarking.
 * @date 2024-10-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <time.h>
#include <stdlib.h>

#include <Clay.h>

int main(int argc, char **argv) {
    
    if(argc != 2) {
        printf("Usage: %s SIZE\n", argv[0]);
        return -1;
    }

    srand(time(NULL));
    Integer N = (Integer) atoi(argv[1]);

    #ifndef NDEBUG // Integrity check.
    assert(N > 0);
    #endif

    clock_t start, stop;

    // Indices.

    Natural *J = (Natural *) malloc(N * sizeof(Natural));
    Natural *K = (Natural *) malloc(N * sizeof(Natural));

    for(Natural t = 1; t < N - 1; ++t) {
        J[t] = rand() % N;
        K[t] = rand() % N;
    }

    // START.

    start = clock();

    Sparse *s0 = newSparse((Natural) N, (Natural) N);

    for(Natural t = 1; t < N - 1; ++t)
        setSparseAt(s0, J[t], K[t], 1.0L);

    stop = clock();

    // STOP.

    Real elapsed = (Real) (stop - start) / CLOCKS_PER_SEC;

    free(J);
    free(K);
    freeSparse(s0);

    printf("Random writing, elapsed time: %.6Lf seconds.\n", elapsed);

    return 0;
}