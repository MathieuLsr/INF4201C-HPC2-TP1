#include "utils.h"
#include <stdlib.h>

#include <sys/types.h> // pid
#include <unistd.h> // pid

int main(int argc, char const *argv[])
{
    
    // 1 argument obligatoire (PORT)
    if(argc !=  2){
        printf("[ERROR] Arguments manquants : ./server [PORT]\n") ; 
        return -1; 
    } 

    // Cast en int 
    int port_user = atoi(argv[1]);
    printf("[INFO] Port choisi : %d\n", port_user) ;

    // Initialise le server en mode UDP et retourne le file descriptor
    // Voir utils.c : InitPacketReceive() pour plus de détails
    int sock = InitPacketReceive(port_user) ;
    if(sock == -1) exit(0) ;

    printf("[INFO] Success init\n") ;

    // Créer un buffer
    char message_recu[SIZE_MAX] ;
    message_recu[SIZE_MAX-1] = '\0' ;
    // sockaddr de réception pour le recvfrom()
    struct sockaddr_in ad_dest ;
    socklen_t size_ad_dest = sizeof(ad_dest) ;

    // On attend passivement que quelqu'un envoie un packet sur notre port
    recvfrom(sock, message_recu, SIZE_MAX, 0, (struct sockaddr* )&ad_dest, &size_ad_dest) ;
    // Affichage du message lorsqu'on l'a reçu
    printf("[RECEIVE] %s\n", message_recu) ;

    // Récupère le PID du processus
    int pid = getpid() ;
    
    // Prépare le message à envoyer en retour au client
    char *msg2 = malloc(SIZE_MAX + 10);
    sprintf(msg2, "[PORT = %d] [%s]", pid, message_recu);
    printf("[TRY SENDING] %s\n", msg2);

    // Envoie du message via le packet qui a été reçu 
    sendto(sock, msg2, sizeof(msg2), 0, (struct sockaddr* )&ad_dest, size_ad_dest) ;


    return 0;
}
