#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int fd = open("home2_test.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd == -1){
        fprintf(stderr, "file open failed");
        exit(-1);
    }
    
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed");
        close(fd); // 使用 close 系统调用关闭文件描述符
        exit(0);
    }else if(rc == 0){
        // 子进程
        const char *child_data = "Data from child\n";
        write(fd, child_data, strlen(child_data));
    }else{
        const char *parent_data = "Data from parent\n";
        write(fd, parent_data, strlen(parent_data));
    }
    
    close(fd); 
    return 0;
}

