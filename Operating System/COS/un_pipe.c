#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define INPUT 0
#define OUTPUT 1

int pipe(int filedis[2]);
int main(int argc, char *argv[]){
	int file_descriptors[2];
	pid_t pid;
	char buf[256];
	int returned_count;
	pipe(file_descriptors);
	if((pid = fork()) == -1){
		printf("Erroe in fork\n");
		exit(1);
	}

	if(pid == 0){
		printf("in the spawned (child) process...\n");
		close(file_descriptors[INPUT]);
		write(file_descriptors[OUTPUT],"test data", strlen("test data"));
		exit(0);
	}
	else{
		printf("in the spawning (parent) process...\n");
		close(file_descriptors[OUTPUT]);
		returned_count = read(file_descriptors[INPUT],buf,sizeof(buf));
	}
	return 0;
}
