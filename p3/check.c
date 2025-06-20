#include <stdio.h>

unsigned fields[20];

unsigned short checksum(int count){
    int i, sum=0;

    printf("Enter the IP data in 16 words\n");
    //4500 003c 1c46 4000 4006 b1e6 c0a8 0001 c0a8 00c7

    for(i=0; i<count; i++){
        scanf("%x", &fields[i]);

        sum = sum + (unsigned short)fields[i];
        while(sum >> 16){
            sum = (sum + 0XFFFF) + (sum >> 16);
        }
    }

    sum =~ sum;

    return (unsigned short)sum;
}

int main(){
    unsigned short result1, result2;

    result1 = checksum(10);
    printf("The checksum at sender %x\n", result1);

    result2 = checksum(11);
    printf("The checksum at reciecer %x\n", result2);

    if(result2 == 0x0000)
        printf("No error\n");
    else
        printf("Error in data received\n");
    
    return 0;
}