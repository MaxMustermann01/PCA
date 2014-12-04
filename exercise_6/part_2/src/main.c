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
#include <unistd.h>

/* Approximates Pi with a given number of steps */
int main(int argc, char *argv[])
{
	/* Check Argument count */
	if(argc == 2)
	{
		int n = atoi(argv[1]);
		double approxPiSer = 0;
		double approxPiPar = 0;

		/* Start Approximation */	
		approxPiSer = approximatePiSer(n);
		approxPiPar = approximatePiPar(n);

		
		/* Display value of Approximation */
		printf("\nSerial Calculation: Approximation of Pi is: %f \n", approxPiSer);
		printf("Parallel Calculation: Approximation of Pi is: %f \n", approxPiPar);
		return 0;
	}
	else
	{
		printf("Wrong number of arguments\n");
		return EXIT_FAILURE;
	}



}
