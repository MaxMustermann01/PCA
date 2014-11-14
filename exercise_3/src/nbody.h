/*********************************************************************************
 * FILENAME         nbody.h
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 3 - Header-File the NBody-handling
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      14. Nov 2014
 * 
 ********************************************************************************/
#ifndef NBODY_H
#define NBODY_H

typedef struct sMassPoint
{
  double dVelocityX;
  double dVelocityY;
  double dPositionX;
  double dPositionY;
  double dMass;
} sMassPoint;

/*
 * DESCRIPTION - Creates a given Number of masspoints
 * PARAMETER   - Integer: Number of masspoints to create
 *
 * RETURN       - sMassPoint*: All created masspoints 
 */
sMassPoint* sInitMassPoints(int);

/*
 * DESCRIPTION - Simulates Interaction between two given MassPoints
 *	         and applies the changes in Velocity
 * PARAMETER   - sMassPoint*, sMassPoint* 
 */
void vApplyForces(sMassPoint*, sMassPoint*);

/*
 * DESCRIPTION - Changes Position according to the current
 *               Velocity.
 * PARAMETER   - sMassPoint*, int timestep
 */
void vUpdatePosition(sMassPoint*, int);

#endif

