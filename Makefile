# compilation flags
CC = g++
CFLAGS = -c -std=c++17 -O2 -Wall

all: pmt

pmt: pmt.o kmp.o shift_or.o
	$(CC) pmt.o kmp.o shift_or.o -o pmt

pmt.o: ./src/pmt.cpp
	$(CC) $(CFLAGS) ./src/pmt.cpp

kmp.o: ./src/kmp.cpp
	$(CC) $(CFLAGS) ./src/kmp.cpp

shift_or.o: ./src/shift_or.cpp
	$(CC) $(CFLAGS) ./src/shift_or.cpp

clean:
	rm *.o pmt