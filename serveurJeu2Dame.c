#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


int main (void){
 	
	char tailleMessage[100];
 	int socket_fd, connexion, identification, ecoute;
 	struct sockaddr_in servaddr;
 
 	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
 	if(socket != -1){
 		printf("Création d'un socket\n");
 	}else{
		printf("Erreur de création du socket\n");
	}
	
	bzero( &servaddr, sizeof(servaddr));
 
	servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    	servaddr.sin_port = htons(7777);

	identification = bind(socket_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (identification == 0){
		printf("Création d'un port de communication \n");
	}else{
		printf("Erreur impossible de le créer \n");	
	}

	ecoute = listen(socket_fd, 10);
	if(ecoute == 0){
		printf("Création d'une connexion \n");
	}else{
		printf("Impossible d'établir une connexion\n");
	}

	connexion = accept(socket_fd, (struct sockaddr*) NULL, NULL);
	if(connexion == -1){
		printf("Impossible d'avoir une connexion\n");			
	
	}else{
		printf("Attente d'une connexion \n");
	}
 

	
 

}
