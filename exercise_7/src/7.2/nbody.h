/*********************************************************************************
 * FILENAME         nbody.h
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 7 - Header-File the NBody-handling
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      22. Dez 2014
 * 
 ********************************************************************************/
#ifndef NBODY_H
#define NBODY_H

#define G 0.00000000006673

typedef struct sMassPoint
{
  double dVelocityX;
  double dVelocityY;
  double dPositionX;
  double dPositionY;
  double dMass;
} sMassPoint;

/*
 * DESCRIPTION - Creates a given Number of masspoints with random
 *               Position and Mass
 * PARAMETER   - Integer: Number of masspoints to create
 *             - Integer: Maximum Value for Position and Mass
 * RETURN       - sMassPoint*: All created masspoints 
 */
sMassPoint* sInitMassPoints(int, int);

/*
 * DESCRIPTION - Simulates Interaction between two given MassPoints
 *	         and applies the changes in Velocity
 * PARAMETER   - sMassPoint*, sMassPoint* 
 *               Integer: Timestep delta T
 */
void vApplyForces(sMassPoint*, sMassPoint*, int);

/*
 * DESCRIPTION - Changes Position according to the current
 *               Velocity.
 * PARAMETER   - sMassPoint*, int timestep
 */
void vUpdatePosition(sMassPoint*, int);

/*
 * DESCRIPTION - Prints all values of a MassPoint
 * PARAMETER   - sMassPoint*
 */
void vPrintMassPoint(sMassPoint*);

/*
 * DESCRIPTION - Executes the nBody Simulation with a given Number
 * 		 of Masspoints, iterations, and timesteps.
 *
 * PARAMETER   - Integer: Number of masspoints to create
 * 	       - Integer: Iterations to do
 *             - Integer: Time between every Iteration
 *             - Integer: Maximum Value for Position and Mass
 * RETURN       - sMassPoint*: All created masspoints after Simulation
 */
sMassPoint* vSimulate(int, int, int, int);

#endif

