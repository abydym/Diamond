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

int main(int argc, const char ** argv){
	struct msg_st msg;
	long int msgtype = 0;

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

