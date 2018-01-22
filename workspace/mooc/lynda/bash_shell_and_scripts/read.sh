#!/bin/bash

export a=first
export b=second
export c=third

echo a = $a b = is $b c = $c

read a b c < data_file
echo a = $a b = $b c = $c
