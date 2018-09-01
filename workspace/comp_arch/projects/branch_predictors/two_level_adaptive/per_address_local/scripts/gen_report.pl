#!/usr/bin/perl

# Author: Jared Stark;   Created: Mon Aug 16 11:38:57 PDT 2004
# Description: Script for generating a report of the mispredict rates.

$path = "../results/$ARGV[0]";
system("mkdir -p $path");
print $path ,"\n";

$rat_size = $ARGV[1];

open FILE, ">>", "$path/trace_analysis.txt";
@trace_list = (
   'DIST-FP-1',
   'DIST-FP-2',
   'DIST-FP-3',
   'DIST-FP-4',
   'DIST-FP-5',
   'DIST-INT-1',
   'DIST-INT-2',
   'DIST-INT-3',
   'DIST-INT-4',
   'DIST-INT-5',
   'DIST-MM-1',
   'DIST-MM-2',
   'DIST-MM-3',
   'DIST-MM-4',
   'DIST-MM-5',
   'DIST-SERV-1',
   'DIST-SERV-2',
   'DIST-SERV-3',
   'DIST-SERV-4',
   'DIST-SERV-5'
);

foreach $trace (@trace_list) {
    print $trace, "\n";
    $output = `../src/branch_predictor/predictor ../traces/$trace $rat_size`;
    print $output;
	print FILE $trace, "\n";
	print FILE $output;
    print "\n";
}

