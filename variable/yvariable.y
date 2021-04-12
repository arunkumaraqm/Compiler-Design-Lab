%{

	#include <stdbool.h>
	#include <stdio.h>
	bool valid = true;
	
%}

%name parse
%token LETTER DIGIT

%%

e: LETTER	{
//	printf("e:LETTER [%c]\n", $1);
}

| e LETTER {
	//printf("e: e LETTER [%d %c]\n", $1, $2);
}

| e DIGIT {
	//printf("e: e DIGIT [%d %c]\n", $1, $2);
}

%%
	
int yyerror()
{
	valid = false;
}

int main()
{
	yyparse();
	printf("\n");
	if (!valid)
	{
		printf("Invalid.");
	}
	else
	{
		printf("Valid.");
	}
	return 0;
}
