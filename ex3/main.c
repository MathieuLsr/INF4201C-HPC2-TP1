#include "utils.h"

int main(int argc, char const *argv[])
{
    
    // 3 Arguments obligatoire
    if(argc <  4){
        printf("[ERROR] Arguments manquants : ./client [NAME] [PORT] [FILE_NAME]\n") ; 
        return -1; 
    }

    const char* name = argv[1] ; 
    int port_user = atoi(argv[2]);
    const char* file_name = argv[3] ; 

    //char message[] = "GET /index.html HTTP/1.1\nHost: localhost:4545\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\nAccept-Encoding: gzip, deflate, br\nConnection: keep-alive\nUpgrade-Insecure-Requests: 1\nSec-Fetch-Dest: document\nSec-Fetch-Mode: navigate\nSec-Fetch-Site: none\nSec-Fetch-User: ?1\r\n\r\n" ;
    //char message[] = "GET / HTTP/1.0\r\n\r\n" ;

    // Simulation d'une requête HTTP 
    char message[] = "GET /index.html HTTP/1.0\r\n\r\n" ; 

    // Envoie de la socket en mode TCP 
    // Voir utils.c : SendNewPacket_TCP()
    int socket = SendNewPacket_TCP(name, port_user, message, strlen(message)) ;

    printf("fd Socket : %d\n", socket) ;
    // Traitement des erreurs
    if(socket == -1){
        printf("[ERROR] Socket not send\n") ; 
        return -1; 
    }
    
    printf("[INFO] Envoyé \n") ; 

    // Buffer pour la réponse HTTP
    char message_recu[SIZE_MAX] ;

    // Attente de la réponse du serveur HTTP
    size_t r = readSocket(socket, message_recu) ;
    if(r == -1){
        printf("[ERROR] Read()\n") ; 
        exit(0) ; 
    } 

    message[r-2] = '\0' ; 
    printf("[RECEIVE] %s\n", message_recu) ;

    return 0;
}

// Tester avec pc5256b.lan.esiee.fr

