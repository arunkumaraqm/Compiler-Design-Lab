# Compiler Design & Systems Software Lab
Lex/Flex and Yacc/Bison Programs 

# Building and Running Lex Programs

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
