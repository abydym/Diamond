#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int rc = fork();
	if (rc < 0){
		fprintf(stderr,"failed to fork\n");
	}else if(rc == 0){
		printf("Child (pid:%d)\n",(int)getpid());
		printf("hello\n");
	}else{
		int status;
		wait(&status);
		printf("Parent (pid:%d)\n",(int)getpid());
		printf("goodbye\n");
	}	
	return 0;
}
