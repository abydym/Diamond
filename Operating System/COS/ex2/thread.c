#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int n = 0;
static void *newThread(void *arg){
        printf("我是新的线程，我的tid是%lu，我所在的进程的pid是%d\n",pthread_self(),getpid());
        for(int i=0;i<100000;i++){
                n++;
        }
        return ((void *)0);
}

int main(){
        pthread_t tidp;
        void *retval;

        if(pthread_create(&tidp,NULL,newThread,NULL)!=0){
                printf("pthread_create error\n");
                return -1;
        }
        printf("我是主线程，我的tid是%lu，我所在的进程的pid是%d\n",pthread_self(),getpid());
        for(int i=0;i<100000;i++){
                n++;
        }
        pthread_join(tidp,&retval);

        return 0;
}
