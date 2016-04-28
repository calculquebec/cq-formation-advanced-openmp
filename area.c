#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> 
#include <complex.h>

# define NPOINTS 2000
# define MAXITER 2000


int main(){
  int i, j, iter, numoutside = 0;
  double area, error, tstart, tend;
  complex z, c;

/*
 *   
 *
 *     Outer loops run over npoints, initialise z=c
 *
 *     Inner loop has the iteration z=z*z+c, and threshold test
 */

  tstart = omp_get_wtime();

  for (i=0; i<NPOINTS; i++) {
    for (j=0; j<NPOINTS; j++) {
      c = -2.0+2.5*i/NPOINTS+1.0e-7 + I*(1.125*j/NPOINTS+1.0e-7);
      z = c;
      for (iter=0; iter<MAXITER; iter++){
        z = z*z + c;
	if ((creal(z)*creal(z)+cimag(z)*cimag(z))>4.0) {
	  numoutside++; 
	  break;
	}
      }
    }
  }

  tend = omp_get_wtime();

/*
 *  Calculate area and error and output the results
 */

      area=2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
      error=area/(double)NPOINTS;

      printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
      printf("numoutside = %d \n", numoutside);
      printf("Time =  %12.8f seconds using %d threads\n",tend - tstart, omp_get_max_threads());

  return 0;

  }
