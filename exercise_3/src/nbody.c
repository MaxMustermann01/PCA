/*********************************************************************************
 * FILENAME         nbody.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 3 - Implementation for Nbody-Handling
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
#include "main.c"

/*
 * ToDo: Organized Output to Screen or file
 * ToDo: Validate function 
 * ToDo: Better (random) Values on Mass and Position:
 *       Small masses and huge distance between massPoints
 *       results in small changes in position, so its likely
 *       to miss them in the output!
 */

/*
* Main Idea: Loop over all Masspoints:
* Do pairwise ApplyForces for the current Masspoint with all following masspoints.
* Example:
* May the masspoints are named a, b, c, d:
* Do (a, b), (a, c), (a, d)
* Do (b, c), (c, d)
* Do (c, d)
* Since ApplyForces applies the Force to both given Points,
* (a, b) is equal to (b, a) and therefore it's not necessary
* to repeat this step in following iterations.
* ApplyForce will update the Velocity of both given Masspoints
* with the calculated delta.
*
* After applying all forces and updating all velocities,
* updatePosition of all MP's to simulate the next timestep
*/

sMassPoint* sInitMassPoints(int n, int maxValue)
{
  int i = 0;
  sMassPoint* massPoints;
  
  massPoints = malloc(n*sizeof(sMassPoint));
  
  /*
   * Initialize All MassPoints with random Position and Mass
   * At Start all MassPoints are at rest (V=0)
   */
  for(i; i<n; i++)
  {
    sMassPoint* tmp = &massPoints[i];
    tmp->dVelocityX = 0.0;
    tmp->dVelocityY = 0.0;
    tmp->dPositionX = (double) (rand()%maxValue);
    tmp->dPositionY = (double) (rand()%maxValue);
    tmp->dMass = (double) (rand()%maxValue);
  }  
  return massPoints;
  
}

void vApplyForces(sMassPoint* mpA, sMassPoint* mpB, int deltaT)
{
  /*
   * Calculate Distance between both MassPoints.
   * The Distance is defined as always positive.
   */
  double distanceX = mpA->dPositionX - mpB->dPositionX;
  double distanceY = mpA->dPositionY - mpB->dPositionY;
  
  /*
   * Calculate force as G*(M1*M2)/(distance)²
   * with G as a predefined constant
   * Caution: G is extremly small. So it is possible,
   * that the resulting force is to small to print on screen
   */
  double forceX = G*(mpA->dMass * mpB->dMass) / (distanceX * distanceX);
  double forceY = G*(mpA->dMass * mpB->dMass) / (distanceY * distanceY);
  
  /*
   * Calculate Acceleration as deltaT * force/mass and
   * change current speed of both given MassPoints according
   * to the acceleration
   */
  mpA->dVelocityX += deltaT * forceX / (mpA->dMass);
  mpA->dVelocityY += deltaT * forceY / (mpA->dMass); 
  mpB->dVelocityX += deltaT * forceX / (mpB->dMass);
  mpB->dVelocityY += deltaT * forceY / (mpB->dMass); 
  
}


void vUpdatePosition(sMassPoint* massPoint, int deltaT)
{
  //Change Position according to current velocity
  massPoint->dPositionX += (massPoint->dVelocityX)*deltaT;
  massPoint->dPositionY += (massPoint->dVelocityY)*deltaT;
}

void vPrintMassPoint(sMassPoint* massPoint)
{
  printf("Velocity in X: \t \t %f \n", massPoint->dVelocityX);
  printf("Velocity in Y: \t \t %f \n", massPoint->dVelocityY);  
  printf("Position in X: \t \t %f \n", massPoint->dPositionX); 
  printf("Position in Y: \t \t %f \n", massPoint->dPositionY);
  printf("Total Mass: \t \t %f \n \n", massPoint->dMass);
  
}

sMassPoint* vSimulate(int numberOfMassPoints, int iterations, int timestep, int maxValue)
{
  //Initialize all MassPoints
  sMassPoint* massPoints = sInitMassPoints(numberOfMassPoints, maxValue);  
  int n = 0;
  
  //Debug
  int s = 0;
  for(s; s<numberOfMassPoints; s++)
    vPrintMassPoint(&massPoints[s]);
  
  //Do all iterations
  for(n; n<iterations; n++)
  {
    /*
     * Do a pairwise calculation and application of forces
     * and update all velocities with vApplyForces()
    */
    int i = 0;
    for(i; i<numberOfMassPoints-1; i++)
    {
      int j = i+1;
      for(j; j<numberOfMassPoints; j++)
      {
	vApplyForces(&massPoints[i], &massPoints[j], timestep);	
      }
    }
    
    /*
     * Update Position on all Masspoints after calculating
     * Speeds
    */
    int k=0;
    for(k; k<numberOfMassPoints; k++)
    {
      vUpdatePosition(&massPoints[k], timestep);
    }
    
    //Debug
    /*
    vPrintMassPoint(&massPoints[1]);
    printf("Iteration %d complete \n ************************************** \n \n", (n+1));
    */
  }
  
  //Debug
  printf("################################# \n");
  s = 0;
  for(s; s<numberOfMassPoints; s++)
    vPrintMassPoint(&massPoints[s]);
  return massPoints;
}