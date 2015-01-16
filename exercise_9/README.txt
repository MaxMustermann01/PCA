
I. File List
------------
docu_9.pdf
Makefile
src/9.1/main.c
src/9.2/main.c
src/9.2/matrix.c
src/9.2/matrix.h
src/9.2/time_measurement.c
src/9.2/time_measurement.h

II. Compilation
---------------
In order to compile, use the Makefile:

$ make approximation
$ make relaxation

To delete the compiled files:

$ make clean

III. Usage
----------
In order to run the programs, use the execution-scripts:

$ exec_approximation.sh <NUM_PROCESSES> <PRECISION>
$ exec_relaxation.sh <NUM_PROCESSES> <GRID_SIZE> <NUM_ITERATIONS> <OPTION>

NUM_PROCESSES		Start n processes
PRECISION		How many summands for the Pi-approximation
GRID_SIZE		Size of Grid for the Heat-Relaxation
NUM_ITERATIONS		How many iterations for the Heat-Relaxation
OPTION			(1) Print Matrix, (0) Print Time