%{
#include <stdio.h>
int posint=0, negint=0, posfrac=0, negfrac=0;
%}

num [0-9]+
posint \+?{num}
negint -{num}
posnum \+?{num}\.{num}?|\+?\.{num}
negnum -{num}\.{num}?|-\.{num}


%%
{posint} posint++;
{negint} negint++;
{posnum} posfrac++;
{negnum} negfrac++;


{posnum}\/{posnum} |
{negnum}\/{negnum} posfrac++;

{posnum}\/{negnum} |
{negnum}\/{posnum} negfrac++;

[ \t] ;

\n return 0;

. ECHO;
%%

int yywrap(){
	return 1;
}
int main(){
	yylex();
	printf("Posint: %d\n Negint: %d\n Posfrac: %d\n Negfrac: %d\n",posint,negint,posfrac,negfrac);
	return 0;
}
