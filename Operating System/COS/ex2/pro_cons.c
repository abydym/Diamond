#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUF_SIZE 10

int Top = 0;
int Bottom = 0;
int * Buffer;

pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t Empty, Full;

static void * Producer_Thread(void * arg);
static void * Consumer_Thread(void * arg);

int main(){
        pthread_t ProducerTIDP, ConsumerTIDP;
        void * Retvalp, *Retvalc;

        Buffer = (int *)malloc(BUF_SIZE * sizeof(int));

        if(sem_init(&Full, 0, 0) == -1 || sem_init(&Empty, 0, BUF_SIZE) == -1){
                printf("sem_init error\n");
                return -2;
        }

        if(pthread_create(&ProducerTIDP, NULL, Producer_Thread, NULL) != 0 || pthread_create(&ConsumerTIDP, NULL, Consumer_Thread, NULL) != 0){
                printf("pthread_create error\n");
                return -1;
        }

        pthread_join(ProducerTIDP, &Retvalp);
        pthread_join(ConsumerTIDP, &Retvalc);

        free(Buffer);
        sem_destroy(&Full);
        sem_destroy(&Empty);
        return 0;
}

static void * Producer_Thread(void * arg){
        printf("Producer thread started\n");
        for(int i = 0; i < 20; i++){
                int Nextp = i;
                sem_wait(&Empty);
                pthread_mutex_lock(&Mutex);
                Buffer[Top] = Nextp;
                Top = (Top + 1) % BUF_SIZE;
                printf("Producer thread: produce an item %d and insert it in buffer\n", Nextp);
                pthread_mutex_unlock(&Mutex);
                sem_post(&Full);
                sleep(1);
        }
}

static void * Consumer_Thread(void * arg){
        printf("Consumer thread started\n");
        for(int i = 0; i < 20; i++){
                sem_wait(&Full);
                pthread_mutex_lock(&Mutex);
                int Nextc = Buffer[Bottom];
                Bottom = (Bottom + 1) % BUF_SIZE;
                printf("Consumer thread: fetch an item %d from buffer\n", Nextc);
                pthread_mutex_unlock(&Mutex);
                sem_post(&Empty);
                sleep(5);
        }
}
