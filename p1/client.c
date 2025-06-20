#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

int main(){
    int sockfd, cont;
    struct sockaddr_in address;
    int buffsize = 1024;
    char *buffer = malloc(buffsize);
    char fname[256];

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))>0){
        printf("Socket created\n");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((connect(sockfd, (struct sockaddr*)&address, sizeof(address)))==0){
        printf("connected\n");
    }
    printf("enter the filename\n");
    scanf("%s", &fname);

    send(sockfd, fname, 256, 0);

    while((cont = recv(sockfd, buffer, buffsize, 0))>0){
        write(1, buffer, cont);
    }
    close(sockfd);
    return 0;
}





