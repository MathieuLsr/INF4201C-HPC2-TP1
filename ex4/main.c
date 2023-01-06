#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "utils.h"
#include <stdio.h>
#include <time.h>

int Start_Port_HTTP(int port){

    printf("Port HTTP : %d\n", port) ; 
    int socket = InitPacketReceive(port) ; 

    if(socket == -1){
        perror("Init failed ") ;
        return -1 ;
    }

    while(1){

        char buffer[SIZE_MAX] ;
        int fd = acceptSocket(socket) ; 
        printf("New request\n") ;
        //printf("fd : %d\n", fd) ; 

        size_t size = readSocket(fd, buffer, SIZE_MAX) ;
        buffer[size] = '\0' ; 
        //printf("%s", buffer) ; 

        char* token = strtok(buffer, "/") ;
        //printf("%s\n", token) ;
        token = strtok(NULL, "/") ;
        token[strlen(token)-5] = '\0' ;
        //printf("%s\n", token) ;

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char time_str[64] ;
        char day[3], month[3], hour[3], min[3] ;
        sprintf(day, "%d", tm.tm_mday);
        sprintf(month, "%d", tm.tm_mon+1);
        sprintf(hour, "%d", tm.tm_hour);
        sprintf(min, "%d", tm.tm_min);
        strcpy(time_str, day) ;
        strcat(time_str, "/") ;
        strcat(time_str, month) ;
        strcat(time_str, " ") ;
        strcat(time_str, hour) ;
        strcat(time_str, "h") ;
        strcat(time_str, min) ;
        FILE *fp;
        fp = fopen ("log_file.log", "a");
        strcat(time_str, " : ") ;
        strcat(time_str, token) ;
        strcat(time_str, "\n") ;
        printf("%s\n", time_str) ;
        fprintf(fp, time_str) ;
        fclose(fp) ; 

        FILE *file_index;
        char buff_file[SIZE_MAX] ;
        file_index = fopen (token, "r");
        fread(buff_file, SIZE_MAX, 1, file_index) ;
        //printf(">> \n%s", buff_file) ;
        fclose(file_index) ; 

        char resp[SIZE_MAX] ;

        strcpy(resp, "HTTP/1.1 400 Bad Request\nDate: Tue, 06 Dec 2022 12:42:57 GMT\nServer: Apache/2.4.51 (Win64)\nContent-Length: 226\nConnection: close\nContent-Type: text/html; charset=iso-8859-1\n\n") ;
        strcat(resp, buff_file) ;
        //printf("----\n") ;
        //printf("%s\n", resp) ;

        sendMsg(fd, resp, sizeof(resp)) ;

    }

    // Addr machine, date, nom fichier demandé 




    return 0 ; 

}

int Start_Port_LOGS(int port){

    printf("Port LOGS : %d\n", port) ; 
    int socket = InitPacketReceive(port) ; 

    if(socket == -1){
        perror("Init failed ") ;
        return -1 ;
    }

    while(1){

        char buffer[SIZE_MAX] ;
        int fd = acceptSocket(socket) ; 
        printf("New request\n") ;
        //printf("fd : %d\n", fd) ; 

        size_t size = readSocket(fd, buffer, SIZE_MAX) ;
        buffer[size] = '\0' ; 
        
        char resp[5012] ;

        strcpy(resp, "HTTP/1.1 400 Bad Request\nDate: Tue, 06 Dec 2022 12:42:57 GMT\nServer: Apache/2.4.51 (Win64)\nContent-Length: 226\nConnection: close\nContent-Type: text/html; charset=iso-8859-1\n\n") ;
        strcat(resp, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\"><html><head><title>Request succeed</title></head><body><h1>ABC Request</h1><p>") ;
        
        FILE *file_log;
        //char buffer_file[SIZE_MAX] ;
        file_log = fopen ("log_file.log", "r");
        //size_t size_file = fread(buffer_file, SIZE_MAX, 1, file_log) ;
        char str[20] ;
        while (fgets(str, 20, file_log) != NULL) {
            printf("> str : %s\n", str) ;
            strcat(resp, str) ;
        }
        fclose(file_log) ; 

        strcat(resp, "<br /></p></body></html>") ;
        strcat(resp, "\0") ;
        printf("Resp :\n%s\n", resp) ;

        sendMsg(fd, resp, strlen(resp)) ;
        
        /*
        strcat(resp, buff_file) ;
        strcat(resp, "<br /></p></body></html>") ;

        printf(">>%s<<\n", resp) ;
        */


    }

    
    return 0 ; 

}


int main(int argc, char const *argv[])
{
    
    
    if(argc != 3){
        printf("Incorrect : ./main [port_http] [port_logs]\n") ;
        return 0 ; 
    }

    int port_http = atoi(argv[1]) ; 
    int port_logs = atoi(argv[2]) ; 

    if(fork() == 0){
        int result = Start_Port_LOGS(port_logs) ;     
        return 0 ; 
    }

    int result = Start_Port_HTTP(port_http) ; 
    

    wait(NULL) ;

    return 0;
}
