%{
#include <stdio.h>
#include <stdlib.h>
int yyerror();
int yylex();
%}

%token TYPE RET IDEN NUM

%right '='
%left '+' '-'
%left '*' '/'

%%
S: FUN {printf("Accepted\n");exit(0);} ;

FUN: TYPE IDEN '(' PARAMS ')' '{' BODY '}' ;

PARAMS: PARAMS ',' PARAM
|PARAM
|
;

PARAM: TYPE IDEN ;

BODY: STMTS STMT ;

STMTS : STMTS STMT
|
;

STMT: DECL ';' 
| E ';'
| RET E ';'
;

DECL: TYPE IDEN ;

E: IDEN '=' E
| E '+' E
| E '-' E
| E '*' E
| E '/' E
| IDEN
| NUM
;

%%

int yyerror(){
	printf("Error\n");
	return 1;
}

int main(){
	printf("Enetr\n");
	yyparse();
	return 0;
}
