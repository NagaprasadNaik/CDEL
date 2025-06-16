%{
#include "prac.tab.h"
int yywrap();
%}

%%
"void"|"int"|"float"|"char" {return TYPE;}
"return" {return RET;}
[a-zA-Z_][a-zA-Z0-9_]* {return IDEN;}
[0-9]+ {return NUM;}
[ \t\n] ;
. {return yytext[0];}
%%
int yywrap(){
	return 1;
}
