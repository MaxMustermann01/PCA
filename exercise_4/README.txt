
I. File List
------------
Makefile
docu_4.pdf
src/main.c
src/matrix_vector_mult.c
src/matrix_vector_mult.h
src/time_measurement.c
src/time_measurement.h
src/utils.h

II. Compilation
---------------
In order to compile, use the Makefile:

$ make mat_mult

To delete the compiled files:

$ make clean

III. Usage
----------
Run the multiplication: 

$ mat_mult <MATRIX_SIZE> <NUM_THREADS> <NUM_ITERATIONS> <MODE>

MATRIX_SIZE	Size of the matrix.
NUM_THREADS	How many threads should be uses.
NUM_ITERATIONS	How many iterations should be made.
MODE		Which type shold be used :
		  (1) Integer, (2) Double, (3) Float

(Output:
 Time for calculation (TYPE): 

 Parallel : --s 
 Seriell  : --s 
 Speed-Up : --
 )