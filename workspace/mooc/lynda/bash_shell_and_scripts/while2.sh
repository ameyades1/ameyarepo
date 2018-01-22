#!/bin/bash

#Read a file line by line. 
while 
  read a b
do 
  echo a = $a, b = $b
done <$1
