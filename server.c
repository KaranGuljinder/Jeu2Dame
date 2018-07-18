#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "damier.c";
	
#define PORT 4950
#define BUFSIZE 1024
extern int CPT = 0;
extern int CLIENT_MAX = 2;
extern char *send_buf = "Begin";
extern char *send_buf1 = "Start";
extern int lobby[5][5] = {{0}};
extern int partie = 0;
extern int joueur = 0;
extern int start = 0;
extern int start1 = 0;



void send_to_all(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master)
{
	if (FD_ISSET(j, master)){
		if (j != sockfd && j != i) {
			if (send(j, recv_buf, nbytes_recvd, 0) == -1) {
				perror("send");
			}
		}
	}
}

void server_send(int j, int sockfd, fd_set *master)
{		
	if (FD_ISSET(j, master)){
		if (j != sockfd) {
			if (send(j, send_buf, BUFSIZE, 0) == -1) {
				perror("send");
			}	
		}
	}
}

void server_playerOne(int j, int sockfd, fd_set *master)
{		
	if (FD_ISSET(j, master)){
		if (j != sockfd) {
			if (send(j, send_buf1, BUFSIZE, 0) == -1) {
				perror("send");
			}	
		}
	}
}

		
void send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
	int nbytes_recvd, j;
	char recv_buf[BUFSIZE], buf[BUFSIZE];
	
	if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) <= 0) {
		if (nbytes_recvd == 0) {
			printf("socket %d hung up\n", i);
		}else {
			perror("recv");
		}
		close(i);
		FD_CLR(i, master);
	}else { 
		for(j = 0; j <= fdmax; j++){
			send_to_all(j, i, sockfd, nbytes_recvd, recv_buf, master );
		}
	}	
}



		
void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr){
	
	socklen_t addrlen;
	int newsockfd, j;
	
	addrlen = sizeof(struct sockaddr_in);
	if(CPT < CLIENT_MAX){		
		if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
			perror("accept");
			exit(1);
		}else {
			FD_SET(newsockfd, master);
			CPT++;
			if(newsockfd > *fdmax){
			*fdmax = newsockfd;
			}
			if(CPT == 1){
				printf("Premier joueur connecté : %s on port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
				printf("Attente du deuxième joueur !\n");
				joueur++;
				lobby[joueur][partie] = newsockfd;
				
			}else if(CPT == 2){
				printf("Deuxième joueur connecté : %s on port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
				printf("Début du jeu ! \n");
				// lancement du jeu 
				joueur++;
				lobby[joueur][partie] = newsockfd;
				if(joueur == 2){
				   	joueur = 0;
					partie++;
	                             
				}
				printf("Partie n°%d \n", partie);
				CPT = 0;
				for(j = 0; j <= *fdmax; j++){
					server_send(j,sockfd,master);			
				}
				for(j = 0; j <= 4; j++){
					server_playerOne(j,sockfd,master);					
				}
			    	
				/*while(fin_de_partie !=1){ // tant que aucun joueur a remporter la partie 								
					if(k%2 == 0){ // systeme pour faire 1 fois sur 2						

					}else{
	
						for(j = 5; j <= *fdmax; j++){
							server_playerTwo(j,sockfd,master);
							k++;
							server_pause(j,sockfd,master);			
						}
					}
				}*/

							
			}
		}
	 }
}
	
void connect_request(int *sockfd, struct sockaddr_in *my_addr)
{
		
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
		
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(4950);
	my_addr->sin_addr.s_addr = INADDR_ANY;
	memset(my_addr->sin_zero, '\0', sizeof my_addr->sin_zero);
		
	if (bind(*sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) == -1) {
		perror("Unable to bind");
		exit(1);
	}
	if (listen(*sockfd, 10) == -1) {
		perror("listen");
		exit(1);
	}
	printf("\n En Attente de joueurs...\n");
	fflush(stdout);
}
int main()
{
	fd_set master;
	fd_set read_fds;
	int fdmax, i;
	int sockfd= 0;
	struct sockaddr_in my_addr, client_addr;
	
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	connect_request(&sockfd, &my_addr);
	FD_SET(sockfd, &master);
	
	fdmax = sockfd;
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		
		for (i = 0; i <= fdmax; i++){
			if (FD_ISSET(i, &read_fds)){
				if (i == sockfd)
					connection_accept(&master, &fdmax, sockfd, &client_addr);
				else
					send_recv(i, &master, sockfd, fdmax);
			}
		}
	}
	return 0;
}

