// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 4244
int main(int argc, char const *argv[])
{
	int un = 1;
    int conteur = 0;
	int server_fd, new_socket, valread , second_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024];
	char *hello = "Welcome in Sokomult\n";
	char *chose = "write 'ok' if you are ready ";
	char *one = "ceci est un un";
    while(1){
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("10.20.85.248");
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))>0)
	{
		memset(buffer,0,255);
		conteur = conteur + 1;
        printf("%i. ",conteur);
	valread = read( new_socket , buffer, 3);
	printf("%s is connect\n",buffer );
	send(new_socket , hello , strlen(hello) , 0);
	send(new_socket , chose , strlen(chose) , 0);
	recv(new_socket , buffer , 255 , 0);
	if(recv(new_socket , "ok" , 255 , 0)){
		printf("connexion down pour un client");
		shutdown(new_socket ,SHUT_RDWR);
	}
	}
    }
	return 0;
}