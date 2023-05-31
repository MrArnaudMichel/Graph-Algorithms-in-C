#include "utils.h"

void generer_permutation(size_t *permutation, size_t n)
{
    for (size_t i = 0; i < n; i++){
        permutation[i] = i;
    }
    for (size_t i = n - 1; i > 0; i--){
        size_t j = rand() % (i + 1);
        size_t tmp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = tmp;
    }
}

void init_aleatoire(double *val, size_t n, double max)
{
    for (size_t i = 0; i < n; i++){
        val[i] = rand() / (double)RAND_MAX * max;
    }
}
