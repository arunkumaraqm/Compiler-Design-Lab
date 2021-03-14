%{
	int ccnt = 0, lcnt = 0;
%}

%%

. ccnt++;
\n {lcnt++; ccnt++;}

%%
int main(int argc, char* argv[])
{
	FILE* fd;
	fd = fopen(argv[1], "r");
	yyin = fd; // alternatively use yyset_in(fd)
	yylex();
	printf("%d chars in %d lines\n", ccnt, lcnt);
	fclose(fd);
	return 0;
}