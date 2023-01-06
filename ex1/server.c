#include "utils.h"
#include <stdlib.h>

#include <sys/types.h> // pid
#include <unistd.h> // pid

int main(int argc, char const *argv[])
{
    
    if(argc !=  2){
        printf("[ERROR] Arguments manquants : ./server [PORT]\n") ; 
        return -1; 
    } 

    int port_user = atoi(argv[1]);
    printf("[INFO] Port choisi : %d\n", port_user) ;

    int sock = InitPacketReceive(port_user) ;
    if(sock == -1) exit(0) ;

    printf("[INFO] Success init\n") ;

    char message_recu[SIZE_MAX] ;
    message_recu[SIZE_MAX-1] = '\0' ;
    struct sockaddr_in ad_dest ;
    socklen_t size_ad_dest = sizeof(ad_dest) ;

    recvfrom(sock, message_recu, SIZE_MAX, 0, (struct sockaddr* )&ad_dest, &size_ad_dest) ;
    printf("[RECEIVE] %s\n", message_recu) ;

    int pid = getpid() ;
    char *msg2 = malloc(SIZE_MAX + 10);
    sprintf(msg2, "[PORT = %d] [%s]", pid, message_recu);
    printf("[TRY SENDING] %s\n", msg2);
    sendto(sock, msg2, sizeof(msg2), 0, (struct sockaddr* )&ad_dest, size_ad_dest) ;


    return 0;
}
