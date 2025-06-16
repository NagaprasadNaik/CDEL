%{
#include "prac.tab.h"
int yywrap();
%}

%%
"if" { return IF ; }
"++" { return INCR ; }
"--" { return DECR ; }
"<=" { return LE ;}
">=" { return GE ;}
"=" { return '=' ;}
"<" { return '<' ;}
">" { return '>' ;}
"{"  { return '{' ;}
"}"  { return '}' ;}
"("  { return '(' ;}
")"  { return ')' ;}
";"  { return ';' ;}
[a-zA-Z_][a-zA-Z0-9_]* { return IDEN ; }
[0-9]* { return NUM ; }
[ \t]+ ;
\n { return 0 ; }
. ;

%%

int yywrap(){
	return 1;
}