#!/bin/bash

make

if [ "$1" != "" ] 
then

./verilogopt test/$1/original.v test/$1/optimized.v
./eval test/$1/original.v test/$1/optimized.v
echo finish $1

else

for n in {1..3};
do
./verilogopt test/testcase$n/original.v test/testcase$n/optimized.v
./eval test/testcase$n/original.v test/testcase$n/optimized.v
echo finish testcase$n
echo
done

fi