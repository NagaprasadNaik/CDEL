#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void str_echo(int connfd, FILE *fp){
    int buffsize=1024, cont=1;
    char *buffer = malloc(buffsize);

    do{
        while((cont=recv(connfd, buffer, buffsize, 0))>0){
            fputs(buffer, stdout);
            send(connfd, buffer, cont, 0);
        }
    }while(cont>1);
}

int main(){
    int listenfd, connfd, addrlen;
    struct sockaddr_in address;

    if((listenfd=socket(AF_INET, SOCK_STREAM, 0))>0){
        printf("connected\n");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = INADDR_ANY;

    if((bind(listenfd, (struct sockaddr*)&address, sizeof(address)))==0){
        printf("binded\n");
    }

    listen(listenfd, 3);

    for(;;){
        addrlen = sizeof(address);
        connfd = accept(listenfd, (struct sockaddr*)&address, &addrlen);
        if(connfd>0){
            printf("connected\n");
        }

        str_echo(connfd, stdin);
        close(connfd);
    }
    return 0;
}