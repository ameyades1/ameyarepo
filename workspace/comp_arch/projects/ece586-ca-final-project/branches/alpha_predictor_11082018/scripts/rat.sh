#!/bin/bash

#
# Return Address Stack, No BTB
#

log_file=../results/rat_results.log
rm -rf $log_file

# Return Address stack sizes
rat_sizes=(1 2 4 8 16 32)

for i in ${rat_sizes[@]}; do
  echo "RAT = " $i
  ./gen_report.pl rat${i} $i &
done

wait

# Compute the mispredict params

for i in ${rat_sizes[@]}; do
	echo -e "RAT Size = $i" | tee -a $log_file
	grep -i wrong_cc_bpredicts ../results/rat${i}/trace_analysis.txt | awk -v mul=1 '{mul=mul*$9} END {print "Conditional Mispredicts GeoMean = " (mul ^ (1/NR))}' | tee -a $log_file
	grep -i wrong_tpredicts ../results/rat${i}/trace_analysis.txt | awk -v mul=1 '{mul=mul*$9} END {print "Target Mispredicts GeoMean = " (mul ^ (1/NR))}' | tee -a $log_file
	echo -e "\n" | tee -a $log_file
done
