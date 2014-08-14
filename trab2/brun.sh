gcc -Wall -m32 -Wa,--execstack -g -lm -o a.out main.c gera_func.c
./a.out
