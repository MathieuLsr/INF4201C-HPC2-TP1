#include "utils.h"

int main(int argc, char const *argv[])
{
    

    if(argc <  2){
        printf("[ERROR] Arguments manquants : ./client [PORT]\n") ; 
        return -1; 
    }

    int port_user = atoi(argv[1]);
    int socket = InitPacketReceive(port_user) ; 

    char buffer[SIZE_MAX] ; 
    readSocket(socket, buffer) ; 
    printf("Is Accepted : .%s.\n", buffer) ; 



    return 0;
}
