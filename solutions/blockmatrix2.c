#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 640
#define N 800

int main(void)
{
    double t1, t2, scale;

    scale = 2.0;

#pragma omp parallel default(none) shared(scale,t1)
    {
      int i, j, k;
      int tid = omp_get_thread_num();
      int tot = omp_get_num_threads();
      int mlocal = (tid+1)*M/tot-tid*M/tot;
      double x[N][N][mlocal];

      for( k = 1; k < N; k++)
	for( j = 1; j < N; j++)
	  for( i = 0; i < mlocal; i++)
             x[k][j][i] = 1.0;

#pragma omp barrier
#pragma omp master
      t1 = omp_get_wtime();

      for( k = 1; k < N; k++)
	for( j = 1; j < N; j++)
	  for( i = 0; i < mlocal; i++)
             x[k][j][i] = x[k-1][j][i] + x[k][j-1][i]*scale;
    }

    t2 = omp_get_wtime();

    printf("%s %d %s %g\n", "Threads = ",  omp_get_max_threads(), "Blockmatrix Time =", t2 - t1);
    return 0;
}
