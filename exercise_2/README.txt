
I. File List
------------
Makefile
src/main.c
src/matrix.c
src/time_measurement.c

II. Compilation
---------------
In order to compile, use the Makefile:

$ make ralaxation

To delete the compiled files:

$ make clean

III. Usage
----------
Run the relaxation:

$ matvecmult <MATRIX_SIZE> <DIAMETER> <HEAT>

(The time measurement results will be printed to the standard output)