# for local testing
CC := g++
CFLAGS := -std=c++11 -O2 -static

# for contest setting
# CC := /opt/rh/devtoolset-6/root/usr/bin/g++
# CFLAGS := -std=c++11 -O2

contest:
	$(CC) $(CFLAGS) -o verilogopt main.cpp

compile:
	$(CC) $(CFLAGS) -o verilogopt src/main.cpp

eval: compile
	$(CC) $(CFLAGS) -o eval src/eval.cpp