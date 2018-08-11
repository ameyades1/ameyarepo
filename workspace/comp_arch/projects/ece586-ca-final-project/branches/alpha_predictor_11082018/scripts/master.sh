#!/bin/bash
#Return Address stack sizes

rat_sizes=(1 2 4 8 16 32)

for i in ${rat_sizes[@]}; do
  echo "RAT = " $i
  ./gen_report.pl rat${i} $i
done
