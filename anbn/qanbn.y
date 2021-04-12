%{

	#include <stdbool.h>
	#include <stdio.h>
	bool valid = true;
	
%}

%name parse
%token A B

%%

e: A B	{
}

| A e B {
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
