#!/bin/bash

function hello {
  echo Hello World
  return
  echo Bye World
}

var=$(hello)
echo $var
