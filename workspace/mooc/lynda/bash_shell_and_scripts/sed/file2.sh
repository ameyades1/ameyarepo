#!/bin/bash

for i in cfiles/*.c
do
  echo ${i%.c}
done
