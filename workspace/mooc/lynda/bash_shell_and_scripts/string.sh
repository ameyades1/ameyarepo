#!/bin/bash

s="a string with words"
echo s = $s

sub=${s:4}
echo sub = $sub

sub=${s:4:3}
echo sub = $sub

echo length of s = ${#s}

