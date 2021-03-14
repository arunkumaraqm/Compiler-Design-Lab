# Instructions to install Lex, build and run Lex programs on Cygwin.

Make sure you install flex using
```
apt-cyg install flex m4
```

Write a lex program, say sample.l
```bash
lex sample.l
gcc lex.yy.c -lfl # not -ll
./a < textinput
```

