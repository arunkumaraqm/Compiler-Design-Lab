%{
	#include <stdio.h>
	#include "y.tab.h"
	extern char yylval[100];
%}

space	[ \t]
digit	[0-9]
number	{digit}+
%%

[_a-zA-Z] {
	//yylval = yytext;
	return LETTER;
}
{digit} {
	//yylval = yytext;
	return DIGIT;
}
.	{
	return 0;
}
\n	{
	return 0;
}
%%
