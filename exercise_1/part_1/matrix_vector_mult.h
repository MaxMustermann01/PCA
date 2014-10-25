/*********************************************************************************
 * FILENAME         matrix_vector_mult.h
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 1 - Header-File the Matrix-Vector-Multiplication
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      24. OKT 2014
 * 
 ********************************************************************************/
#ifndef MATRIX_VECTOR_MULT_H
#define MATRIX_VECTOR_MULT_H


typedef struct sMatrixInt
{
  int iRow;       // for rows
  int iCol;       // for columns
  int** ppaMat;   // int[][]
} sMatrixInt;

typedef struct sMatrixDouble
{
  int iRow;       // for rows
  int iCol;       // for columns
  double** ppaMat;   // int[][]
} sMatrixDouble;

typedef struct sMatrixFloat
{
  int iRow;       // for rows
  int iCol;       // for columns
  float** ppaMat;   // int[][]
} sMatrixFloat;

/* 
 * DESCRIPTION - Multiply a matrix by a vector; either int, double,float
 * PARAMETER   - sMatrix *: pointer to matrix (it's quatratic) which should be multiplied
 *               sMatrix *: pointer to vector which should be multiplied
 *               sMatrix *: pointer to vector in which the result will be stored
 * RETURN      - void
 */
void vMatrixVecMulInt(sMatrixInt *, sMatrixInt *, sMatrixInt *);
void vMatrixVecMulDouble(sMatrixDouble *, sMatrixDouble *, sMatrixDouble *);
void vMatrixVecMulFloat(sMatrixFloat *, sMatrixFloat *, sMatrixFloat *);

/*
 * DESCRIPTION - Allocate memory for the dynamic matrix; either int, double, float
 * PARAMETER   - sMatrixInt: pointer to a sMatrixInt type for which the memory will be allocated
 *             - Integer: matrix rows
 *             - Integer: matrix columns
 *RETURN       - Integer: 0 if alloc was ok, 1 if alloc failed 
 */
int vAllocMatrixInt(sMatrixInt *,int, int);
int vAllocMatrixDouble(sMatrixDouble *,int, int);
int vAllocMatrixFloat(sMatrixFloat *,int, int);
/*
 * DESCRIPTION - will free the allocated memory; either int, double, float
 * PARAMETER   - pointer to type sMatrixInt, which should be destroid
 * RETURN      - void
 */
void vFreeMatrixInt(sMatrixInt *);
void vFreeMatrixDouble(sMatrixDouble *);
void vFreeMatrixFloat(sMatrixFloat *);
/*
 * DESCRIPTION - prints the matrix-elements; either int, double, float; only for test
 * PARAMETER   - pointer to matrix, which should be printed
 * RETURN      - void
 */
void vPrintMatrixInt(sMatrixInt *);
void vPrintMatrixDouble(sMatrixDouble *);
void vPrintMatrixFloat(sMatrixFloat *);
/*
 * DESCRIPTION - initialize a matrix with random numbers, either int, double, float
 * PARAMETER   - pointer to matrix...
 *               integer for seed
 * RETRUN      - void
 */
void vInitMatrixInt(sMatrixInt *, int);
void vInitMatrixDouble(sMatrixDouble *, int);
void vInitMatrixFloat(sMatrixFloat *, int);

#endif
