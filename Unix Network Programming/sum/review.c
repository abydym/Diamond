/*说明：此代码用于考前复习，里面综合了各种知识点，从而构建成了一个带统计功能的并发服务器
 *包含了网络层、并发层、协议层和IPC层
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <semaphore.h>

#define PORT 55312
#define MAXLINE 4096

//协议设计：意在解决TCP的粘包/拆包
struct Packet{
	int type;
	int length;
	char data[0];
};

//IPC结构体定义
struct LogMsg{
	long mtype;
	char mtext[MAXLINE];
};

int *client_count;
sem_t mutex;
int msgid;

//辅助函数readn，意在处理字节流少读的问题
size_t readn(int fd, void *vptr, size_t n){
	size_t nleft =  n;
	ssize_t nread;
	char *ptr = vptr;

	while(nleft > 0){
		if((nread = read(fd, ptr, nleft)) < 0){
			if(errno = EINTR) nread = 0;//被信号中断了，继续读
			else return -1;
		}else if(nread == 0){
			break;//EOF
		}
		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft);
}

//线程工作函数
void *doit(void *arg){
	int connfd = *((int *)arg);
	free(arg);
	pthread_detach(pthread_self());
	printf("Thread %lu handling client fd: %d\n", pthread_self(), connfd);

	//同步操作
	sem_wait(&mutex);
	(*client_count)++;
	printf("Current Clients: %d\n", *client_count);
	sem_post(&mutex);

	//TLV
	struct Packet header;
	if(readn(connfd, &header, sizeof(header)) == sizeof(header)){
		char *body = malloc(header.length + 1);
		if(readn(connfd, body, header.length) == header.length){
			body[header.length] = '\0';
			printf("Recv Type: %d, Data: %s\n", header.type, body);

			//发送消息队列
			struct LogMsg log;
			log.mtype = 1;
			snprintf(log.mtext, MAXLINE, "Client sent: %s", body);
			msgsnd(msgid, &log, sizeof(log.mtext), 0);
		}
		free(body);
	}
	//客户端断开，计数减1
	sem_wait(&mutex);
	(*client_count)--;
	sem_post(&mutex);

	close(connfd);
	return NULL;
}

int main(int argc, char ** argv){
	int listenfd, *iptr;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	pthread_t tid;

	//IPC初始化
	int shmid = shmget((key_t)1234, sizeof(int), 0666 | IPC_CREAT);
	client_count = (int *)shmat(shmid, NULL, 0);
	*client_count = 0;
	msgid = msgget((key_t)5678, 0666 | IPC_CREAT);
	sem_init(&mutex, 0, 1);

	//网络初始化
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&servaddr,0 ,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, 1024);
	printf("Server running on port %d...\n", PORT);

	while(1){
		int clilen = sizeof(cliaddr);
		iptr = malloc(sizeof(int));
		*iptr = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if(*iptr < 0){
			free(iptr);
			continue;
		}

		pthread_create(&tid, NULL, &doit, iptr);
	}

	shmdt(client_count);
	shmctl(shmid, IPC_RMID, NULL);
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
