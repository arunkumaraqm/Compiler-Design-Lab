%{
	#include <stdio.h>
	#include "y.tab.h"
%}

space	[ \t]
digit	[0-9]
number	{digit}+
%%

a {
	return A;
}
b {
	return B;
}
\n|.	{
	return 0;
}
%%
