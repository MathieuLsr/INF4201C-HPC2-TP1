#include "utils.h"

/*
Identique à l'exercice 2 
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
Identique à l'exercice 2 
*/
size_t readSocket(int socket, char* buffer){
        
        struct sockaddr_in c_ain;   
        socklen_t size = sizeof(c_ain);  

        int cd = accept(socket, (struct sockaddr *)&c_ain, (socklen_t*)&size);
        size_t msgSize = read(socket, buffer, SIZE_MAX);
        //printf("Message : %s\n", buffer) ; 
        if (msgSize == -1) {
            close(cd);
            printf("[ERROR] MESSAGE NULL\n");
            return -1 ; 
        }

        return msgSize ;
}


int sendMsg(int sockfd, char *msg, size_t msgSize)
{

    // Écrit dans le file descriptor de la socket
    if (write(sockfd, msg, msgSize) < 0) { 
        // Utilisation de perror en cas d'erreur
        perror("error writing to socket");
        return -1;
    }

    return 0;
}

int SendNewPacket_TCP(const char* SERVER, int PORT, char* str, int size){

    /*
    Paramétrage de la socket : identique à l'exercice précédent 
    */
    struct hostent *hp;
    struct sockaddr_in s_ain;
    int socket_client; 

    hp = gethostbyname(SERVER) ;
    if(hp == NULL){
        printf("[ERROR] Hp null\n") ; 
        return -1 ;
    }


    bzero((char *)&s_ain, sizeof(s_ain));
    s_ain.sin_family = AF_INET;
    memcpy(&(s_ain.sin_addr),  hp->h_addr_list[0], hp->h_length);
    s_ain.sin_port = htons(PORT);
    /***********************************/


    // Création de la socket en mode TCP
    socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Connexion au serveur 
    if(connect(socket_client, (struct sockaddr*) &s_ain, sizeof(s_ain)) == -1 ) {
        perror("connect failed : ") ;
        return -1;
    }

    // Envoie du message et traitement des errors 
    if (sendMsg(socket_client, str, size) != 0) {
        close(socket_client);
        return -1;
    }

    return socket_client ; 
}







