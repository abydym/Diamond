#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define ROUNDS  1000000
#define KEY     55312

struct sharedData{
    int n;
    pthread_mutex_t mutex;
};

int main(int argc, const char ** argv){

    pid_t pid = fork();

    //child process
    if(pid == 0){
        sleep(1);

        int shmid                  = shmget((key_t)KEY, sizeof(struct sharedData), IPC_CREAT | 0666);
        struct sharedData * shmadd = shmat(shmid, NULL, 0);

        for(int i = 0; i < ROUNDS; i++){
            pthread_mutex_lock(&shmadd->mutex);
            shmadd->n ++;
            pthread_mutex_unlock(&shmadd->mutex);
        }

        shmdt(shmadd);
    }

    //parent process
    else{
        int shmid                  = shmget((key_t)KEY, sizeof(struct sharedData), IPC_CREAT | 0666);
        struct sharedData * shmadd = shmat(shmid, NULL, 0);
        shmadd->n                  = 0;
        pthread_mutex_init(&shmadd->mutex, NULL);

        for(int i = 0; i < ROUNDS; i++){
            pthread_mutex_lock(&shmadd->mutex);
            shmadd->n ++;
            pthread_mutex_unlock(&shmadd->mutex);
        }
        
        wait(NULL);
        printf("%d\n", shmadd->n);

        pthread_mutex_destroy(&shmadd->mutex);
        shmdt(shmadd);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
