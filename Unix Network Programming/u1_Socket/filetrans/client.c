#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 55312
#define BUFFSIZ 1024

int main(int argc, char ** argv){
	int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenfd == -1){
		printf("Failed to create the socket\n");
		return -1;
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(PORT);

	int connfd = connect(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
	if(connfd == -1){
		printf("Failed to connect to the server\n");
		return -1;
	}

	FILE * fp = fopen("2.tif", "rb");
	if(fp == NULL){
		printf("Failed to open the file\n");
		return -1;
	}

	char buff[BUFFSIZ];
	int bytesRead = 0;
	bytesRead = fread(buff, sizeof(char), BUFFSIZ, fp);
	while(bytesRead > 0){
		write(listenfd, buff, bytesRead);
	}
	close(listenfd);
	fclose(fp);

	return 0;
}
