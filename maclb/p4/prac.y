
%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(const char *s);
int count=0;
%}

%token IF IDEN NUM
%token LE GE INCR DECR

%%
S: I ;
I: IF A B { count++ ; } ;
A: '(' E ')' ;
E: IDEN Z IDEN
 | IDEN Z NUM
 | IDEN U
 | IDEN
 ;
Z: '='
 | '<'
 | '>'
 | LE
 | GE
 ;
U: INCR
 | DECR
 ;
B: '{' B '}' 
 | I
 | E ';'
 |
 ;
%%

int yyerror(const char *s){
	printf("error %s\n", s);
	return 1;
}

int main(){
	printf("Enetr: \n");
	yyparse();
	printf("count: %d\n", count);
	return 0;
}