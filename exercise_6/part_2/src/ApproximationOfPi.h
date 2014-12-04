/*********************************************************************************
 * FILENAME         ApproximationOfPi.h
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 1 - Header-File the Approximation of Pi
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      28. OKT 2014
 * 
 ********************************************************************************/
#ifndef APPROXIMATIONOFPI_H
#define APPROXIMATIONOFPI_H

/*
 * DESCRIPTION - will return the f(x) value to a given x
 * PARAMETER   - X-value
 * RETURN      - double, function-value
 */
double f(double);

/*
 * DESCRIPTION - will approximate pi in n steps
 * PARAMETER   - step-count
 * RETURN      - double approximated value for pi
 */
double approximatePiSer(int);

/*
 * DESCRIPTION - will approximate pi in n steps with parallel Threads
 * PARAMETER   - step-count
 * RETURN      - double approximated value for pi
 */
double approximatePiPar(int);

#endif
