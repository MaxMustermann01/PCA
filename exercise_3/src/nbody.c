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

//ToDo Implementation of Functions defined in nbody.h
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


