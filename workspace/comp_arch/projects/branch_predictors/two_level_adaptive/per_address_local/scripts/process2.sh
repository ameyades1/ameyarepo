#!/bin/bash

trace_file=$1

# Trace file list
declare -a trace_list=( 
   "DIST-FP-1" "DIST-FP-2" "DIST-FP-3" "DIST-FP-4" "DIST-FP-5"
   "DIST-INT-1" "DIST-INT-2" "DIST-INT-3" "DIST-INT-4" "DIST-INT-5"
   "DIST-MM-1" "DIST-MM-2" "DIST-MM-3" "DIST-MM-4" "DIST-MM-5"
   "DIST-SERV-1" "DIST-SERV-2" "DIST-SERV-3" "DIST-SERV-4" "DIST-SERV-5"
)

# Identify the configurations
declare -a rat_sizes=($(grep -i "rat size"   $trace_file | uniq | awk '{print $3}' | sort -n | tr '\n' " "))
declare -a ghr_sizes=($(grep -i "ghr size"   $trace_file | uniq | awk '{print $3}' | sort -n | tr '\n' " "))
declare -a ahrt_sizes=($(grep -i "ahrt size" $trace_file | uniq | awk '{print $3}' | sort -n | tr '\n' " "))
declare -a ahrt_asso=($(grep -i "ahrt asso"  $trace_file | uniq | awk '{print $3}' | sort -n | tr '\n' " "))
declare -a btb_sizes=($(grep -i "btb size"   $trace_file | uniq | awk '{print $3}' | sort -n | tr '\n' " "))

total_config=$((${#rat_sizes[@]} * ${#ghr_sizes[@]} * ${#ahrt_sizes[@]} * ${#ahrt_asso[@]} * ${#btb_sizes[@]}))

echo "---Predictor Configurations---"
echo "RAT Sizes:"  ${rat_sizes[@]}
echo "GHR Sizes:"  ${ghr_sizes[@]}
echo "AHRT Sizes:" ${ahrt_sizes[@]}
echo "AHRT Asso:"  ${ahrt_asso[@]}
echo "BTB Sizes:"  ${btb_sizes[@]}

echo -e "\nTotal Configurations = ${#rat_sizes[@]} x ${#ghr_sizes[@]} x ${#ahrt_sizes[@]} x ${#ahrt_asso[@]} x ${#btb_sizes[@]} = ${total_config}"

declare -a fp_line_nos=($(grep -in "^DIST-FP" $trace_file | head -n 5 | awk -F ":" '{print $1}'))

echo "FP Line Nos =" ${fp_line_nos[@]}
for i in ${fp_line_nos[@]}; do
  echo $i
  sed -n "${fp_line_nos[$i]}, ${fp_line_nos[$i+1]}p" $trace_file
done


#echo -e "\n---Results Summary---"
#echo "RAT GHR AHRT AHRT_ASSO -- Accuracy"
#
#for i in ${rat_sizes[@]}; do
#  for j in ${ghr_sizes[@]}; do
#    for k in ${ahrt_sizes[@]}; do
#      for l in ${ahrt_asso[@]}; do
#      	echo "${i}   ${j}   ${k}    ${l}     " $(grep -i -e "ahrt size: ${k}" -A 13 -B 4 $trace_file | grep -i accuracy | awk -v sum=0 '{sum+=$3;}END{print sum/NR}')
#      done
#    done    
#  done
#done

#grep -i -e "ahrt size: 64" -A 13 -B 4 $trace_file | grep -i accuracy | awk -v sum=0 '{sum+=$3;}END{print sum/NR}'


#echo "RAT Sizes:" $(grep -i "rat size"   $trace_file | sort | uniq | awk '{print $3}' | tr '\n' " ") 
#echo "GHR Sizes:" $(grep -i "ghr size"   $trace_file | sort | uniq | awk '{print $3}' | tr '\n' " ")
#echo "AHRT Sizes:" $(grep -i "ahrt size" $trace_file | sort | uniq | awk '{print $3}' | tr '\n' " ")
#echo "AHRT Asso:" $(grep -i "ahrt asso"  $trace_file | sort | uniq | awk '{print $3}' | tr '\n' " ")
#echo "BTB Sizes:" $(grep -i "btb size"   $trace_file | sort | uniq | awk '{print $3}' | tr '\n' " ")

#grep -i -e DIST -e accuracy trace_analysis.txt | paste -d " "  - - | awk '{printf("%-15s %s\n",$1,$4)}'

