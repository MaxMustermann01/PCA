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

/* Approximates Pi with a given number of steps */
int main(int argc, char *argv[])
{
	/* Check Argument count */
	if(argc == 2)
	{
		int n = atoi(argv[1]);
		printf("Approximation of Pi is:%f \n", approximatePi(n));
		return 0;
	}
	else
	{
		printf("Wrong number of arguments\n");
		return EXIT_FAILURE;
	}

}
