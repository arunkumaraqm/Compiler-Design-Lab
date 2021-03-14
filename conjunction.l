%{
	#include <stdio.h>

%}

conj (and|or|but|because)

%%

.*" "{conj}" ".*\n	printf("Compound sentence\n");
.*\n	printf("Simple sentence\n");
.	;

	


%%

