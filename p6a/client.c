#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

void str_cli(int sockfd, FILE *fp){
    int buffsize=1024, cont;
    char *buffer = malloc(buffsize);

    while((fgets(buffer, buffsize, stdin)!=NULL)){
        send(sockfd, buffer, buffsize, 0);

        if((cont=recv(sockfd, buffer, buffsize, 0))>0){
            printf("from server: \n");
            fputs(buffer, stdout);
        }
    }
    printf("EOF\n");
}

int main(){
    int sockfd;
    struct sockaddr_in address;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))>0){
        printf("created\n");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((connect(sockfd, (struct sockaddr*)&address, sizeof(address)))>0){
        printf("connected\n");
    }

    str_cli(sockfd, stdin);
    return 0;
}