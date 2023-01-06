#include "utils.h"


/*
    Fonction permettant d'initialiser une socket TCP en mode écoute
    Fonction quasiment similaire à celle d'initialisation UDP
*/
int InitSocketReceive_TCP(int PORT) {
    

    struct sockaddr_in s_ain;
    // SOCK_STREAM : Protocol pour le mode TCP
    // IPPROTO_TCP : En mode TCP
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Paramétrage par "défaut" 
    s_ain.sin_family = AF_INET;
    s_ain.sin_addr.s_addr = INADDR_ANY ;
    s_ain.sin_port = htons(PORT);
    memset(s_ain.sin_zero, 0, 8) ;

    // Bind de la socket avec la sockaddr
    if(bind(s, (struct sockaddr *)&s_ain, sizeof(s_ain)) == -1) {
        perror("Bind failed : ") ; 
        return -1;
    }
    
    // Fonction spécifique au mode TCP
    // Permet d'attendre la requête de connexion d'un client 
    // 5 est le nombre de connexions pendantes
    if(listen(s, 5) == -1) {
        perror("Listen failed : ") ;  
        return -1;
    }
    
    return s ;

}

size_t readSocket(int socket, char* buffer){
        
        // sockaddr de réception 
        struct sockaddr_in c_ain;   
        socklen_t size = sizeof(c_ain);  

        // Attente passive & fonction bloquante : accepte la connexion d'un client
        int cd = accept(socket, (struct sockaddr *)&c_ain, (socklen_t*)&size);

        // Réception et lecture du message dans la file descriptor de la socket 
        // out dans le buffer mis en argument
        size_t msgSize = read(socket, buffer, SIZE_MAX);
        //printf("Message : %s\n", buffer) ; 
        if (msgSize == -1) {
            close(cd);
            printf("[ERROR] MESSAGE NULL\n");
            return -1 ; 
        }

        return msgSize ;
}
