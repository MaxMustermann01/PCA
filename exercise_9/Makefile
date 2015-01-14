#
# Exercise 9 - Makefile
# AUTHORS  Shamna Shyju (shamnashyju@googlemail.com)
#          Fabian Finkeldey (Fabian@Finkeldey-hm.de)
#          Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
#
CC = mpicc
CPP = mpic++
CFLAGS = -Wall

relaxation:
	$(CC) $(CFLAGS)		src/9.2/main.c \
				src/9.2/matrix.c \
				src/9.2/time_measurement.c
				-o relaxation

clean :
	rm -f 	relaxation