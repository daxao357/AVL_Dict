CC = g++
CFLAGS = -Wall -std=c++11

all: main

run:
	./main

main: main.o AVL.o
	$(CC) $(CFLAGS) -o main main.o AVL.o

main.o: main.cpp AVL.hpp
	$(CC) $(CFLAGS) -c main.cpp

AVL.o: AVL.cpp AVL.hpp
	$(CC) $(CFLAGS) -c AVL.cpp

clean:
	rm -f main main.o AVL.o
