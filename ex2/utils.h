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

int InitSocketReceive_TCP(int PORT) ;
size_t readSocket(int socket_server, char buffer[]); 