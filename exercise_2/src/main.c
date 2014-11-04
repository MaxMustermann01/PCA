/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 2 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      04. Nov 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "time_measurement.h"

int main(int argc, char* argv[])
{
  int iSize, iDiameter;
  double dValue;
  sMatrixDouble sMgrid;
  double dStartTimeGTOD=0.0, dElapsedTimeGTOD=0.0;
  
  /* Open a File for storing time-measurment-values */
  //FILE * f = OpenTimeFile();
  
  /* Check integrity of arguments */
  if(argc!=4)
  {
    printf("\nWrong number of arguments. Check usage!"
           " \nrelaxation <MATRIX_SIZE> <DIAMETER> <HEAT>\n");
    exit(1);
  }
  /* Convert C-String to int */
  iSize = atoi(argv[1]);
  iDiameter = atoi(argv[2]);
  dValue = atoi(argv[3]);
  
  /* Allocate memory for grid */
  if(iAllocMatrixDouble(&sMgrid, iSize, iSize))
  {
    printf("DEBUG: Allocation failure!");
    exit(1);
  }
  
  /* Print matrix before relaxation */
  //vPrintMatrixDouble(&sMgrid);
  vFillCircleMatrix(&sMgrid, iDiameter, dValue);
  /* Start time-measurement, integer */
  dStartTimeGTOD = dstartMesGTOD();
  /* Make relaxation */
  vRelaxMatrix(&sMgrid);
  /* Stop time-measurement, integer */
  dElapsedTimeGTOD = dstopMesGTOD(dStartTimeGTOD);
  
  /* Print matrix after relaxation */
  vPrintMatrixDouble(&sMgrid);
  
  /* Free Allocated Memory */
  vFreeMatrixDouble(&sMgrid);
  
  return EXIT_SUCCESS;
}