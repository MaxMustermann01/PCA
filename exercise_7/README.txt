
I. File List
------------
Makefile
src/7.1/main.c
src/7.1/matrix.c
src/7.1/matrix.h
src/7.1/time_measurement.c
src/7.1/time_measurement.h
src/7.2/main.c
src/7.2/nbody.c
src/7.2/nbody.h
src/7.2/time_measurement.c
src/7.2/time_measurement.h

II. Compilation
---------------
In order to compile, use the Makefile:

$ make relaxation
$ make nbody

To delete the compiled files:

$ make clean

III. Usage
----------
Run the heat relaxation: 

$ relaxation <NUM_THREADS> <NUM_ITERATIONS>
$ nbody <NUM_THREADS> <NUM_ELEMENTS>

NUM_THREADS	How many threads should be used.
NUM_ITERATIONS	How many iterations should be made.

(Output:

 Parallel       : --s 
 Serial         : --s 

 Iteration Rate : -- per sec
 Speed-Up       : --
 )