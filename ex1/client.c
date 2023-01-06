#include <stdlib.h>
#include "utils.h"
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    
    // Nécessite au minimum 3 arguments obligatoires
    if(argc <  4){
        printf("[ERROR] Arguments manquants : ./client [NAME] [PORT] [MESSAGE]\n") ; 
        return -1; 
    }

    const char* name = argv[1] ; 
    // Cast du port en int
    int port_user = atoi(argv[2]);
    
    // Création d'un buffer
    char msg[500] ; 
    // Method qui permet de convertir un int en char* (string)
    sprintf(msg, "[PID = %d]", getpid());

    // Boucle sur tous les arguments pour pouvoir envoyer la phrase en entier
    for(int i=3 ; i<argc ; i++){
        // Ici, il aurait mieux fallu utiliser strcat pour le rendre fonctionnel
        sprintf(msg, "%s %s", msg, argv[i]);
    }

    printf("[TRY SEND] (%d) %s\n", sizeof(msg), msg) ;

    // Envoie un message (msg) sur le server (name) via le port (port_user)
    // Renvoie le file descriptor de la socket envoyée
    // Voir utils.c : SendNewPacket() pour plus de détails
    int socket = SendNewPacket(name, port_user, msg, sizeof(msg)) ; 
    
    printf("fd Socket : %d\n", socket) ;
    // Si la socket n'a pas réussi à être créée
    if(socket == -1){
        printf("[ERROR] Socket not send\n") ; 
        return -1; 
    }
    
    printf("[INFO] Envoyé \n") ; 

    // Création d'un buffer & d'une sockaddr pour la réception 
    char message_recu[SIZE_MAX] ;
    message_recu[SIZE_MAX-1] = '\0' ;
    struct sockaddr_in ad_dest ;
    socklen_t size_ad_dest = sizeof(ad_dest) ;

    // Attente de réception passive via la socket envoyée
    recvfrom(socket, message_recu, SIZE_MAX, 0, (struct sockaddr* )&ad_dest, &size_ad_dest) ;
    printf("[RECEIVE] %s\n", message_recu) ;

    return 0;
}
