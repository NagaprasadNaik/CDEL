#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void str_echo(int connfd, int port){
    int buffsize=1024, cont=1;
    char *buffer = malloc(buffsize);

    do{
        while((cont=recv(connfd, buffer, buffsize, 0))>0){
            printf("clli connect %d: ", port);
            fputs(buffer, stdout);
            send(connfd, buffer, cont, 0);
        }
    }while(cont>0);
}

int main(){

    int listefd, connfd, addrlen, pid;
    struct sockaddr_in address;

    if((listefd = socket(AF_INET, SOCK_STREAM, 0))>0){
        printf("Socket connected\n");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(15001);
    address.sin_addr.s_addr = INADDR_ANY;

    if((bind(listefd, (struct sockaddr*)&address, sizeof(address)))==0){
        printf("Connected bind\n");
    }

    listen(listefd, 3);

    for(;;){
        addrlen = sizeof(address);
        connfd = accept(listefd, (struct sockaddr*)&address, &addrlen);

        if((pid=fork())==0){
            close(listefd);
            str_echo(connfd, address.sin_port);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}

