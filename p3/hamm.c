#include <stdio.h>

int main(){
    int data[8], recv[8];
    int c, c0, c1, c2, i;

    printf("4 bit data\n");
    scanf("%d", &data[3]);
    scanf("%d", &data[5]);
    scanf("%d", &data[6]);
    scanf("%d", &data[7]);

    data[1] = (data[3]+data[5]+data[7]) % 2;
    data[2] = (data[3]+data[6]+data[7]) % 2;
    data[4] = (data[5]+data[6]+data[7]) % 2;
    printf("Encoded data : ");
    for(i=1; i<8; i++){
        printf("%d", data[i]);
    }

    printf("\nEneter the recv data: ");
    for(i=1; i<8; i++){
        scanf("%d", &recv[i]);
    }

    c0 = (recv[1] + recv[3] + recv[5] + recv[7]) % 2;
    c1 = (recv[2] + recv[3] + recv[6] + recv[7]) % 2;
    c2 = (recv[4] + recv[5] + recv[6] + recv[7]) % 2;

    c = c2*4 + c1*2 + c0*1;
    printf("\nerror at %d\n", c);

    if(recv[c] == 0)
        recv[c] = 1;
    else
        recv[c] = 0;
    printf("Corrected data : ");
    for(i=1; i<8; i++)
        printf("%d" , recv[i]);

    return 0;
}