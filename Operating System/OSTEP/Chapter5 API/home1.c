#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("Test! (pid:%d)\n", (int) getpid());
	int x = 100;
	printf("The initial value of x is %d\n",x);
	int rc = fork();
	if (rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if (rc == 0){
		printf("This is child! The value of x is %d.(pid:%d)\n", x,  (int) getpid());
		x = 200;
		printf("Child process changed x to %d\n", x);
	}else{
		printf("This is parent of %d (pid:%d)! The value of x is %d.\n",rc,(int) getpid(), x);
		x = 300;
		printf("Parent process changed x to %d\n", x);
	}
	printf("After changes:(pid:%d)The value of x is %d\n",(int) getpid(), x);
	return 0;

}
