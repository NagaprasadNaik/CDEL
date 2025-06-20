#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

void str_cli(FILE *fp, int sockfd){
    int buffsize = 1024, cont;
    char *buffer = malloc(buffsize);

    while((fgets(buffer, buffsize, fp)!=NULL)){
        send(sockfd, buffer, buffsize, 0);

        if((cont=recv(sockfd, buffer, buffsize, 0))>=0){
            printf("Server has replied\n");
            fputs(buffer, stdout);
        }
    }
    printf("\nEOF\n");
}

int main(){
    int sockfd;
    struct sockaddr_in address;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) >0){
        printf("Socket created\n");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((connect(sockfd, (struct sockaddr*)&address, sizeof(address)))>0){
        printf("Connected\n");
    }

    str_cli(stdin, sockfd);
    close(sockfd);
    return 0;
}





