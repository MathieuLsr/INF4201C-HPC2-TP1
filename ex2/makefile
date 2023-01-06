all: main utils.o

######################################################################

main: main.o utils.o 
	gcc main.o utils.o -o main

main.o: main.c utils.c # client.h 
	gcc -c main.c -o main.o

######################################################################

utils.o: utils.c utils.h
	gcc -c utils.c -o utils.o