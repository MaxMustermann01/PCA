
I. File List
------------
Makefile
src/8.2/main.c

II. Compilation
---------------
In order to compile, use the Makefile:

$ make hello

$ make latency

To delete the compiled files:

$ make clean

III. Usage
----------
Run the MPI Hello World!: 

$ mpirun -host <HOSTS> -np <NUM_PROCESSES> ./mpi_hello
$ mpirun -host <HOSTS> -np <NUM_PROCESSES> ./latency

HOSTS		creek01,creek02,...
NUM_PROCESSES	start n processes