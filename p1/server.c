#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

int main(){
    int sockfd, connfd, cont, fd;
    struct sockaddr_in address;
    int buffsize = 1024;
    char *buffer = malloc(buffsize);
    char fname[256];

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))>0){
        printf("socket created\n");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = INADDR_ANY;

    if((bind(sockfd, (struct sockaddr*)&address, sizeof(address)))==0){
        printf("binding successful\n");
    }

    listen(sockfd, 3);
    socklen_t addrlen = sizeof(address);
    if((connfd = accept(sockfd, (struct sockaddr*)&address, &addrlen))>0){
        printf("Connnection accepted\n");
    }

    recv(connfd, fname, 256, 0);

    if((fd=open(fname, O_RDONLY))<0){
        printf("error\n");
        exit(0);
    }

    while((cont=read(fd, buffer, buffsize))>0){
        send(connfd, buffer, cont, 0);
    }
    close(connfd);
    close(sockfd);
    return 0;
}




