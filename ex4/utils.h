#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h> 

#undef SIZE_MAX
#define SIZE_MAX 500

int InitPacketReceive(int PORT) ;

int acceptSocket(int socket) ; 
size_t readSocket(int accepted_socket, char* buffer, int size) ; 

int sendMsg(int sockfd, char *msg, size_t msgSize) ;
int SendNewPacket_TCP(const char* SERVER, int PORT, char* message, int size) ; 
int SendNewPacket_UDP(const char* SERVER, int PORT, char* message, int size) ; 