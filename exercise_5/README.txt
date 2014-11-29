
I. File List
------------
Makefile
src/main.c
src/matrix.c
src/matrix.h
src/time_measurement.c
src/time_measurement.h

II. Compilation
---------------
In order to compile, use the Makefile:

$ make relaxation

To delete the compiled files:

$ make clean

III. Usage
----------
Run the heat relaxation: 

$ relaxation <NUM_THREADS> <NUM_ITERATIONS>

NUM_THREADS	How many threads should be used.
NUM_ITERATIONS	How many iterations should be made.

(Output:

 Parallel       : --s 
 Serial         : --s 

 Iteration Rate : -- per sec
 Speed-Up       : --
 )