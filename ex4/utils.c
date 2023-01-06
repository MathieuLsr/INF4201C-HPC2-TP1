#include "utils.h"

/* 
    Identique aux exercices précédents  
    Initilisation d'une socket d'écoute en mode TCP
*/
int InitPacketReceive(int PORT) {


    struct sockaddr_in s_ain;
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    s_ain.sin_family = AF_INET;
    s_ain.sin_addr.s_addr = INADDR_ANY ;
    s_ain.sin_port = htons(PORT);
    memset(s_ain.sin_zero, 0, 8) ;

    if(bind(s, (struct sockaddr *)&s_ain, sizeof(s_ain)) == -1) {
        perror("Bind failed : ") ; 
        return -1;
    }
    
    if(listen(s, 5) == -1) {
        perror("Listen failed : ") ;  
        return -1;
    }
    
    return s ;

}

/*
    Fonction permettant d'accepter la connexion d'un nouvel utilisateur
*/
int acceptSocket(int socket){

    struct sockaddr_in c_ain;   
    socklen_t size_addr = sizeof(c_ain);  

    return accept(socket, (struct sockaddr *)&c_ain, (socklen_t*)&size_addr);
    
}

/*
    Fonction qui permet de lire un message dans une socket.
    Pratique de créer une fonction commune si nous voulons 
    appliquer un changement sur toutes nos lectures de socket.
*/
size_t readSocket(int accepted_socket, char* buffer, int size){
    return read(accepted_socket, buffer, size);
}


/*
    Écriture d'un message dans le file descriptor de la socket
    avec traitement des erreurs.
*/
int sendMsg(int sockfd, char *msg, size_t msgSize)
{

    if (write(sockfd, msg, msgSize) < 0) {
        perror("error writing to socket");
        return -1;
    }

    return 0;
}
