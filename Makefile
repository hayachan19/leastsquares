CC=g++
CFLAGS=-std=c++14

all: main

main: vector.o matrix.o LU.o main.o
	$(CC) $(CFLAGS) vector.o matrix.o LU.o main.o -o main
	
vector.o: vector.cpp
	$(CC) -c vector.cpp
	
matrix.o: matrix.cpp
	$(CC) -c matrix.cpp
	
LU.o: LU.cpp
	$(CC) -c LU.cpp
	
main.o: main.cpp
	$(CC) -c main.cpp
	
clean:
	rm *o main