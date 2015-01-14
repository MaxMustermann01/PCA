/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 9 - main function for the Heat equation
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      14. Dez 2015
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "time_measurement.h"
#include "mpi.h"

#define FI 0.24
#define MASTER 0
#define BEGIN 1
#define LEFTTAG 2
#define RIGHTTAG 3
#define DONE 4
#define DIAMETER 128
#define HEAT 60
#define SOUTH 0
#define NORTH 1

int main(int argc, char* argv[])
{
  int iSize, iIterations, iOpt, j, k;
  /* MPI variables */
  int iErrorcode = 0, iNumTasks, iTaskID, iNumWorker;
  int iFrom, iTo, iRows, iCols;
  MPI_Status mpiStatus;
  MPI_Request snd_request_1, snd_request_2, snd_request_3, snd_request_4, snd_request_5;
  MPI_Request rcv_request_1, rcv_request_2, rcv_request_3, rcv_request_4, rcv_request_5;
  int periods[1], dims[1], reorganisation=0, ndims, index, displ, Neighbor[2];
  MPI_Comm comm, comm1d;
  double dpar1, dpar2, dser1, dser2;
  sMatrixDouble sMgrid, sMgridSer, sMgridTmp[2];
  int iIndex = 0;

  MPI_Init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &iNumTasks);
  MPI_Comm_rank(comm, &iTaskID);
  iNumWorker = iNumTasks - 1;
  
  /* Create 1D grid */
  
  periods[0] = 0;
  ndims = 1;
  dims[0] = iNumTasks;
  
  MPI_Cart_create(comm, ndims, dims, periods, reorganisation, &comm1d);
  index = 0; // shift along the first index
  displ = 1; // shift by 1
  MPI_Cart_shift(comm1d, index, displ, &Neighbor[NORTH], &Neighbor[SOUTH]);
  
  /********************************** Master process **********************************/
  if(iTaskID == MASTER)
  {
    /* Check integrity of arguments */
    if(argc!=4)
    {
      printf("\nWrong number of arguments. Check usage!"
             " \nrelaxation <MATRIX_SIZE> <ITERATIONS> <OPTION>\n\n"
             "<OPTION> : (1) Print Matrix, (0) Print ellapsed time\n");
      MPI_Abort(MPI_COMM_WORLD, iErrorcode);
      exit(1);
    }
    /* Convert C-String to int */
    iSize = atoi(argv[1]);
    iIterations = atoi(argv[2]);
    iOpt = atoi(argv[3]);
    
    /* Allocate memory for grid and inject heat */
    iAllocMatrixDouble(&sMgrid, iSize, iSize);
    vFillCircleMatrix(&sMgrid, DIAMETER, HEAT);
    
    /* Start time-measurement */
    dpar1 = MPI_Wtime();
    /********************* Start parallel equation ********************/
    /* Distribute work to tasks */
    for(i=1; i<=iNumWorker; i++)
    {
      /* Figure out how many rows to send */
      iFrom = ((i-1) * sMgrid.iRow) / iNumWorker;
      iTo = (i * sMgrid.iRow) / iNumWorker;
      iRows = iTo - iFrom;
      iCols = iSize;
 
      /* Send offset, number of coloumns, iterations and number of rows */
      MPI_Isend(&iFrom, 1, MPI_INT, i, BEGIN, comm1d, &snd_request_1);
      MPI_Isend(&iRows, 1, MPI_INT, i, BEGIN, comm1d, &snd_request_2);
      MPI_Isend(&iCols, 1, MPI_INT, i, BEGIN, comm1d, &snd_request_3);
      MPI_Isend(&iIterations, 1, MPI_INT, i, BEGIN, comm1d, &snd_request_4);
      /* Send Data */
      MPI_Isend(&(sMgrid.ppaMat[iFrom][0]), iRows*iCols, MPI_DOUBLE, i, BEGIN, comm1d, &snd_request_5);
    }
    /* Wait for all messages to transmit */
    MPI_Wait(&snd_request_1, &mpiStatus);
    MPI_Wait(&snd_request_2, &mpiStatus);
    MPI_Wait(&snd_request_3, &mpiStatus);
    MPI_Wait(&snd_request_4, &mpiStatus);
    MPI_Wait(&snd_request_5, &mpiStatus);
    /* Collect results from tasks */
    for(i=1; i<=iNumWorker; i++)
    {
      MPI_Irecv(&iFrom, 1, MPI_INT, i, DONE, comm1d, &rcv_request_1);
      MPI_Irecv(&iRows, 1, MPI_INT, i, DONE, comm1d, &rcv_request_2);
      MPI_Wait(&rcv_request_1, &mpiStatus);
      MPI_Wait(&rcv_request_2, &mpiStatus);

      MPI_Irecv(&(sMgrid.ppaMat[iFrom][0]), iRows*sMgrid.iCol, MPI_DOUBLE, i, DONE, comm1d, &rcv_request_3);
    }
    MPI_Wait(&rcv_request_3, &mpiStatus);
    /****************** End parallel equation **********************/
    /* Stop time-measurement */
    dpar2 = MPI_Wtime();

    /******************* Start serial equation **********************/
    /* Allocate memory for grid */
    if(iAllocMatrixDouble(&sMgridSer, iSize, iSize))
    {
      printf("DEBUG: Allocation failure!");
      exit(1);
    }

    vFillCircleMatrix(&sMgrid, DIAMETER, HEAT);
    
    dser1 = MPI_Wtime();
    for(i = 0; i < iIterations; i++)
      vRelaxMatrix(&sMgrid);
    dser2 = MPI_Wtime();

    /******************* End serial equation ************************/
    
    /* Print grid to std-output */
    if(iOpt == 1)
      vPrintMatrixDouble(&sMgrid);
    else
    {
      printf(" \n Elapsed Time : ");
      printf(" \n   Parallel %lf s\n",(dpar2-dpar1)/iIterations);
      printf(" \n   Serial   %lf s\n",(dser2-dser1)/iIterations);
      printf(" \n   Speed-Up %lf \n",(dser2-dser1)/(dpar2-dpar1));
    }
    /* Free allocated memory */
    vFreeMatrixDouble(&sMgrid);
    vFreeMatrixDouble(&sMgridSer);
  }
  /************************************ Slave process *********************************/
  else
  {
    /* Recieve offset, number of coloums, iterations and number of rows */
    MPI_Irecv(&iFrom, 1, MPI_INT, MASTER, BEGIN, comm1d, &rcv_request_1);
    MPI_Irecv(&iRows, 1, MPI_INT, MASTER, BEGIN, comm1d, &rcv_request_2);
    MPI_Irecv(&iCols, 1, MPI_INT, MASTER, BEGIN, comm1d, &rcv_request_3);
    MPI_Irecv(&iIterations, 1, MPI_INT, MASTER, BEGIN, comm1d, &rcv_request_4);

    MPI_Wait(&rcv_request_2, &mpiStatus);
    MPI_Wait(&rcv_request_3, &mpiStatus);

    /* Allocate memory for grid-slice and for temporary grid */
    iAllocMatrixDouble(&sMgridTmp[0], iRows+2, iCols);
    iAllocMatrixDouble(&sMgridTmp[1], iRows+2, iCols);
    
    MPI_Wait(&rcv_request_1, &mpiStatus);
    MPI_Wait(&rcv_request_4, &mpiStatus);
    /* Recieve data from master */
    /* Start with index 0 */
    iIndex = 0;
    MPI_Irecv(&(sMgridTmp[iIndex].ppaMat[1][0]), iRows*iCols, MPI_DOUBLE, MASTER, BEGIN, comm1d, &rcv_request_5);
    MPI_Wait(&rcv_request_5, &mpiStatus);
    for(i=0; i<iIterations; i++)
    {
      if(Neighbor[NORTH] > 0)
      {
        MPI_Irecv(&(sMgridTmp[iIndex].ppaMat[0][0]), iCols, MPI_DOUBLE, Neighbor[NORTH], LEFTTAG, comm1d, &rcv_request_1);
        MPI_Isend(&(sMgridTmp[iIndex].ppaMat[1][0]), iCols, MPI_DOUBLE, Neighbor[NORTH], RIGHTTAG, comm1d, &snd_request_1);
      }
      if(Neighbor[SOUTH] > 0)
      {
        MPI_Isend(&(sMgridTmp[iIndex].ppaMat[iRows][0]), iCols, MPI_DOUBLE, Neighbor[SOUTH], LEFTTAG, comm1d, &snd_request_2);
        MPI_Irecv(&(sMgridTmp[iIndex].ppaMat[iRows+1][0]), iCols, MPI_DOUBLE, Neighbor[SOUTH], RIGHTTAG, comm1d, &rcv_request_2);
      }
      /* Calculate new grid points and let border elements static */
      for(j=2; j<iRows; j++)
        for(k=0; k<iCols; k++)
	{
          /* Update temporary grid */
          sMgridTmp[1-iIndex].ppaMat[j][k] =sMgridTmp[iIndex].ppaMat[j][k] \
                                             +FI*((-4)*sMgridTmp[iIndex].ppaMat[j][k] \
                                             +sMgridTmp[iIndex].ppaMat[j+1][k] \
                                             +sMgridTmp[iIndex].ppaMat[j-1][k] \
                                             +sMgridTmp[iIndex].ppaMat[j][k+1] \
                                             +sMgridTmp[iIndex].ppaMat[j][k-1]);
        }

      if(Neighbor[NORTH] > 0)
      {
        j=1;
        MPI_Wait(&snd_request_1, &mpiStatus);
        MPI_Wait(&rcv_request_1, &mpiStatus);
        for(k=1; k<iCols-1; k++){
          sMgridTmp[1-iIndex].ppaMat[j][k]   =sMgridTmp[iIndex].ppaMat[j][k] \
                                             +FI*((-4)*sMgridTmp[iIndex].ppaMat[j][k] \
                                             +sMgridTmp[iIndex].ppaMat[j+1][k] \
                                             +sMgridTmp[iIndex].ppaMat[j-1][k] \
                                             +sMgridTmp[iIndex].ppaMat[j][k+1] \
                                             +sMgridTmp[iIndex].ppaMat[j][k-1]);
        }
      }
     
      if(Neighbor[SOUTH] > 0)
      {
        j=iRows;
        MPI_Wait(&snd_request_2, &mpiStatus);
        MPI_Wait(&rcv_request_2, &mpiStatus);
        for(k=1; k<iCols-1; k++)
        {
          sMgridTmp[1-iIndex].ppaMat[j][k] =sMgridTmp[iIndex].ppaMat[j][k] \
                                             +FI*((-4)*sMgridTmp[iIndex].ppaMat[j][k] \
                                             +sMgridTmp[iIndex].ppaMat[j+1][k] \
                                             +sMgridTmp[iIndex].ppaMat[j-1][k] \
                                             +sMgridTmp[iIndex].ppaMat[j][k+1] \
                                             +sMgridTmp[iIndex].ppaMat[j][k-1]);
        }
      }
      /* Invert Index */
      iIndex = 1 - iIndex;
    }
    /* Send results back to master */
    MPI_Isend(&iFrom, 1, MPI_INT, MASTER, DONE, comm1d, &snd_request_1);
    MPI_Isend(&iRows, 1, MPI_INT, MASTER, DONE, comm1d, &snd_request_2);
    MPI_Isend(&(sMgridTmp[iIndex].ppaMat[1][0]), iRows*iCols, MPI_DOUBLE, MASTER, DONE, comm1d, &snd_request_3);
  
    MPI_Wait(&snd_request_1, &mpiStatus); 
    MPI_Wait(&snd_request_2, &mpiStatus);
    MPI_Wait(&snd_request_3, &mpiStatus); 
    
    /* Free allocated memory */
    vFreeMatrixDouble(&sMgridTmp[1-iIndex]);
    vFreeMatrixDouble(&sMgridTmp[iIndex]);
  }
  MPI_Finalize();
  return EXIT_SUCCESS;
}
