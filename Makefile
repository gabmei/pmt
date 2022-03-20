# compilation flags
CC = g++
CFLAGS = -c -std=c++17 -O2

all: pmt

pmt: pmt.o kmp.o
	$(CC) pmt.o kmp.o -o pmt

pmt.o: ./src/pmt.cpp
	$(CC) $(CFLAGS) ./src/pmt.cpp

kmp.o: ./src/kmp.cpp
	$(CC) $(CFLAGS) ./src/kmp.cpp
