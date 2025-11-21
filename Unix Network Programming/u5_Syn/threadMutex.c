#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define ROUNDS 1000000

int gv_n;

pthread_mutex_t mutex;

static void * childThread(void * arg);

int main(int argc, char ** argv){
	pthread_mutex_init(&mutex, NULL);
	pthread_t tid;
	pthread_create(&tid, NULL, childThread, NULL);
	
	for(int i =0; i < ROUNDS; i++){
		pthread_mutex_lock(&mutex);
		gv_n ++;
		pthread_mutex_unlock(&mutex);
	}

	pthread_join(tid, NULL);
	printf("%d\n", gv_n);
	pthread_mutex_destroy(&mutex);
	return 0;
}

static void * childThread(void * arg){
	for(int i =0; i < ROUNDS; i++){
		pthread_mutex_lock(&mutex);
		gv_n ++;
		pthread_mutex_unlock(&mutex);
	}
}
