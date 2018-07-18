#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "damier.c"
	
#define BUFSIZE 1024		
int Damier2[10][10];



void send_recv(int i, int sockfd)
{
	char send_buf[BUFSIZE] = "Envoyé info";
	char recv_buf[BUFSIZE];
	int nbyte_recvd;



// --------------- Afficher damier -----------------------	
	nbyte_recvd = recv(sockfd, recv_buf, BUFSIZE, 0);
	recv_buf[nbyte_recvd] = '\0';                	
	if(damierIsDisplay == 0)
		if (strcmp ("Begin", recv_buf) == 0) {				
			printf("Nouvelle Partie !\n");				
			initialisation_plateau(Damier2);
			configuration_piont(Damier2);
			afficher_plateau(Damier2);
			damierIsDisplay = 1; 			
		}
	}
// ---------------------------------------------------------
	

//----------- Afficher le jeu au 1er joeur -----------------
	

	if (strcmp ("Start", recv_buf) == 0) {				
		jeu(1);
		printf("Damier affiché\n");	
		send(sockfd, send_buf, strlen(send_buf), 0);	

	else if(i > 0){
		nbyte_recvd = recv(sockfd, recv_buf, BUFSIZE, 0);
		recv_buf[nbyte_recvd] = '\0';
		printf("%s\n" , recv_buf);
	}

   

//----------------------------------------------------------
 
	
     
	//if (i == 0){
				
		//fgets(send_buf, BUFSIZE, stdin);
		//send_buf[] = "PlayOne";	
	//	printf("Message : %s", send_buf);
	//	if (strcmp(send_buf , "quit\n") == 0) {
	//		exit(0);
	//	}
		//printf("MessageOne : %s\n",recv_buf);
               //	if (strcmp ("Me\n", send_buf) == 0) {	   														
			
		//}	
    			
		      				
		/*if (strcmp ("PlayTwo\n", send_buf) == 0) {						
			printf("MessageTwo : %s\n",recv_buf);		      	
			jeu(2);
			
		}*/
		 
		//else{
		//	jeu(1);
		//	send(sockfd, "OK", strlen("OK"), 0);	
			//send(sockfd, send_buf, strlen(send_buf), 0);
		//	}
		
	//}else {
		
	//	jeu(1);
	//	send(sockfd, "OK", strlen("OK"), 0);

		//if (strcmp ("OK", recv_buf) == 0) {				
		//	printf("Nouvelle Partie !\n");				
			
		//}


					
				
	//		fflush(stdout);

	//}

}
		
		
void connect_request(int *sockfd, struct sockaddr_in *server_addr)
{
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(4950);
	server_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr->sin_zero, '\0', sizeof server_addr->sin_zero);
	
	if(connect(*sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
}
	
int main()
{
	int sockfd, fdmax, i;
	struct sockaddr_in server_addr;
	fd_set master;
	fd_set read_fds;
	
	connect_request(&sockfd, &server_addr);
	FD_ZERO(&master);
        FD_ZERO(&read_fds);
        FD_SET(0, &master);
        FD_SET(sockfd, &master);
	fdmax = sockfd;
	
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		
		for(i=0; i <= fdmax; i++ )
			if(FD_ISSET(i, &read_fds))
				send_recv(i, sockfd);
	}
	printf("Le joueur à quitté \n");
	close(sockfd);
	return 0;
}
