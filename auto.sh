#!/bin/bash

make

if [ "$1" != "" ] 
then

./verilogopt test/$1/original.v test/$1/optimized.v
echo finish $1

fi