#include "utils.h"

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

int readSocket(int socket, char buffer[]){
         
        struct sockaddr_in c_ain;   
        socklen_t size = sizeof(c_ain);  

        int cd = accept(socket, (struct sockaddr *)&c_ain, (socklen_t*)&size);
        size_t msgSize;
        int s = read(cd, buffer, SIZE_MAX);
        buffer[s] = '\0' ;
        //printf("Message : %s\n", buffer) ;

        if (!buffer) {
            close(cd);
            return -1; 
        }

        return 0 ; 
}

int sendMsg(int sockfd, const char *msg, size_t msgSize)
{
    unsigned int convertedNum = htonl(msgSize);
    if (write(sockfd, &convertedNum, sizeof(convertedNum)) < 0) {
        perror("error writing to socket");
        return -1;
    }

    if (write(sockfd, msg, msgSize) < 0) {
        perror("error writing to socket");
        return -1;
    }

    return 0;
}


int SendNewPacket(const char* SERVER, int PORT, const char* message, int size){

    struct hostent *hp;
    struct sockaddr_in s_ain;
    unsigned char byte;
    int socket_client; 

    hp = gethostbyname(SERVER) ;
    bzero((char *)&s_ain, sizeof(s_ain));
    s_ain.sin_family = AF_INET;
    memcpy(&(s_ain.sin_addr),  hp->h_addr_list[0], hp->h_length);
    s_ain.sin_port = htons(PORT);

    socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(connect(socket_client, (struct sockaddr*) &s_ain, sizeof(s_ain)) == -1 ) {
        perror("Failed to connect : ") ; 
        return -1;
    }


    if (sendMsg(socket_client, message, size) != 0) {
        close(socket_client);
        return 1;
    }
    //printf("%s Send is done \n", "[PREFIX]");


    return socket_client ; 
}