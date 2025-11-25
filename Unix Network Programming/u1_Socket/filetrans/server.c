#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 55312
#define BUFFSIZ 1024
#define LISTENQ 5

int main(int argc, char ** argv){
	int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenfd == -1){
		printf("Failed to create the socket\n");
		return -1;
	}
	struct sockaddr_in servAddr,cliaddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	if(bind(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1){
		printf("Failed to bind\n");
		return -1;
	}

	if(listen(listenfd, LISTENQ) == -1){
		printf("Failed to enter listening state\n");
		return -1;
	}

	socklen_t cliAddr;
	int connfd = accept(listenfd, (struct sockaddr *)&servAddr, &cliAddr);
	if(connfd == -1){
		printf("Failed to accept the connection from the client\n");
		return -1;
	}

	FILE * fp = fopen("receivedFile.tif", "wb");
	if(fp == NULL){
		printf("Failed to open the file\n");
		return -1;
	}

	char buff[BUFFSIZ];
	int byteRead = 0;
	byteRead = read(connfd, buff, BUFFSIZ);
	while(byteRead > 0){
		fwrite(buff, sizeof(char), byteRead, fp);
	}
	close(listenfd);
	fclose(fp);
}
