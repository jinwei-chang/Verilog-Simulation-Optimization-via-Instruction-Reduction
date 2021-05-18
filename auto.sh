#!/bin/bash

make
./verilogopt test/$1/original.v test/$1/optimized.v
echo finish $1