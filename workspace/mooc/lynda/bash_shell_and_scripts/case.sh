#!/bin/bash

echo "Do you want to rule the world ? Y/N"
read ans

case $ans in 
	yes|YES|y|Y ) echo "Will do!";;
	n*|N* ) echo "Will NOT do!!";;
	*) echo "Oops!";;
esac

if test -f myfile
then
	echo myfile exists!
else
	echo myfile does not exist
fi

if [[ -f myfile && $(cat myfile | wc -l) -gt 1 ]]
then
	echo myfile has more than 1 lines
fi

if grep -q important myfile
then
	echo myfile has important stuff
else
	echo myfile does NOT have important stuff
fi

echo "All executable files"

for k in *
do
  if [[ -x $k ]]
  then
    echo $k is executable
  fi
done



