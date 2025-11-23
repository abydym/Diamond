#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h> 

#define SERV_PORT 9877
#define LISTENQ 1024

int main(int argc, char ** argv){ 
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in servaddr, cliaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    listen(listenfd, LISTENQ);
    printf("Server is running...waiting for connections\n");

    
    pid_t childpid; 
    socklen_t clilen; 

    while(1){
        
        clilen = sizeof(cliaddr); 
        
        
        int connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        if (connfd < 0) {
            if (errno == EINTR) continue;
            else {
                perror("accept error");
                exit(1);
            }
        }

        
        if ( (childpid = fork()) == 0 ){ 
           
            close(listenfd); 
            
            printf("Child Process (PID: %d) is processing connection.\n", getpid());
            
            close(connfd);   
            exit(0);         
        }
        close(connfd); 
    }
    return 0;
}
