#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define PORT 55312
#define MAX_BUFF_SIZE 1024

int main(int argc,const char ** argv){
	if(argc != 2){
	fprintf(stderr,"用法:%s<Server IP Address>\n",argv[0]);
	return -1;
	}

	char buff[MAX_BUFF_SIZE];
	memset(buff,0,sizeof(buff));
	printf("This is the client\n");

	int socketClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socketClient == -1){
		fprintf(stderr,"Create socket failed:%s\n",strerror(errno));
		return -1;
	}
	struct sockaddr_in servAddr;
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	if(inet_pton(AF_INET,argv[1],&servAddr.sin_addr) <= 0){
	fprintf(stderr,"inet_pton failed:Invalid IP address %s\n",argv[1]);
	close(socketClient);
	return -1;
	}

	if(connect(socketClient,(struct sockaddr *)&servAddr,sizeof(servAddr)) == -1){
	fprintf(stderr,"Connect failed %s\n",strerror(errno));
	close(socketClient);
	return -1;
	}

	printf("Connect to server at %s\n",argv[1]);
	printf("Receiving message..\n");

	ssize_t n;
	n=read(socketClient,buff,MAX_BUFF_SIZE-1);

	if(n<0){
	fprintf(stderr,"read err:%s\n",strerror(errno));
	}
	else if(n==0){
	printf("Server closed the connection\n");
	}
	else{
	buff[n]='\0';
	printf("%s",buff);
	}

	close(socketClient);
	printf("Socket is closed\n");

	return 0;
}
