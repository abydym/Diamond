#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int pipefd[2];
	char ch;

	if(pipe(pipefd) == -1){
		fprintf(stderr,"pipe failed\n");
		exit(-1);
	}
	int rc = fork();
	if(rc < 0){
		fprintf(stderr,"fork failed\n");
		exit(0);
	}else if(rc == 0){
		close(pipefd[0]); //关闭管道读端
		printf("Child (pid:%d)\n",(int)getpid());
		printf("hello\n");
		write(pipefd[1], "o", 1); //随便写入一个字符通知父进程
		close(pipefd[1]);
		exit(1);
	}else{
		close(pipefd[1]); //先关闭写端
		read(pipefd[0], &ch, 1);
		printf("Parent (pid:%d)\n",(int)getpid());
		printf("goodbye\n");
		close(pipefd[0]); //关闭读端
		exit(1);
	}
	return 0;
}
