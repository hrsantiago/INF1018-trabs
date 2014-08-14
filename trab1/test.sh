#!/bin/sh

#gcc -Wall -m32 -o teste codifica.c teste.c
gcc -Wall -g -o teste src/codifica.c src/teste.c

./teste

cmp -l output/arquivo1 output/e1
cmp -l output/arquivo2 output/e2
