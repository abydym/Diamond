#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 55312

int main(int argc, const char ** argv){
	char buff[1024];
	bzero(buff,sizeof(buff));
	printf("This is client.\n");

	int socketClient = socket(AF_INET,SOCK_STREAM,0);
	if(socketClient == -1){
		fprintf(stderr,"Create socket failed!\n");
		return -1;
	}

	struct sockaddr_in servAddr;
	bzero(&servAddr,sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(PORT);

	if(connect(socketClient,(struct sockaddr*)&servAddr,sizeof(servAddr)) == -1){
		fprintf(stderr,"Connect failed!\n");
		return -1;
	}
	printf("Connected to the server!\n");
	printf("Receiving messages...\n");
	read(socketClient,buff,sizeof(buff));
	printf("%s\n",buff);
	close(socketClient);
	printf("Socket is closed!\n");

	return 0;

}
