/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 1 - main function
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      28. OKT 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ApproximationOfPi.h"
#include <omp.h>
#include <unistd.h>

/* Approximates Pi with a given number of steps */
int main(int argc, char *argv[])
{
	/* Check Argument count */
	if(argc == 2)
	{
		int n = atoi(argv[1]);
		double dApproxPiSer = 0.0;
		double dApproxPiPar = 0.0;
		double dSerTime = 0.0;
		double dParTime = 0.0;

		// Start Approximation and measure time	
		dSerTime = omp_get_wtime();
		dApproxPiSer = approximatePiSer(n);
		dSerTime = omp_get_wtime() - dSerTime;
		
		dParTime = omp_get_wtime();
		dApproxPiPar = approximatePiPar(n);
		dParTime = omp_get_wtime() - dParTime;
		
		/* Display value of Approximation */
		printf("\n%d Iterations done: \n", n);
		printf("Serial  : Approximated Pi to %f in %fs \n", dApproxPiSer, dSerTime);
		printf("Parallel: Approximated Pi to %f in %fs \n \n", dApproxPiPar, dParTime);
		return 0;
	}
	else
	{
		printf("Wrong number of arguments\n");
		return EXIT_FAILURE;
	}



}
