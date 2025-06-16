#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0,j=0,k=0,r=0,l=0;

char arr[30], inp[30], stk[30], temp[30];

void dispstk(){
	printf("\n");
	for(k=0; k<strlen(stk); k++){
		printf("%c", stk[k]);
	}
}

void dispinp(){
	printf("\t\t\t");
	for(k=0; k<strlen(inp); k++){
		printf("%c", inp[k]);
	}
	printf("$");
}

void assign(){
	stk[++j] = arr[i];
	inp[i] = ' ';
	dispstk();
	dispinp();
}

int main(){

	printf("Enter\n");
	gets(inp);
	
	for(k=0; k<strlen(inp); k++){
		arr[k] = inp[k];
	}
	stk[0] = '$';
	
	printf("Stack\t\t\tInput\t\t\tAction");
	dispstk();
	dispinp();
	printf("\t\t\tShift");

	for(i=0; i<strlen(inp); i++){
		switch(arr[i]){
			case 'i': 
				assign();
				printf("\t\t\tReduce E->i");
				stk[j] = 'E';
				dispstk();
				dispinp();
				if(arr[i+1]!='\0')
					printf("\t\t\tShift");
				break;
			case '+':
			case '-':
			case '*':
				assign();
				printf("\t\t\tShift");
				break;
			default:
				printf("String not accepted\n");
				return 0;
		}
	}

	l = strlen(stk);
	while(l>2){
		r=0;
		for(k=l-1; k>=l-3; k--){
			temp[r] = stk[k];
			r++;
		}
		if(strcmp(temp, "E+E")==0 ){
			for(k=l-1; k>=l-3; k--){
				stk[k] = ' ';
			}
			stk[l-3] = 'E';
			printf("\t\t\tReduced by E->");
			for(k=0; k<3; k++)
				printf("%c", temp[k]);
			dispstk();
			dispinp();
			
		}
		else{
			printf("\t\t\tStr not accepted\n");
			return 0;
		}
		l -= 2;
	}
	printf("\t\t\tAccepted");
	return 0;
}
