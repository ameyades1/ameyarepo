#!/bin/bash

grep -i wrong_cc_bpredicts trace_analysis.txt | awk -v mul=1 '{mul=mul*$9} END {print "Conditional Mispredicts GeoMean = " (mul ^ (1/NR))}'
grep -i wrong_tpredicts trace_analysis.txt | awk -v mul=1 '{mul=mul*$9} END {print "Target Mispredicts GeoMean = " (mul ^ (1/NR))}'

