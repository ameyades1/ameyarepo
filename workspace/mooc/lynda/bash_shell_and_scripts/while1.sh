#!/bin/bash

x=0;
while ((x<10)) 
do
	echo loop $x;
	date > data.$x
	((x=x+1))
done


