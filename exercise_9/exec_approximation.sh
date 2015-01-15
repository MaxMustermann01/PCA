#!/usr/bin/env bash

if [ $# -ne 2 ]
then
  echo "Check Usage: exec_approximation.sh <NUM_PROCESSES> <PRECISION>"
  exit 1
fi

mpirun -host creek01,creek02,creek03,creek04,creek05,creek06,creek07,creek08 -np $1 ./approximation $2