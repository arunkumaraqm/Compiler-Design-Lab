<h1>Lex Program to Recognize Positive and Negative Integers and Floating Point Numbers</h1>

Lex is a utility that generates lexical analyzers. A Lex program consists of three sections, separated by `%%`:

* Definition section (optional)
	* Defining macros
	* Importing headers
	* Any C code
* Rules section (mandatory)
	* Associating regex patterns with actions written in C
* C code (optional)

In the definition section, we include `stdio.h` for `printf`. We also define various macros:

* `digit [0-9]` Any character between 0 and 9
* `number {digit}+` One or more digits.
* `negative_number \-{number}` A hyphen followed by a number. The minus sign is escaped with a backslash. 
* `positive_number \+?{number}` A plus sign followed by a number or just the number. The question mark indicates zero or one of the preceding character. The plus sign is escaped with a backslash.
* `negative_frac ({negative_number}\.{digit}*)|(\-\.{number})` There are two conditions here. The pipe character indicates an OR.
	* `{negative_number}\.{digit}*)` A negative number followed by a period, followed by zero or more digits. The period is escaped.
	* `(\-\.{number})` The minus sign followed by a period, followed by a number. Eg: -.890
* `positive_frac ({positive_number}\.{digit}*)|(\+?\.{number})` Similar to previous.

Be careful not to include unnecessary spaces. Lex parsing error messages may not be helpful.

In the rules section, we check for the appearance of these macros and display corresponding message.

```c
%{
	#include <stdio.h>
%}

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
```

Contrary to most Lex programs that you will see, this program does not take any file as input. It will read the input from stdin and print to stdout.

To compile and run,
```bash
lex filenamehere.l
gcc lex.yy.c -ll # use -lfl for flex

./a.out <command line args>
```
A two step compilation is not convenient if you are using the terminal. Here is a trick to compile in one step:
```bash
# Setup:
echo "lex \$1 && gcc lex.yy.c -ll" > lexy.sh
alias lexy="sh lexy.sh"

# Usage:
lexy my_lex_program.l
./a.out <command line args>
```

Here is some sample I/O:
```
9
positive number

+9
positive number

+90
positive number

-89
negative number

0
positive number

0.5
positive fraction

.5
positive fraction

-.5
negative fraction

-0.5
negative fraction

23.43
positive fraction

+23.43
positive fraction

-23.43
negative fraction

-.43
negative fraction

+.43
positive fraction

.43
positive fraction

1.
positive fraction

432.
positive fraction

-543.
negative fraction
```

A known issue with this program is that even though zero is neither positive or negative, it will be classified as one of those. Fixing this issue is left as an exercise.



