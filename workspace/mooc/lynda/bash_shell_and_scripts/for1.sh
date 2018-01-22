#!/bin/bash

for i in dog cat elephant
do
  echo i = $i
done

for num in $(seq 1 5)
do
  echo num = $num
done

for char in {A..M}
do
  echo char = $char
done

for num2 in {3..6}
do 
  echo num2 = $num2
done

for j in *.sh 
do
  echo file name is $j
done

for k in $(find .  -iname *.sh)
do
  echo file name2 is $k
done

for f in $(find /etc 2>/dev/null | grep grub )
do
  echo grub named things are $f
done
