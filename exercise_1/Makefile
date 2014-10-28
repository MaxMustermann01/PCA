#
# Exercise 1 - Makefile
# AUTHORS  Shamna Shyju (shamnashyju@googlemail.com)
#          Fabian Finkeldey (Fabian@Finkeldey-hm.de)
#          Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
#

CC=gcc
CFLAGS = -Wall

# Optimization Flags:
# -O1    : Optimizing compilation takes somewhat more time, and a lot more memory for a 
#          large function.
# -02    : Optimize even more.
# -03    : Optimize yet more. -O3 turns on all optimizations specified by -O2 and more
# -Ofast : Disregard strict standards compliance. -Ofast enables all -O3 optimizations. It 
#         also enables optimizations that are not valid for all standard-compliant programs.

CFLAGS += -O1

matvecmult :
	$(CC) $(CFLAGS)	part_1/main.c \
			part_1/matrix_vector_mult.c \
			part_1/time_measurement.c \
			-o matvecmult

approximatepi :
	$(CC) $(CFLAGS)	part_2/ApproximationOfPi.c \
			part_2/time_measurement.c \
			part_2/main.c \
			-o approximatepi

clean :
	rm -f matvecmult approximatepi Time_measurement.dat
