%{
#include <stdio.h>
int id=0, op=0, key=0;
%}

%%
"int"|"float"|"if"|"for"|"return"|"while" {printf("keyword\n");key++;}
[a-zA-Z_][a-zA-Z0-9_]* {printf("identifier\n");id++;}
[\+\-\*\/\%\=\^] {printf("operator\n");op++;}
[ \t] ;
. ;
\n {return 0;}
%%

int yywrap(){
	return 1;
}

int main(){

	printf("Enter \n");
	yylex();
	printf("ID: %d\n KEY: %d\n OP: %d\n", id, key, op);
	return 0;
}
