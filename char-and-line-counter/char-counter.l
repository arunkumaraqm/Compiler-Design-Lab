%{
	int ccnt = 0, lcnt = 0;
%}

%%

. ccnt++;
\n {lcnt++; ccnt++;}

%%
int main()

{
	yylex();
	printf("%d chars in %d lines", ccnt, lcnt);
	return 0;
}