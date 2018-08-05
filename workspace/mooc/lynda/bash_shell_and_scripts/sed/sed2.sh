#!/bin/bash

echo "Command line vars are ..."
while 
[[ $# -gt 0 ]]
do
  echo $1
  shift
done

