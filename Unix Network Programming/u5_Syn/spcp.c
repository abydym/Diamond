#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFF 5
#define ITERATIONS 20

struct shareData{
	int buff[BUFF];
	int front, rear;
	sem_t mutex, empty, full;
};

struct shareData sd;

static void * producer(void * arg);
static void * consumer(void * arg);

int main(int argc, const char ** argv){
	pthread_t tid_producer, tid_consumer;
	sd.front = 0;
	sd.rear = 0;
	sem_init(&sd.mutex, 0 ,1);
	sem_init(&sd.empty, 0, BUFF);
	sem_init(&sd.full,0, 0);

	pthread_create(&tid_producer, NULL, producer, NULL);
	pthread_create(&tid_consumer, NULL, consumer, NULL);

	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);

	sem_destroy(&sd.mutex);
	sem_destroy(&sd.empty);
	sem_destroy(&sd.full);
}

static void * producer(void * arg){
	for(int i = 0; i < ITERATIONS; i++){
	sem_wait(&sd.empty);
	sem_wait(&sd.mutex);

	sd.buff[sd.rear] = i;
	printf("%-3d:the producer thread put a product %-3d into the buffer %d\n", i, i, sd.rear);
	sd.rear = (sd.rear + 1)% BUFF;

	sem_post(&sd.mutex);
	sem_post(&sd.full);

	sleep(2);
	}
}
static void * consumer(void * arg){
	for(int i = 0; i < ITERATIONS ; i++){
	sem_wait(&sd.full);
	sem_wait(&sd.mutex);

	printf("%-3d:the consumer thread consume a product %-3d from the buffer %d\n",i, sd.buff[sd.front], sd.front);
	sd.front = (sd.front + 1)% BUFF;

	sem_post(&sd.mutex);
	sem_post(&sd.full);

	sleep(1);	
	}
	return NULL;
}

