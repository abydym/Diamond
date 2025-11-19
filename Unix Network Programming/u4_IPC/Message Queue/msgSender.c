#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

struct msg_st{
	long int msg_type;
	char buff[BUFSIZ];
};

int main(){
	struct msg_st msg;
	char buff[BUFSIZ];
	//long int msgtype = 0; 这一行是僵尸代码，因为在之后根本没用上，主要还是依靠while循环里的msg.msg_type=1，因为消息队列的消息类型(mtype)要求是必须一个大于0的整数，如果为0了，msgsnd会报错，返回-1，errno设置为EINVAL。

	int msgid = msgget((key_t)5312, 0666 | IPC_CREAT);
	if(msgid == -1){
		fprintf(stderr,"Msgget failed,errno:%s\n",strerror(errno));
		return -1;
	}

	while(1){
		printf("Input message:");
		fgets(buff, BUFSIZ, stdin); //键盘里的信息通过这个stdin来被送进buff
		buff[strlen(buff) - 1] = '\0';//因为在最后会有一个换行符，所以这里使用这个来把最后的\n换成\0。
		if(strncmp(buff, "urgent", 6) == 0){
			msg.msg_type = 2;
			printf(">>Sending URGENT message...\n");
		}
		else{
			msg.msg_type = 1;
			printf(">>Sending normal message...\n");
		}
		//现在尝试加入紧急消息和普通消息的机制，就不统一都用msg.msg_type = 1;
		strcpy(msg.buff, buff);

		if(msgsnd(msgid, (void *)&msg, strlen(buff) + 1, 0) == -1){//原来msgsnd的第三个参数是BUFSIZ，现在改成了strlen(buff)+1，即说明我发送可以只发送原来字符加上\0那么长，节省了很多资源，不用发8192B（BUFSIZ）的空间。
			fprintf(stderr,"Msgsnd failed,errno:%s\n",strerror(errno));
			return -1;
		}
		if(strcmp(buff, "quit") == 0){
			break;
		}
	}

	return 0;
}
