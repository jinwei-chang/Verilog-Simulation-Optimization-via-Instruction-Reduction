#!/bin/bash

if [ "$1" == "" ] 
then
    make eval
    for n in {0..10};
    do
        if [ $n == 6 ] 
        then 
        continue
        fi

        ./verilogopt test/testcase$n/original.v test/testcase$n/optimized.v
        ./eval test/testcase$n/original.v test/testcase$n/optimized.v
        echo finish testcase$n
        echo
    done
elif [ "$1" == "eval" ] 
then
    if [ "$2" == "" ] 
    then
        for n in {0..10};
        do
            if [ $n == 6 ]
            then 
            continue 
            fi

            ./eval test/testcase$n/original.v test/testcase$n/optimized.v
            echo finish testcase$n
            echo
        done
    else
        ./eval test/$2/original.v test/$2/optimized.v
        echo finish $2
        echo
    fi
else

make eval
./verilogopt test/$1/original.v test/$1/optimized.v
./eval test/$1/original.v test/$1/optimized.v
echo finish $1

fi