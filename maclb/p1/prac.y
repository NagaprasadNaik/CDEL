%{
#include <stdio.h>
#include <stdlib.h>
int yyerror();
int yylex();
%}
%%
S:A B
;
A:'a'A'b'
|
;
B:'b'B'c'
|
;
%%
int main(){
	printf("Enetr the string\n");
	yyparse();
	printf("Valid string\n");
}
int yyerror(){
	printf("Invalid String\n");
	exit(1);
}
