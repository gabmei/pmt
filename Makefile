# compilation flags
CC = g++
CFLAGS = -c -std=c++17 -O2 -Wall

all: pmt

pmt: pmt.o kmp.o shift_or.o sellers.o ukkonen.o
	$(CC) ./bin/pmt.o ./bin/kmp.o ./bin/shift_or.o ./bin/sellers.o ./bin/ukkonen.o -o ./bin/pmt

pmt.o: ./src/pmt.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) ./src/pmt.cpp -o ./bin/pmt.o

kmp.o: ./src/kmp.cpp
	$(CC) $(CFLAGS) ./src/kmp.cpp -o ./bin/kmp.o

shift_or.o: ./src/shift_or.cpp
	$(CC) $(CFLAGS) ./src/shift_or.cpp -o ./bin/shift_or.o

sellers.o: ./src/sellers.cpp
	$(CC) $(CFLAGS) ./src/sellers.cpp -o ./bin/sellers.o

ukkonen.o: ./src/ukkonen.cpp
	$(CC) $(CFLAGS) ./src/ukkonen.cpp -o ./bin/ukkonen.o

clean:
	rm ./bin/*.o ./bin/pmt