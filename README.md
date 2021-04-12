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

# Building and Running Lex+Yacc Projects

```bash
lex filenamehere.l
yacc -d filenamehere.y
gcc lex.yy.c y.tab.c -ll # use -lfl for flex

./a.out <command line args>
```
Here is a trick to compile in one step:
```bash
# Setup:
# copy yax.sh to current directory
alias yax="sh lexy.sh"

# Usage:
yax filenamehere.l filenamehere.y
./a.out <command line args>
```

I would recommend that you put the shell scripts in a fixed location and add the aliases to your .bashrc or .bash_aliases.


