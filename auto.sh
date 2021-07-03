#!/bin/bash

if [ "$1" == "" ] 
then

make
for n in {1..3};
do
    ./verilogopt test/testcase$n/original.v test/testcase$n/optimized.v
    ./eval test/testcase$n/original.v test/testcase$n/optimized.v
    echo finish testcase$n
    echo
done

elif [ "$1" == "eval" ] 
then

for n in {1..3};
do
    ./eval test/testcase$n/original.v test/testcase$n/optimized.v
    echo finish testcase$n
    echo
done

else

make
./verilogopt test/$1/original.v test/$1/optimized.v
./eval test/$1/original.v test/$1/optimized.v
echo finish $1

fi