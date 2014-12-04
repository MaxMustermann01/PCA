/*********************************************************************************
* FILENAME ApproximationOfPi.c
*
* DESCRIPTION These functions are part of the submission to exercises of
* the Parallel Computer Architecture (PCA) lecture of the
* University of Heidelberg.
*
* Exercise 1 - Implementation for the approximation of Pi via summing up n
* rectangles
*
* AUTHORS Shamna Shyju (shamnashyju@googlemail.com)
* Fabian Finkeldey (Fabian@Finkeldey-hm.de)
* Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
*
* LAST CHANGE 26. OKT 2014
*
********************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "ApproximationOfPi.h"

/* Definition of function */
double f(double x)
{
	return 4 / (1 + x*x);
}

/* 
 * Approximation of Pi via Summing n Rectangles
 * Serial Implementation
*/
double approximatePiSer(int iIterations)
{
  //Initializing Variables
  int i;
  double sum = 0;
  double deltaX = 1.0/(iIterations+1);

	for(i=0; i<=iIterations; i++)
	{
		sum += f(i*deltaX)*deltaX;
	}
	return sum;
}

/* Approximation of Pi via Summing n Rectangles
 * Parallel Implementation 
 */
double approximatePiPar(int iIterations)
{
  // Initializing Variables 
  int i;
  double sum = 0;
  double deltaX = 1.0/(iIterations+1);
  
  
  #pragma omp parallel for reduction(+:sum)
  for(i=0; i<=iIterations; i++)
  {
    sum += (f(i*deltaX)*deltaX);
  }
  return sum;
}
