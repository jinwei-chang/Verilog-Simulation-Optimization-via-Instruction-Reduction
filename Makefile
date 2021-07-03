CC := g++
# CC := /opt/rh/devtoolset-6/root/usr/bin/g++

CFLAGS := -std=c++11 -O2 -static

compile:
	$(CC) $(CFLAGS) -o verilogopt src/main.cpp
	$(CC) $(CFLAGS) -o eval src/eval.cpp