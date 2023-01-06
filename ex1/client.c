#include <stdlib.h>
#include "utils.h"
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    
    if(argc <  4){
        printf("[ERROR] Arguments manquants : ./client [NAME] [PORT] [MESSAGE]\n") ; 
        return -1; 
    }

    const char* name = argv[1] ; 
    int port_user = atoi(argv[2]);
    
    char msg[500] ; 

    sprintf(msg, "[PID = %d]", getpid());

    for(int i=3 ; i<argc ; i++){
        sprintf(msg, "%s %s", msg, argv[i]);
    }

    printf("[TRY SEND] (%d) %s\n", sizeof(msg), msg) ;

    int socket = SendNewPacket(name, port_user, msg, sizeof(msg)) ; 
    
    printf("fd Socket : %d\n", socket) ;
    if(socket == -1){
        printf("[ERROR] Socket not send\n") ; 
        return -1; 
    }
    
    printf("[INFO] Envoyé \n") ; 

    char message_recu[SIZE_MAX] ;
    message_recu[SIZE_MAX-1] = '\0' ;
    struct sockaddr_in ad_dest ;
    socklen_t size_ad_dest = sizeof(ad_dest) ;

    recvfrom(socket, message_recu, SIZE_MAX, 0, (struct sockaddr* )&ad_dest, &size_ad_dest) ;
    printf("[RECEIVE] %s\n", message_recu) ;

    return 0;
}
