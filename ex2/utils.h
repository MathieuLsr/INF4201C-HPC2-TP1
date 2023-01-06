#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h> 

#define SIZE_MAX 500

int InitPacketReceive(int PORT) ;
int SendNewPacket(const char* SERVER, int PORT, const char* message, int size) ; 
int readSocket(int socket_server, char buffer[]); 