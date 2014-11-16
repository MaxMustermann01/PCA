/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 3 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      14. Nov 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "nbody.h"
#include "time_measurement.h"

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    printf("Invalid number of Arguments. Please enter ./nbody <numberOfMassPoints>");
  }
  else
  {
    /*
     * numberOfMassPoints, iterations, timestep, maxValue for mass and position 
     * Choose large timestep to see an significant position cange
     */
    vSimulate(atoi(argv[1]), 100, 100, 25000);
  }  

  return EXIT_SUCCESS;
}