#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>
struct msg_st{
	long int msg_type;
	char buff[BUFSIZ];
};

int main(int argc, char ** argv){
	struct msg_st msg;
	long int msgtype = 0;//这个是默认接受所有类型的消息
	if(argc > 1){//这一块容易出错，首先argc是命令行里有几个参数，程序自己的名字就已经是一个参数了，如果没加其他参数然后直接去拿argv[1]，程序就会崩溃（Segmentation Fault，段错误），所以我们要先判断是否有大于1个参数，即argc > 1，然后再去捞，一定要防止越界。
	msgtype = atol(argv[1]);
	printf(">> Mode:Receiving only type %ld\n",msgtype);
	}
	else{
	printf(">> Mode:Receiving ALL messages(FIFO)\n");
	}

	int msgid = msgget((key_t)5312, 0666 | IPC_CREAT);
	if(msgid == -1){
		fprintf(stderr,"Msgget failed,errno:%s\n",strerror(errno));
		return -1;
	}

	while(1){
		if(msgrcv(msgid, (void *)&msg, BUFSIZ, msgtype, 0) == -1){
		fprintf(stderr,"Msgrcv failed,errno:%s\n",strerror(errno));
		return -1;
	}
	
		printf("Message from the sender: %s\n",msg.buff);

		if(strcmp(msg.buff, "quit") == 0){
			break;
		}

		if(msgctl(msgid, IPC_RMID, 0) == -1){
			fprintf(stderr,"Magctl failed,errno:%s\n",strerror(errno));
			return -1;
		}
	}
	return 0;
}

