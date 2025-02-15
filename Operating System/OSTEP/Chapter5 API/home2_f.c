#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	FILE *file;
	file = fopen("home2_test.txt", "a");
	if(file == NULL){
		fprintf(stderr, "file open failed");
		exit(-1);
	}
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed");
		fclose(file);
		exit(0);
	}else if(rc == 0){
		fprintf(file, "Data from child\n");
	}else{
		fprintf(file, "Data from parent\n");
	}
	fclose(file);
	return 0;
}
