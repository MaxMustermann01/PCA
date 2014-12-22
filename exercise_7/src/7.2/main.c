/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 7 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      22. Dez 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "nbody.h"
#include "time_measurement.h"

int main(int argc, char* argv[])
{
  //Starting Parameter
  int iterations = 100;
  int timestep = 100;
  int maxValue = 25000;
  int n, i, j, k, numberOfMassPoints;
  int threadID, numThreads;
  sMassPoint* massPoints;
  double dStartTime=0.0, dElapsedTimeSer=0.0, dElapsedTimePar=0.0;
  
  if(argc != 3)
  {
    printf("Invalid number of Arguments. Please enter ./nbody <numofThreads> <numberOfMassPoints>\n");
  }
  else
  {
    numThreads = atoi(argv[1]);
    numberOfMassPoints = atoi(argv[2]);

    /* Parallel Part */
    massPoints = sInitMassPoints(numberOfMassPoints, maxValue);
    
    /* Start time-measurement, parallel */
    dStartTime = dstartMesGTOD();
    #pragma omp parallel
    {
      threadID = omp_get_thread_num();
      for(n=0; n<iterations; n++)
      {
       /*
        * Do a pairwise calculation and application of forces
        * and update all velocities with vApplyForces()
        */
        for(i = threadID; i<numberOfMassPoints; i+=numThreads)
        {
          for(j=i+1; j<numberOfMassPoints; j++)
          {
	    vApplyForces(&massPoints[i], &massPoints[j], timestep);	
          }
        }
        #pragma omp barrier
        /*
         * Update Position on all Masspoints after calculating
         * Speeds
         */
        for(k=threadID; k<numberOfMassPoints; k+=numThreads)
        {
          vUpdatePosition(&massPoints[k], timestep);
        }
        #pragma omp barrier
      }
    }
    /* Stop time-measurement */
    dElapsedTimePar = dstopMesGTOD(dStartTime) / iterations;
    
    /* Seriell Part */
    massPoints = sInitMassPoints(numberOfMassPoints, maxValue);
  
    /* Start time-measurement for serial relaxation */
    dStartTime = dstartMesGTOD();
    for(n=0; n<iterations; n++)
    {
      for(i = 0; i<numberOfMassPoints-1; i++)
      {
        for(j=i+1; j<numberOfMassPoints; j++)
        {
          vApplyForces(&massPoints[i], &massPoints[j], timestep);
        }
      }
      
      for(k=0; k<numberOfMassPoints; k++)
      {
        vUpdatePosition(&massPoints[k], timestep);
      }
    }
    dElapsedTimeSer = dstopMesGTOD(dStartTime) / iterations;
    
    printf("\n Time for calculation (per Iteration): \n");
    printf("\n Parallel       : %lfs \n", dElapsedTimePar);
    printf(" Serial         : %lfs \n\n", dElapsedTimeSer);
    printf(" Speed-Up       : %lf \n", dElapsedTimeSer/dElapsedTimePar);
  }  

  return EXIT_SUCCESS;
}