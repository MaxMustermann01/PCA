#
# Exercise 8 - Makefile
# AUTHORS  Shamna Shyju (shamnashyju@googlemail.com)
#          Fabian Finkeldey (Fabian@Finkeldey-hm.de)
#          Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
#

CC = mpicc
CFLAGS = -Wall
LDLIBS = 

# Optimization Flags:
# -O1    : Optimizing compilation takes somewhat more time, and a lot more memory for a 
#          large function.
# -02    : Optimize even more.
# -03    : Optimize yet more. -O3 turns on all optimizations specified by -O2 and more
# -Ofast : Disregard strict standards compliance. -Ofast enables all -O3 optimizations. It 
#         also enables optimizations that are not valid for all standard-compliant programs.

CFLAGS += -O3

hello :
	$(CC) $(CFLAGS) $(LDLIBS)	src/7.1/main.c \
					-o hello

clean :
	rm -f hello
