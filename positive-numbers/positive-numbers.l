%{
	#include <stdio.h>
%}

space	[ \t\n]
digit	[0-9]
number	{digit}+
positive_number \+?{number}
negative_number \-{number}
positive_frac ({positive_number}\.{digit}*)|(\+?\.{number})
negative_frac ({negative_number}\.{digit}*)|(\-\.{number})
%%

{positive_number} printf("positive integer\n");
{negative_number} printf("negative integer\n");
{positive_frac} printf("positive float\n");
{negative_frac} printf("negative float\n");

%%


