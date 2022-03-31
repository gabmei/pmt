# compilation flags
CC = g++
CFLAGS = -c -std=c++17 -O2 -Wall

all: pmt

pmt: pmt.o kmp.o shift_or.o sellers.o ukkonen.o
	$(CC) pmt.o kmp.o shift_or.o sellers.o ukkonen.o -o pmt

pmt.o: ./src/pmt.cpp
	$(CC) $(CFLAGS) ./src/pmt.cpp

kmp.o: ./src/kmp.cpp
	$(CC) $(CFLAGS) ./src/kmp.cpp

shift_or.o: ./src/shift_or.cpp
	$(CC) $(CFLAGS) ./src/shift_or.cpp

sellers.o: ./src/sellers.cpp
	$(CC) $(CFLAGS) ./src/sellers.cpp

ukkonen.o: ./src/ukkonen.cpp
	$(CC) $(CFLAGS) ./src/ukkonen.cpp

clean:
	rm *.o pmt