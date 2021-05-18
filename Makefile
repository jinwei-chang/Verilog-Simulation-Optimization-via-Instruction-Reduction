CC := g++
CFLAGS := -std=c++11 -O2 -static

compile:
	$(CC) $(CFLAGS) -o verilogopt src/main.cpp