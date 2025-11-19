#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

#define SHARED_MEMORY_SIZE 1024
#define KEY 55312

int main(int argc, char ** argv){
	int shmid;
	char *shmadd;

	shmid = shmget((key_t)KEY, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		fprintf(stderr,"Shmget failed,errno:%s\n", strerror(errno));
		return -1;
	}

	shmadd = shmat(shmid, NULL, 0);
	if(shmadd < 0){
		fprintf(stderr, "Shmat failed,errno:%s\n", strerror(errno));
		return -1;
	}

	while(1){
		printf("Message is in the shared memory:%s\n",shmadd);
		if(strcmp(shmadd, "quit") == 0){
			break;
		}	
		sleep(5);
	}
	shmdt(shmadd);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
