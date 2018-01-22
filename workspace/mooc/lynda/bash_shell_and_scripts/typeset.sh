#!/bin/bash

function f1 
{
  typeset x
  x=7  # Local variable
  y=8  # Global variable
}

x=1
y=2

echo x = $x
echo y = $y

f1

echo x = $x
echo y = $y
