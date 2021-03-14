%{
	#include <stdio.h>

	int nf_com = 0;
%}

whitespace 	[ \t]*
mc_start	"/*"
mc_end	"*/"

%%

"//".*	{
	nf_com ++;
}

{mc_start}(.|\n)*{mc_end} {
	nf_com ++;
	printf("%s\n\n", yytext);
}

.	{
	fprintf(yyout, "%s", yytext);
}


%%

void main(int argc, char* argv[])
{
	FILE *fin, *fout;
	if (argc != 3)
	{
		perror("Not correct input method.");
		return;
	}
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	
	yyin = fin;
	yyout = fout;
	yylex();
	
	printf("# comments = %d\n", nf_com);
	
	fclose(fin);
	fclose(fout);
}
