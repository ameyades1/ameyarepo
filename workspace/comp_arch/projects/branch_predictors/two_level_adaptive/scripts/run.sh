#!/bin/bash

#
# Return Address Stack
#

# Results folder
#[ -z $results_folder_base ] && results_folder_base=../results/return_address_stack

results_folder=../results/per_address/$(uuidgen -t)
mkdir -p $results_folder

# Log file
log_file=$results_folder/results.log

# Executable path
predictor_path=../src/

# Trace file directory
trace_file_directory=../traces

# Trace file list
declare -a trace_list=( 
   "DIST-FP-1" "DIST-FP-2" "DIST-FP-3" "DIST-FP-4" "DIST-FP-5"
   "DIST-INT-1" "DIST-INT-2" "DIST-INT-3" "DIST-INT-4" "DIST-INT-5"
   "DIST-MM-1" "DIST-MM-2" "DIST-MM-3" "DIST-MM-4" "DIST-MM-5"
   "DIST-SERV-1" "DIST-SERV-2" "DIST-SERV-3" "DIST-SERV-4" "DIST-SERV-5"
)

# Return Address stack sizes
declare rat_size=16

# Global History Size
declare -a g_hist_sizes=(8 16)

# AHRT Size
declare -a ahrt_sizes=(128 256 512)

# AHRT Associativity
declare ahrt_asso=4

# BTB Sizes
declare btb_size=512

for i in ${g_hist_sizes[@]}; do
  mkdir -p $results_folder/g_hist_sizes_${i}
  
  for k in ${ahrt_sizes[@]}; do
    for j in ${trace_list[@]}; do
      echo "Simulating g_hist_size =" $i " ahrt_size = " $k " for trace " $j " ..."
      echo $j >> $results_folder/g_hist_sizes_${i}/trace_analysis_${i}_${k}_${j}.txt  
      $predictor_path/predictor --trace-file=$trace_file_directory/$j --rat-size=$rat_size --g-history-size=$i --ahrt-size=$k --ahrt-asso=$ahrt_asso --btb-size=$btb_size>> $results_folder/g_hist_sizes_${i}/trace_analysis_${i}_${k}_${j}.txt &
    done
  done
  
done

wait

echo -e "\nFinished Simulating ..."

for i in ${g_hist_sizes[@]}; do
  cat $results_folder/g_hist_sizes_${i}/trace_analysis_* > $results_folder/g_hist_sizes_${i}/trace_analysis.txt
done
    
## Compute the mispredict params
#echo -e "\nResults Summary: " $results_folder
#
#for i in ${rat_sizes[@]}; do
#	echo -e "\nRAT Size = $i" | tee -a $log_file
#	grep -i wrong_cc_bpredicts $results_folder/rat_${i}/trace_analysis.txt | awk -v mul=1 '{mul=mual*$9} END {print "Conditional Mispredicts GeoMean = " (mul ^ (1/NR))}' | tee -a $log_file
#	grep -i wrong_tpredicts $results_folder/rat_${i}/trace_analysis.txt | awk -v mul=1 '{mul=mul*$9} END {print "Target Mispredicts GeoMean = " (mul ^ (1/NR))}' | tee -a $log_file
#    grep -i "total accuracy" $results_folder/rat_${i}/trace_analysis.txt | awk -v mul=1 '{mul=mul*$3} END {print "Total Accuracy GeoMean = " (mul ^ (1/NR))}' | tee -a $log_file  
#	echo -e "\n" | tee -a $log_file
#done
