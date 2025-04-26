#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0){
        fprintf(stderr,"fork error!");
        return -1;
    }
    else if(pid == 0){
        printf("我是子进程，我的PID是%d，我的父进程PID是%d\n",getpid(),getppid());
    }
    else{
        printf("我是父进程，我的PID是%d，我的子进程PID是%d\n",getpid(),pid);
    }

    return 0;
}

