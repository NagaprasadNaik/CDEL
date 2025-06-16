%{
#include <stdio.h>
int lines=0,chars=0,words=0,spaces=0;
%}
%%
\n {lines++;}
\t {spaces+=4;}
[ ] {spaces++;}
[^ \t\n#]+ {words++;chars+=yyleng;}
# {return 0;}
%%
int yywrap(){
	return 1;
}
int main(){
	printf("Enter the strign\n");
	yylex();
	printf("Lines :%d\n Chars: %d\n Words: %d\n, Spaces %d\n", lines,chars,words,spaces);
	return 0;
}
