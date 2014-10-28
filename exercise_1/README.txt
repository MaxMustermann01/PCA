
I. File List
------------
Makefile
part_1/main.c
part_1/matrix_vector_mult.c
part_1/time_measurement.c
part_2/ApproximationOfPi.c

II. Compilation
---------------
In order to compile, use the Makefile:

$ make matvecmult
$ make approximatepi

To delete the compiled files:

$ make clean

III. Usage
----------
Run the Matrix-vector-Multiplication:

$ matvecmult <MATRIX_SIZE> <SEED>

(The time measurement results will be printed to the standard output. Also they will
be stored in a file called 'Time_measurement.dat'.)

Run the Pi approximation:

$ approximatepi <PRECISION>

(The Pi approximation will be printed to the standard output.)