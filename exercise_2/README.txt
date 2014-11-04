
I. File List
------------
Makefile
src/main.c
src/matrix.c
src/time_measurement.c

II. Compilation
---------------
In order to compile, use the Makefile:

$ make relaxation

To delete the compiled files:

$ make clean

III. Usage
----------
Run the relaxation:

$ relaxation <MATRIX_SIZE> <DIAMETER> <HEAT>

(The calculated matrix will be printed to the std-output, so be careful with
 the <MATRIX_SIZE>)