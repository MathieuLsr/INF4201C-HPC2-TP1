#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "utils.h"
#include <stdio.h>
#include <time.h>

int Start_Port_HTTP(int port){

    printf("Port HTTP : %d\n", port) ; 
    // Utilisation de la méthode créé à l'exercice 
    int socket = InitPacketReceive(port) ; 

    if(socket == -1){
        perror("Init failed ") ;
        return -1 ;
    }

    // On boucle à l'infini pour traiter toutes les requêtes tant que le serveur est ON
    while(1){

        char buffer[SIZE_MAX] ;
        // Accepte la connexion d'un nouvel utilisateur
        int fd = acceptSocket(socket) ; 
        printf("New request\n") ;

        // Lis le message dans la socket
        size_t size = readSocket(fd, buffer, SIZE_MAX) ;
        buffer[size] = '\0' ; 

        // Token permettant de récupérer le nom de la page demandée 
        char* token = strtok(buffer, "/") ;
        token = strtok(NULL, "/") ;
        token[strlen(token)-5] = '\0' ;

        // Récupération de la date et mise en forme 
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

        // Ouverture en "append" et insertion de la requête dans le fichier
        FILE *fp;
        fp = fopen ("log_file.log", "a");
        strcat(time_str, " : ") ;
        strcat(time_str, token) ;
        strcat(time_str, "\n") ;
        printf("%s\n", time_str) ;
        fprintf(fp, time_str) ;
        fclose(fp) ; 

        // Récupération du fichier demandé par l'utilisateur (ex : index.html)
        FILE *file_index;
        char buff_file[SIZE_MAX] ;
        file_index = fopen (token, "r");
        // Lecture du fichier pour pouvoir ensuite l'intégrer dans la requête 
        fread(buff_file, SIZE_MAX, 1, file_index) ;
        fclose(file_index) ; 

        // Buffer pour la réponse
        char resp[SIZE_MAX] ;

        /* On intègre un début de requête HTTP qu'on a eu grace aux exercices précédents 
           La date ne correspond pas et la taille de la requête est légèrement plus grande 
           Or si nous voulions faire un vrai serveur, il aurait fallu rendre tous ces paramètres dynamiques
           mais ce n'est pas l'objectif réel de ce TP. */
        strcpy(resp, "HTTP/1.1 400 Bad Request\nDate: Tue, 06 Dec 2022 12:42:57 GMT\nServer: Apache/2.4.51 (Win64)\nContent-Length: 226\nConnection: close\nContent-Type: text/html; charset=iso-8859-1\n\n") ;
        /* On copie ensuite le fichier lu 
         Les deux retours à la ligne sont intégrés au fichier mais sinon 
         il est important de finir un requête HTTP par 2 retours à la ligne. */
        strcat(resp, buff_file) ;

        // Enfin, nous écrivons cette requête dans la socket envoyé par l'utilisateur
        sendMsg(fd, resp, sizeof(resp)) ;

    }

    return 0 ; 

}

int Start_Port_LOGS(int port){

    // Initialisation du serveur d'écoute
    printf("Port LOGS : %d\n", port) ; 
    int socket = InitPacketReceive(port) ; 

    if(socket == -1){
        perror("Init failed ") ;
        return -1 ;
    }

    while(1){

        char buffer[SIZE_MAX] ;
        // Accepte la connexion d'un nouvel utilisateur
        int fd = acceptSocket(socket) ; 
        printf("New request\n") ;

        /* Lorsqu'il y a 1 message envoyé, ça débloque la fonction bloquante 
        Critique : Le message peut être n'importe quoi et pas seulement une requête HTTP. 
        Si nous voulons faire un vrai serveur, il aurait été intéressant de traiter 
        la requête HTTP avec un nom d'utilisateur par exemple ou autre. */
        size_t size = readSocket(fd, buffer, SIZE_MAX) ;
        buffer[size] = '\0' ; 
        
        char resp[5012] ;

        // Création de la requête à envoyer
        strcpy(resp, "HTTP/1.1 400 Bad Request\nDate: Tue, 06 Dec 2022 12:42:57 GMT\nServer: Apache/2.4.51 (Win64)\nContent-Length: 226\nConnection: close\nContent-Type: text/html; charset=iso-8859-1\n\n") ;
        strcat(resp, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\"><html><head><title>Request succeed</title></head><body><h1>ABC Request</h1><p>") ;
        
        // Ouverture et lecture du fichier log 
        FILE *file_log;
        file_log = fopen ("log_file.log", "r");
        char str[20] ;
        while (fgets(str, 20, file_log) != NULL) {
            printf("> str : %s\n", str) ;
            // Ajout des logs dans le code HTML
            strcat(resp, str) ;
        }
        fclose(file_log) ; 

        // Fin de la page HTML
        strcat(resp, "<br /></p></body></html>") ;
        strcat(resp, "\r\n\r\n\0") ;
        printf("Resp :\n%s\n", resp) ;

        // Envoie de la requête 
        sendMsg(fd, resp, strlen(resp)) ;

    }

    
    return 0 ; 

}


int main(int argc, char const *argv[])
{
    
    // 2 Arguments obligatoires
    if(argc != 3){
        printf("Incorrect : ./main [port_http] [port_logs]\n") ;
        return 0 ; 
    }

    // Cast des 2 ports mis en arguments
    int port_http = atoi(argv[1]) ; 
    int port_logs = atoi(argv[2]) ; 

    // Nous créons un processus pour faire une écoute parallèle 
    if(fork() == 0){
        // Lancement du serveur pour les logs
        int result = Start_Port_LOGS(port_logs) ;     
        return 0 ; 
    }

    // Lancement du serveur pour le site
    int result = Start_Port_HTTP(port_http) ; 
    

    wait(NULL) ;

    return 0;
}
