%{
	#include <stdio.h>
	#include "y.tab.h"
	
	extern int yylval;
%}

space	[ \t]
digit	[0-9]
number	{digit}+
%%

{number}	{
	yylval = atoi(yytext);
//	printf("%d", yylval);
	return NUM;
}

\n	return 0;
\t	;
.	{
	return yytext[0]; // yytext only has one char anyway
}

%%
