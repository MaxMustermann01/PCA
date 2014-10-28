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

#include <stdio.h>
#include <stdlib.h>

//Definition of function
double f(double x)
{
	return 4 / (1 + x*x);
}

// Approximation of Pi via Summing n Rectangles
double approximatePi(double n)
{
	//Initializing Variables
	double sum = 0; 
	int j;

	//Width of a Rectangle
	double deltaX = 1.0/n;
	//Current position
	double xi = 0;

	for(j=0; j<=n; ++j)
	{
		sum += f(xi)*deltaX;
		xi += deltaX;
	}
	return sum;
}

int main(int argc, char *argv[])
{
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
