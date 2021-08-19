#!/bin/bash

if [ "$1" == "" ] 
then

make eval
for n in {0..5};
do
    ./verilogopt test/testcase$n/original.v test/testcase$n/optimized.v
    ./eval test/testcase$n/original.v test/testcase$n/optimized.v
    echo finish testcase$n
    echo
done

elif [ "$1" == "eval" ] 
then

for n in {0..5};
do
    ./eval test/testcase$n/original.v test/testcase$n/optimized.v
    echo finish testcase$n
    echo
done

else

make eval
./verilogopt test/$1/original.v test/$1/optimized.v
./eval test/$1/original.v test/$1/optimized.v
echo finish $1

fi