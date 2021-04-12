%{

	#include <stdbool.h>
	#include <stdio.h>
	bool valid = true;
	
	//fix changing [ to -
	
%}

%token NUM
%left '+' '-'
%left '*' '/'
%left '['

%%

e: NUM	{
	printf("e:NUM [%d]\n", $1);
	$$ = $1;
	yylval = $$;
}

| e'+'e {
	printf("e+e [%d %d]\n", $1, $3);
	$$ = $1 + $3;
	yylval = $$;
}

| e'-'e {
	printf("e-e [%d %d]\n", $1, $3);
	$$ = ($1 - $3);
	yylval = $$;
}

| e'*'e {
	printf("e*e [%d %d]\n", $1, $3);
	$$ = $1 * $3;
	yylval = $$;
}

| e'/' e {
	printf("e/e [%d %d]\n", $1, $3);
	if ($3)
	{
		$$ = $1 / $3;
		yylval = $$;
	}
	else
	{
		valid = false;
	}
}

| '(' e ')' {
	printf("(e) [%d]\n", $2);
	$$ = $2;
	yylval = $$;
}

| '[' e {
	$$ = -$2;
	yylval = $$;
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
	else	printf("Result = %d", yylval);
	return 0;
}
