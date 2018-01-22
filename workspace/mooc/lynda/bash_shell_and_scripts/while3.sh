#!/bin/bash

#Print owner of each file in the current folder

ls -l | while 
  read a b c d
  do
    echo owner is $c 
  done 
