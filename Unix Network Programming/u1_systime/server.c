#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 55312
int main(int argc,const char ** argv){
	char buff[1024];
	printf("This is server\n");

	int socketServer = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socketServer == -1){
		fprintf(stderr,"create socket failed\n");
		return -1;
	}

	printf("The socket is created\n");

	struct sockaddr_in servAddr;
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	if(bind(socketServer,(struct sockaddr *)&servAddr,sizeof(servAddr))==-1){
		fprintf(stderr,"bind failed,errno:");
		return -1;
	}
	printf("The address is bound\n");

	if(listen(socketServer, 5)==-1){
		fprintf(stderr,"Listen failed\n");
	}
	printf("Listen state!\n");

	struct sockaddr_in cliAddr;
	socklen_t len = sizeof(cliAddr);

	while(1){
		printf("Waiting for connection\n");
		int conn = accept(socketServer,(struct sockaddr *)(&cliAddr),&len);
		if(conn == -1){
			fprintf(stderr,"accept failed\n");
			continue;
		}

		printf("Connection from %s, port %d\n",inet_ntop(AF_INET,&cliAddr.sin_addr,buff,sizeof(buff)),ntohs(cliAddr.sin_port));

		time_t ticks = time(NULL);
		printf("Sending messages...\n");
		snprintf(buff,sizeof(buff),"%24s\r\n",ctime(&ticks));
		write(conn,buff,strlen(buff));
		printf("Message is sent\n\n");
		close(conn);
	}

	close(socketServer);
	printf("The socket is closed\n");
	return 0;


}
