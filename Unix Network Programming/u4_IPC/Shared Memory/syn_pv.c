#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>

#define NUM_PROCESS 100
#define KEY 1234
#define ITERATIONS 1000000

struct sharedMem{
	int n;
	pthread_mutex_t mutex;
};

int main(int argc, char ** argv){
	int shmid;
	struct sharedMem * shmadd;

	shmid = shmget((key_t)KEY, sizeof(struct sharedMem), IPC_CREAT | 0666);
	if(shmid < 0){
		fprintf(stderr,"Shmget failed,errno:%s\n", strerror(errno));
		return -1;
	}

	shmadd = (struct shareMem *)shmat(shmid, NULL, 0);
	if(shmadd < 0){
		fprintf(stderr,"Shmadd failed,errno:%s\n", strerror(errno));
		return -1;
	}

	shmadd->n = 0;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&shmadd->mutex, &attr);

	pid_t childProcessPID;
	for(int i = 0; i < NUM_PROCESS; i++){
		childProcessPID = fork();
		if(childProcessPID < 0){
			fprintf(stderr,"Fork failed,errno:%s\n",strerror(errno));
			return -1;
		}
		else if(childProcessPID == 0){
			for(int i = 0; i < ITERATIONS; i++){
				pthread_mutex_lock(&shmadd->mutex);
				shmadd->n ++;
				if(shmadd->n % 100000 == 0){
				printf("Process with PID %d:%d\n",getpid(), shmadd->n);
				}
				pthread_mutex_unlock(&shmadd->mutex);
			}
			shmdt(shmadd);
			return 0;
		}
	}


}
