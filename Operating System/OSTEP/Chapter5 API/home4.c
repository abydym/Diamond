#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	printf("hello,world (pid:%d)", (int)getpid());
	int rc = fork();
	if(rc < 0){
		fprintf(stderr,"Fork failed");
		exit(1);
	}else if(rc == 0){
		printf("hello, I am child (pid:%d)\n", (int) getpid());
		char *myargs[3];
		myargs[0] = strdup("ls");
		myargs[1] = strdup("-l");
		myargs[2] = NULL;
		execvp("/bin/ls", myargs);
		printf("this shouldn't print out\n");
		exit(1);
	}else{
		wait(NULL);
		printf("Parent: Child process finishied.\n");
	}
	return 0;
}
