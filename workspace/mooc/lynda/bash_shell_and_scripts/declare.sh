#!/bin/bash

declare -l lstring="ABCdef"    #Lowercase string
declare -u ustring="ABDdef"    #Uppercase string
declare -r readonly="Readonly" #Readonly string
declare -a Myarray1            #Array integer indexed
declare -A Myarray2            #Array string indexed, hash, dictionary

echo lstring = $lstring
echo ustring = $ustring

echo readonly = $readonly
readonly = "New Value"
echo readonly = $readonly

Myarray1[2]="Second Value"
echo "Myarray1[2] = ${Myarray1[2]}"

Myarray2["red"]="Ferrari"
echo "Myarray[red] = " ${Myarray2['red']}
