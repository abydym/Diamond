#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LISTENQ 5
#define PORT 5

void *doit(void *arg){
	int connfd = *((int *)arg);
	free(arg);//arg是主线程给的，用完必须要扔掉，以防止内存泄漏
	pthread_detach(pthread_self());//类似sigchild，保证子线程结束后资源能够自动回收
	printf("Child thread is handling connection: %d\n", connfd);
	close(connfd);
	return NULL;
}

int main(){
	int listenfd, *iptr;
	pthread_t tid;
	struct sockaddr_in cliaddr;
	socklen_t len;

	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliaddr.sin_port = htons(PORT);

	bind(listenfd, (struct sockaddr *)&cliaddr, len);
	listen(listenfd, LISTENQ);

	while(1){
		len = sizeof(cliaddr);
		iptr = malloc(sizeof(int));
		*iptr = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		pthread_create(&tid, NULL, &doit, iptr);
	}

}
