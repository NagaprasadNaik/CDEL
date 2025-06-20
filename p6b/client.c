#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void str_cli(FILE *fp, int sockfd, struct sockaddr* serv_address, int serv_addrlen){
    int buffsize = 1024, cont;
    char *buffer = malloc(buffsize);


    while((fgets(buffer, buffsize, fp))!=NULL){
        sendto(sockfd, buffer, buffsize, 0, serv_address, serv_addrlen);

        if((cont=recvfrom(sockfd, buffer, buffsize, 0, NULL, NULL))>0){
            fputs(buffer, stdout);
        }
    }
    printf("EOF\n");
}

int main(){
    int sockfd;
    struct sockaddr_in serv_address;

    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))>0){
        printf("created\n");
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(15001);
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    str_cli(stdin, sockfd, (struct sockaddr*)&serv_address, sizeof(serv_address));
    return 0;
}