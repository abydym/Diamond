#include <pthread.h>
#include <semaphore.h>

int n=0;
sem_t sem;

static void *newThread(void *arg){
        printf("我是新的线程，我的tid是%lu，我所在的进程的pid是%d\n",pthread_self(), getpid());
        for(int i=0;i<100000;i++){
                sem_wait(&sem);
                n++;
                sem_post(&sem);
        }
        return ((void *)0);
}

int main(){
        pthread_t tidp;
        void *retval;

        if(sem_init(&sem,0,1) == -1){
                fprintf(stderr,"信号量初始化错误");
                return -2;
        }
        if(pthread_create(&tidp,NULL,newThread,NULL)!=0){
                fprintf(stderr,"子线程创建错误");
                return -1;
        }
        printf("我是主线程，我的tid是%lu，我所在的进程的pid是%d\n",pthread_self(), getpid());
        for(int i=0;i<100000;i++){
                sem_wait(&sem);
                n++;
                sem_post(&sem);
        }

        pthread_join(tidp,&retval);
        sem_destroy(&sem);
        printf("全局变量n的值为%d\n",n);
        return 0;
}
                                                                        42,1          Bot
