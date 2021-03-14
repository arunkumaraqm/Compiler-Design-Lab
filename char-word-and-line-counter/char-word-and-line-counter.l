%{
	int char_cnt = 0;
	int word_cnt = 0;
	int blank_cnt = 0;
	int line_cnt = 0;
%}

WORD 	[^ \t\n]+
EOL 	\n

%%

[ ]		{
			blank_cnt++;
			char_cnt++;
		}
{WORD}	{
			word_cnt++;
			char_cnt += yyleng;
		}
{EOL}	{
			line_cnt++;
		}
%%

int main(int argc, char* argv[])
{
	FILE* fd;
	if (argc > 1)
	{
		fd = fopen(argv[1], "r");
		if (!fd)
		{
			printf("Error opening.\n");
			exit(1);
		}

		yyin = fd;
		yylex();

		printf("char_cnt = %d\n", char_cnt);
		printf("word_cnt = %d\n", word_cnt);
		printf("line_cnt = %d\n", line_cnt);
		printf("blank_cnt = %d\n", blank_cnt);
	}
	else
	{
		printf("Usage: argv[0] argv[1]\n");
	}
}