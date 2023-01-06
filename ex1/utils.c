#include "utils.h"

int InitPacketReceive(int PORT) {

    
    struct sockaddr_in s_ain;
    // Création d'un socket en mode AF_INET et UDP
    // AF_INET désigne le type d'adresses avec lesquels on peut communiquer (IP V4 par défaut)
    // SOCK_DGRAM permet de définir le mode UDP
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    // On paramètre notre sockaddr :
    // Type AF_INET pour IP V4
    s_ain.sin_family = AF_INET;
    // la socket est associée à toutes les @ de la machine (évite utilisation de gethostname())
    s_ain.sin_addr.s_addr = INADDR_ANY ;
    // Si PORT == NULL, ça bind sur un port disponible
    // Sinon, ça force le bind sur le port 
    s_ain.sin_port = htons(PORT);
    // Écrire de 8 zéros supplémentaires pour que sockaddr_in ait la même taille de sockaddr
    memset(s_ain.sin_zero, 0, 8) ;

    // Permet d'associer l'écoute d'une socket à un port 
    if(bind(s, (struct sockaddr *)&s_ain, sizeof(s_ain)) == -1) {
        // Si erreur, on affiche le message par défaut
        perror("Bind failed : ") ; 
        return -1;
    }
    
    return s ;

}


int SendNewPacket(const char* SERVER, int PORT, const char* message, int size){

    struct hostent *hp;
    struct sockaddr_in addr;
    int socket_client; 

    // Permet d'obtenir une adresse ip 
    hp = gethostbyname(SERVER) ;

    // Si l'adresse est invalide
    if(hp == NULL){
        printf("[ERROR] HP est null.\n") ; 
        return -1 ; 
    }

    // Réinitialise la mémoire de la sockadrr à 0
    bzero((char *)&addr, sizeof(addr));
    // Type AF_INET pour IP V4
    addr.sin_family = AF_INET;
    // On copie l'@ récupérée via gethostbyname() dans notre sockaddr
    memcpy(&(addr.sin_addr),  hp->h_addr_list[0], hp->h_length);
    // On configure le port
    addr.sin_port = htons(PORT);
    // Et on complète à nouveau les 8 dernières places mémoires pour avoir la même taille que sockaddr
    memset(addr.sin_zero, 0, 8) ;

    // On crée notre socket en UDP (SOCK_DGRAM)
    socket_client = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t s = sizeof(addr) ;

    // On envoie notre message via notre socket et notre sockaddr
    // Attention, nous n'avons aucune garanti de la réception vu que nous sommes en UDP.
    sendto(socket_client, message, strlen(message), 0, (struct sockaddr*) &addr, s) ;     
    
    return socket_client ; 
}