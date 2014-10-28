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
#include "time_measurement.h"
#include <unistd.h>

/* Approximates Pi with a given number of steps */
int main(int argc, char *argv[])
{
	/* Check Argument count */
	if(argc == 2)
	{
		int n = atoi(argv[1]);
		double approxPi = 0;
		double dStartTimeGTOD=0.0, dElapsedTimeGTOD=0.0;
		unsigned long long ullStartTimeRDTSC=0.0;
		double dElapsedTimeRDTSC=0.0;

		/* Open a File for storing time-measurment-values */
		FILE * f = OpenTimeFile();

		/* Start time-measurement */
  		dStartTimeGTOD = dstartMesGTOD();
  		ullStartTimeRDTSC = ullstartMesRDTSC();	

		/* Start Approximation */	
		approxPi = approximatePi(n);

		/* Stop time-measurement */
		dElapsedTimeGTOD = dstopMesGTOD(dStartTimeGTOD);
  		dElapsedTimeRDTSC = dstopMesRDTSC(ullStartTimeRDTSC);

		/* Write reslulting values in file */
 		writeTimeToFile(f,0,dElapsedTimeGTOD);
		writeTimeToFile(f,1,dElapsedTimeRDTSC);

		/* Display value of Approximation */
		printf("Approximation of Pi is:%f \n", approxPi);
		return 0;
	}
	else
	{
		printf("Wrong number of arguments\n");
		return EXIT_FAILURE;
	}



}
