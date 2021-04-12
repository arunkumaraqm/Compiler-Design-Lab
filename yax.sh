lex $1 && yacc -d $2 && gcc lex.yy.c y.tab.c -ll
