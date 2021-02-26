#Author: Daniel Polak
CC=g++
CFLAGS= -std=c++11 -pthread -fopenmp


#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

BUILD: TwinPrime.o
	$(CC) -o twinPrimes TwinPrime.o $(CFLAGS) $(DEBUGFLAGS)
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o

INSTALL:
	cp ./main ~/bin/
