#!/bin/bash

for f in /usr/bin/*
do
  if [[ $(strings $f | grep -q "unable to fork") ]]
  then
    echo $f unable to fork
  fi
done
