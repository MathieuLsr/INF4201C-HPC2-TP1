#include "utils.h"

int InitPacketReceive(int PORT) {


    struct sockaddr_in s_ain;
    //int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    //bzero((char *)&s_ain, sizeof(s_ain));
    s_ain.sin_family = AF_INET;
    s_ain.sin_addr.s_addr = INADDR_ANY ;
    s_ain.sin_port = htons(PORT);
    memset(s_ain.sin_zero, 0, 8) ;

    if(bind(s, (struct sockaddr *)&s_ain, sizeof(s_ain)) == -1) {
        perror("Bind failed : ") ; 
        return -1;
    }
    /*
    if(listen(s, 5) == -1) {
        perror("Listen failed : ") ;  
        return -1;
    }
    */

   

    return s ;

}


int SendNewPacket(const char* SERVER, int PORT, const char* message, int size){

    struct hostent *hp;
    struct sockaddr_in s_ain;
    unsigned char byte;
    int socket_client; 

    hp = gethostbyname(SERVER) ;

    if(hp == NULL){
        printf("[ERROR] HP est null.\n") ; 
        return -1 ; 
    }

    bzero((char *)&s_ain, sizeof(s_ain));
    s_ain.sin_family = AF_INET;
    memcpy(&(s_ain.sin_addr),  hp->h_addr_list[0], hp->h_length);
    s_ain.sin_port = htons(PORT);
    memset(s_ain.sin_zero, 0, 8) ;

    socket_client = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t s = sizeof(s_ain) ;
    sendto(socket_client, message, strlen(message), 0, (struct sockaddr*) &s_ain, s) ;     
    
    return socket_client ; 
}