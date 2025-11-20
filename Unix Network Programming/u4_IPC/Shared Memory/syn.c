#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define KEY 5512
#define ITERATIONS 1000000

int main(int argc, char ** argv){
	pid_t rc = fork();
	if(rc < 0){
		fprintf(stderr,"Fork failed,errno:%s\n",strerror(errno));
		return -1;
	}

	else if(rc == 0){
		int shmid;
		int * shmadd;
		shmid = shmget((key_t)KEY, sizeof(shmadd), IPC_CREAT | 0666);
		if(shmid < 0){
			fprintf(stderr,"Shmid failed,errno:%s\n",strerror(errno));
			return -1;
		}
		shmadd = shmat(shmid, NULL, 0);
		if(shmadd < 0){
			fprintf(stderr,"Shmadd failed,errno:%s\n",strerror(errno));
			return -1;
		}

		for(int i = 0; i < ITERATIONS; i++){
			*shmadd += 1;}
		shmdt(shmadd);
	}

	else{
		int shmid;
		int * shmadd;

		shmid = shmget((key_t)KEY, sizeof(shmadd), IPC_CREAT | 0666);
		if(shmid < 0){
			fprintf(stderr,"Shmget failed,errno:%s\n",strerror(errno));
			return -1;
		}
		shmadd = shmat(shmid, NULL, 0);
		if(shmadd < 0){
			fprintf(stderr,"Shmadd failed,errno:%s\n",strerror(errno));
			return -1;
		}

		for(int i = 0; i < ITERATIONS; i++){
			*shmadd += 1;
		}
		wait(NULL);
		printf("Result: %d\n",*shmadd);

		shmdt(shmadd);
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}
