#include <stdio.h>
#include <omp.h>

#define M 640
#define N 800

double x[N][N][M];

int main(void)
{
    int i, j, k;
    double t1, t2, scale;

#pragma omp parallel default(none) private(i,j,k) shared(x)
    for( k = 1; k < N; k++)
       for( j = 1; j < N; j++)
#pragma omp for
	  for( i = 0; i < M; i++)
             x[k][j][i] = 1.0;

    t1 = omp_get_wtime();
    scale = 2.0;

#pragma omp parallel default(none) private(i,j,k) shared(x,scale)
    for( k = 1; k < N; k++)
       for( j = 1; j < N; j++)
#pragma omp for
	  for( i = 0; i < M; i++)
             x[k][j][i] = x[k-1][j][i] + x[k][j-1][i]*scale;

    t2 = omp_get_wtime();

    printf("%s %d %s %g\n", "Threads = ",  omp_get_max_threads(), "Blockmatrix Time =", t2 - t1);
    return 0;
}
