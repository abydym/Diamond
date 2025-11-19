#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>

#define SHARED_MEMORY_SIZE 1024
#define KEY 55312

int main(int argc, char ** argv){
	int shmid;
	char * shmadd;
	char buff[SHARED_MEMORY_SIZE];

	shmid = shmget((key_t)KEY, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		fprintf(stderr,"Shmget failed,errno:%s",strerror(errno));
		return -1;
	}

	shmadd = shmat(shmid, NULL, 0);
	if(shmadd < 0){
		fprintf(stderr,"Shmadd failed,errno:%s",strerror(errno));
		return -1;
	}

	while(1){
		printf("Input message:");
		memset(buff, 0, sizeof(buff));
		fgets(buff, sizeof(buff), stdin);
		buff[strlen(buff) - 1] = '\0';

		strcpy(shmadd, buff);
		if(strcmp(buff, "quit") == 0){
			break;
		}
	
	}
	shmdt(shmadd);
	return 0;

}
