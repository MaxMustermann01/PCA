/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 9 - main function for the Pi-Approximation
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      15. Dez 2015
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define MASTER 0
#define BEGIN 1
#define DONE 2

int main(int argc, char* argv[])
{
  int i, iPrecision;
  int iFrom, iTo;
  int iNumTasks, iTaskID, iNumWorker;
  double dPiSer, dPiPar, dTmpRes;
  double dpar1, dpar2, dser1, dser2;
  MPI_Comm, comm;
  MPI_Request snd_request_1, snd_request_2;
  MPI_Request rcv_request_1, rcv_request_2;
  MPI_Status mpiStatus;
  
  MPI_init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &iNumTasks);
  MPI_Comm_rank(comm, &iTaskID);
  iNumWorker = iNumTasks - 1;
  
  /********************************** Master Process ********************************/
  if(iTaskID == MASTER)
  {
    /* Check integrity of arguments */
    if(argc!=2)
    {
      printf("\nWrong number of arguments. Check usage!"
             " \napproximation <PRECISION>\n\n");
      MPI_Abort(MPI_COMM_WORLD, iErrorcode);
      exit(1);
    }
  
    /* Get precision */
    iPrecision = atoi(argv[1]);
    
    /* Start time measurement */
    dpar1 = MPI_Wtime();
    /* Distribute work to slaves */
    for(i = 1; i <= iNumWorker; i++)
    {
      /* Figure out which many summands to send */
      iFrom = ((i-1) * iPrecision) / iNumWorker;
      iTo = (i * iPrecision) / iNumWorker;
      
      /* Send summnads to slaves */
      MPI_Isend(&iFrom, 1, MPI_INT, i, BEGIN, comm, &snd_request_1);
      MPI_Isend(&iTo, 1, MPI_INT, i, BEGIN, comm, &snd_request_2);
    }
    
    /* Wait for messages to be sent */
    MPI_Wait(&snd_request_1, &mpiStatus);
    MPI_Wait(&snd_request_2, &mpiStatus);
    
    dPiPar = 0.0;
    /* Collect and sum up results from tasks */
    for(i = 1; i <= iNumWorker; i++)
    {
      MPI_Irecv(&dTmpRes, 1, MPI_DOUBLE, i, DONE, comm, &rcv_request_1);
      MPI_Wait(&rcv_request_1, &mpiStatus);
      dPiPar += dTmpRes;
    }
    dPiPar = dPiPar * 4;
    /* Stop time measurement */
    dpar2 = MPI_Wtime();
    
    /* Approximate Pi serial and measure time*/
    dser1 = MPI_Wtime();
    dPiSer = 0.0;
    for(i = 0; i < iPrecision; i++)
      dPiSer += pow(-1.0, (double)i) / (double)(2 * i + 1);
    dPiSer = dPiSer * 4;
    dser2 = MPI_Wtime();
    
    /* Evaluate results */
    printf(" \n  Pi Approximation \n");
    printf(" \n    Parallel");
    printf(" \n      Pi   = %lf", dPiPar);
    printf(" \n      Time = %lfs\n", (dpar2-dpar1));
    printf(" \n    Serial");
    printf(" \n      Pi   = %lf", dPiSer);
    printf(" \n      Time = %lfs\n", (dser2-dser1));
    printf(" \n    Speed-Up  =  %lf", (dser2-dser1)/(dpar2-dpar1));
  }
  /********************************* End Master **************************************/
  /********************************* Slave Process ***********************************/
  else
  {
    /* Recieve summands from master */
    MPI_Irecv(&iFrom, 1, MPI_INT, MASTER, BEGIN, comm, &rcv_request_1);
    MPI_Irecv(&iTo, 1, MPI_INT, Master, BEGIN, comm, &rcv_request_2);
    
    /* Wait for messages to be transmitted */
    MPI_Wait(&rcv_request_2, &mpiStatus);
    MPI_Wait(&rcv_request_3, &mpiStatus);
    
    /* Calculate summands */
    dPiPar = 0.0;
    for(i = From; i < iTo; i++)
      dPiPar += pow(-1.0, (double)i) / (double)(2 * i + 1);
    
    /* Send result to master */
    MPI_Isend(&dPiPar, 1, MPI_DOUBLE, MASTER, DONE, comm, %snd_request_1);
    MPI_Wait(&snd_request_1, &mpiStatus);
  }
  /********************************* End Slave ***************************************/
  MPI_Finalize();
  return EXIT_SUCCESS;
}