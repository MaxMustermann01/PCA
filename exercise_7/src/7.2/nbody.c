/*********************************************************************************
 * FILENAME         nbody.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 7 - Implementation for Nbody-Handling
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      22. Dez 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "nbody.h"


sMassPoint* sInitMassPoints(int n, int maxValue)
{
  int i;
  sMassPoint* massPoints;
  
  massPoints = malloc(n*sizeof(sMassPoint));
  
  /*
   * Initialize All MassPoints with random Position and Mass
   * At Start all MassPoints are at rest (V=0)
   */
  for(i=0; i<n; i++)
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
  int n,i;
  
  //Do all iterations
  for(n=0; n<iterations; n++)
  {
    /*
     * Do a pairwise calculation and application of forces
     * and update all velocities with vApplyForces()
    */
    for(i=0; i<numberOfMassPoints-1; i++)
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
    

  }
  
  //Debug: Display some Data to ensure that everthing is working
  printf("\n************************************************\n");
  printf("This Programm will do %d Iterations with a timescale of %d \n", iterations, timestep);
  printf("To show the effect, a sample point will be displayed after the simulation. \n");
  printf("Starting Simulation... with vx = vy = 0.0 for all Points \n \n");
  vPrintMassPoint(&massPoints[1]);
  printf("%d Iterations complete \n************************************************ \n \n", n);
  
  return massPoints;
}

sMassPoint* vSimulatePar(int numberOfMassPoints, int iterations, int timestep, int maxValue)
{
  
  //Initialize all MassPoints
  sMassPoint* massPoints = sInitMassPoints(numberOfMassPoints, maxValue);  
  int n = 0;
  
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
    

  }
  
  //Debug: Display some Data to ensure that everthing is working
  printf("\n************************************************\n");
  printf("This Programm will do %d Iterations with a timescale of %d \n", iterations, timestep);
  printf("To show the effect, a sample point will be displayed after the simulation. \n");
  printf("Starting Simulation... with vx = vy = 0.0 for all Points \n \n");
  vPrintMassPoint(&massPoints[1]);
  printf("%d Iterations complete \n************************************************ \n \n", n);
  
  return massPoints;
}