#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>

#define H_GRP "239.0.0.1"
#define H_PORT 12345

int main(){
    int sockfd, addrlen;
    struct sockaddr_in address;
    struct ip_mreq mreq;
    u_int yes=1;
    int buffsize=1024, cont;
    char *buffer = malloc(buffsize);
    

    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))>0){
        printf("created\n");
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))<0){
        printf("sock error\n");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(H_PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(sockfd, (struct sockaddr*)&address, sizeof(address)))==0){
        printf("Binded\n");
    }

    mreq.imr_multiaddr.s_addr = inet_addr(H_GRP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0){
        printf("ip error\n");
        exit(1);
    }

    while(1){
        addrlen = sizeof(address);
        int d = recvfrom(sockfd, buffer, buffsize, 0, (struct sockaddr*)&address, &addrlen);
        if(d < 0){
            perror("recvfrom");
            exit(1);
        }   
        buffer[d] = '\0';
        fputs(buffer, stdout);
    }
}