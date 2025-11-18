#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>

struct msg_st{
	long int msg_type;
	char buff[BUFSIZ];
};

int main(){
	struct msg_st msg;
	char buff[BUFSIZ];
	long int msgtype = 0;

	int msgid = msgget((key_t)5312, 0666 | IPC_CREAT);
	if(msgid == -1){
		fprintf(stderr,"Msgget failed,errno:%s\n",strerror(errno));
		return -1;
	}

	while(1){
		printf("Input message:");
		fgets(buff, BUFSIZ, stdin);
		buff[strlen(buff) - 1] = '\0';
		msg.msg_type = 1;
		strcpy(msg.buff, buff);

		if(msgsnd(msgid, (void *)&msg, BUFSIZ, 0) == -1){
			fprintf(stderr,"Msgsnd failed,errno:%s\n",strerror(errno));
			return -1;
		}
		if(strcmp(buff, "quit") == 0){
			break;
		}
	}

	return 0;
}
