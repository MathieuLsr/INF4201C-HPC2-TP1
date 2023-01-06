all: client server utils.o

######################################################################

client: client.o utils.o 
	gcc client.o utils.o -o client

client.o: client.c utils.c # client.h 
	gcc -c client.c -o client.o

######################################################################


server: server.o utils.o 
	gcc server.o utils.o -o server

server.o: server.c utils.c # server.h 
	gcc -c server.c -o server.o

######################################################################

utils.o: utils.c utils.h
	gcc -c utils.c -o utils.o