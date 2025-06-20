#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#define H_PORT 12345
#define H_GRP "239.0.0.1"

int main(){
    int sockfd;
    struct sockaddr_in address;
    char *msg = "RVCE-CSE";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(H_PORT);
    address.sin_addr.s_addr = inet_addr(H_GRP);

    while(1){
        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&address, sizeof(address));
        printf("Sent: %s\n", msg);
        sleep(1);
    }
    return 0;
}