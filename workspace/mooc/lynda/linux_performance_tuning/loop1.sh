#!/bin/bash

while true
do
  x=$((x+1))
  pwd > /dev/null
  if [ $x -gt 5000 ] 
  then
    exit
  fi
done
