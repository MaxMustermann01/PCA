/*********************************************************************************
* FILENAME time_measurement.c
*
* DESCRIPTION These functions are part of the submission to exercises of
* the Parallel Computer Architecture (PCA) lecture of the
* University of Heidelberg.
*
* Exercise 1 - Implementation for the time measurement
*
* AUTHORS Shamna Shyju (shamnashyju@googlemail.com)
* Fabian Finkeldey (Fabian@Finkeldey-hm.de)
* Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
*
* LAST CHANGE 27. OKT 2014
*
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "time_measurement.h"
#include "utils.h"

/* start time measurement based on rdtsc() */
unsigned long long ullstartMesRDTSC(void)
{
  return rdtsc();
}

/* stop time measurement based on rdtsc() */
double dstopMesRDTSC(unsigned long long ullStartTime)
{
  unsigned long long ullStopTime;
  ullStopTime = rdtsc();
  /* The denominator depends on the CPU freq. In my case it is 1.2 GHz */
  /* To get the right value, run: lscpu on commandline  */
  return (double)(ullStopTime - ullStartTime) / 120000000;
}

/* Start time-measurement */
double dstartMesGTOD(void)
{
  struct timeval tim;
  gettimeofday(&tim, NULL);
  return tim.tv_sec+(tim.tv_usec/1000000.0);
}

/* Stop time-measurement */
double dstopMesGTOD(double dStartTime)
{
  struct timeval tim;
  gettimeofday(&tim, NULL);
  return (tim.tv_sec+(tim.tv_usec/1000000.0)) - dStartTime;
}

/* Opens File for storing N/Time-Values */
FILE* OpenTimeFile()
{
  FILE *f = fopen("Time_measurement.dat", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
    
  }
  return f;
}

/* Writes a value with corresponding index in a file */
void writeTimeToFile(FILE *f, int index, double value)
{
  /* print index and long integer */
  fprintf(f, "%d %f \n", index, value);
}

/* Just for testing */
void TestFileWriting()
{
  FILE* f = OpenTimeFile();
  writeTimeToFile(f, 0, 10);
  writeTimeToFile(f, 1, 10);
  writeTimeToFile(f, 2, 36);
  writeTimeToFile(f, 10, 10);
  writeTimeToFile(f, 1000, 12);
  fclose(f);
}