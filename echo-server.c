#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[]) //specifiying number of arguments that will be input
{
	if(argc <2) //if input does not contain the port number
	{
		printf("Error!.Port not provided.\n");
		exit(1);
	}
	int sockfd,newsockfd,portno,n;
	char buffer[255];
	
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t clilen; //socklen_t is data type in socket.h,32 bit
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd <0 )
	{
		error("Error opening socket\n");
	}
	
	bzero((char *)&serv_addr,sizeof(serv_addr));
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port = htons(portno); //htons- Host to network short 
	
	if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) <0)
	{
		error("Binding failed!\n");
	}
	
	listen(sockfd,5);
	clilen= sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	
	if (newsockfd <0)
		error("Error on accept!\n");
	
	
	n = read(newsockfd,buffer,255);
	if (n <0)
		error("Error!Could not read!\n");
	printf("Client : %s\n",buffer);
	
	
	
	strcpy(buffer,"Hello from server!");
	printf("Server:%s\n",buffer);
	n=write(newsockfd,buffer,strlen(buffer));
	if (n<0)
		error("Error on writing!\n");

	
	close(newsockfd);
	close(sockfd);
	return 0;
	
}
