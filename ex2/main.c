#include "utils.h"

int main(int argc, char const *argv[])
{
    
    // 1 Argument obligatoire 
    if(argc <  2){
        printf("[ERROR] Arguments manquants : ./client [PORT]\n") ; 
        return -1; 
    }

    // Cast du port 
    int port_user = atoi(argv[1]);

    // Initialisation de notre socket en mode écoute 
    int socket = InitSocketReceive_TCP(port_user) ; 

    // Création d'un buffer 
    char buffer[SIZE_MAX] ; 
    // Attente d'une connexion ainsi que l'envoie d'un message qui est stocké dans buffer
    // Voir utils.c : readSocket() pour les détails
    readSocket(socket, buffer) ; 
    printf("Is Accepted : .%s.\n", buffer) ; 

    return 0;
}
