#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVEURNAME “127.0.0.1”

int main(int argc , char *argv[])
{
    int sock, read_size;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");

    printf("Enter message : ");
    scanf("%s" , message);	
    write(sock , message , strlen(message));	
     
    //keep communicating with server
    while(read_size = read(sock , server_reply , sizeof(server_reply)) > 0)
    {

	//Receive a reply from the server        
	printf("Server reply : %s\n",server_reply);
  	printf("Enter message : ");
        scanf("%s" , message);
         
        //Send some data
        write(sock , message , strlen(message));
     
    }
     
    close(sock);
    return 0;
  		
}
