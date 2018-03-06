#!/bin/bash

exec 7< myfile1 #File descriptor 7 for reading myfile1
exec 8> myfile2 #File descriptor 8 for writing myfile2

lsof -p $$

exec 7>&- # Close descriptor
exec 8>&- 

lsof -p $$
