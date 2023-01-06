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

size_t readSocket(int socket, char* buffer) ; 

int sendMsg(int sockfd, char *msg, size_t msgSize) ;
int SendNewPacket_TCP(const char* SERVER, int PORT, char* message, int size) ; 
