%{
	// program to identify variable names
	#include <stdio.h>
	
	int idcnt = 0;
	
	char d_enclose[] = "\033[01;32m%s\033[01;00m" ; //"D[ %s ]D "
	char i1_enclose[] = "\033[01;33m%s\033[01;00m"; //"I1[ %s ]I1 ";
	char i2_enclose[] = "\033[01;34m%s\033[01;00m"; //"I2[ %s ]I2 ";
	
	// no spaces around pipe for dtype
%}

space	[ \t\n]
ide		[a-zA-Z][0-9a-zA-Z]*
dtype	({space}*"int"{space}+)|({space}*"float"{space}+) 
ide_among_spaces {space}*{ide}{space}*

%start vardef

%%

{dtype}		{ 
				// in green
				printf(d_enclose, yytext); 
				BEGIN vardef;				
}

<vardef>{ide_among_spaces}\;	{
				// in yellow
				printf(i1_enclose, yytext);
				idcnt++;
				BEGIN 0;
				
}

<vardef>{ide_among_spaces}\,	{
				// in blue
				printf(i2_enclose, yytext);
				idcnt++;
				
}

.	;

%%

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Invalid usage.\n");
		return 0;
	}
	
	yyin = fopen(argv[1], "r");
	
	yylex();
	printf("No. of identifiers: %d\n", idcnt);
	
	fclose(yyin);
}


