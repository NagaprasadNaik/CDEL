#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void str_echo(int listenfd, struct sockaddr *cli_address, int addrlen){
    int buffsize = 1024, cont=1;
    char *buffer = malloc(buffsize);

    do{
        while((cont=recvfrom(listenfd, buffer, buffsize, 0, cli_address, &addrlen))>0){
            sendto(listenfd, buffer, cont, 0, cli_address, addrlen);
        }
    }while(cont>0);
}

int main(){
    int listenfd;
    struct sockaddr_in serv_address, cli_address;

    if((listenfd = socket(AF_INET, SOCK_DGRAM, 0))>0){
        printf("created\n");
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(15001);
    serv_address.sin_addr.s_addr = INADDR_ANY;

    if((bind(listenfd, (struct sockaddr*)&serv_address, sizeof(serv_address)))==0){
        printf("binded\n");
    }

    str_echo(listenfd, (struct sockaddr*)&cli_address, sizeof(cli_address));
    return 0;
}