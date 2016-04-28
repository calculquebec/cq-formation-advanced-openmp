#include <stdio.h>
#include <stdlib.h>


void please_fill(double *array, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++) {
        array[i] = rand();
    }
}


int main(int argc, char ** argv)
{
    const size_t N = 44100;
    size_t i;
    double *input = (double*)malloc(N * sizeof(double));
    double *output = (double*)malloc(N * sizeof(double));

    srand(0);
    please_fill(input, N);

#pragma omp simd
    for (i = 0; i < N; i++) {
        if (i == 0) {
            output[i] = (               2 * input[i] + input[i + 1]) / 3;
        }
        else if (i < N - 1) {
            output[i] = (input[i - 1] + 2 * input[i] + input[i + 1]) / 4;
        }
        else {
            output[i] = (input[i - 1] + 2 * input[i]               ) / 3;
        }
    }

    printf("%5d: %f -> %f\n", 0, input[0], output[0]);
    for (i = 1; i < N; i *= 2) {
        printf("%5d: %f -> %f\n", i, input[i], output[i]);
    }
    printf("%5d: %f -> %f\n", N - 1, input[N - 1], output[N - 1]);

    free(input);
    free(output);

    return 0;
}
