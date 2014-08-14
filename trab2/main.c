/* Henrique Rodrigues Santiago 1120671 3WB */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "gera_func.h"

typedef int (*func0_ptr) ();

int ret()
{
  return 2;
}

int test0(void)
{
  printf("** TEST 0 **\n");
  func0_ptr f_ret = NULL;
  f_ret = (func0_ptr) gera_func(&ret, 0, NULL);
  printf("Expecting 2: %d\n", f_ret());
  libera_func(f_ret);
  return 0;
}

typedef double (*func1_ptr) (double x);

int test1(void)
{
  printf("** TEST 1 **\n");
  Parametro params[2];
  func1_ptr f_quadrado = NULL;
  double d;
  int i;

  params[0].tipo = DOUBLE_PAR;
  params[0].amarrado = 0;
  params[0].posicao = 1;
  params[1].tipo = DOUBLE_PAR;
  params[1].amarrado = 1;
  params[1].valor.v_double = 2.0;

  f_quadrado = (func1_ptr) gera_func(pow, 2, params);

  for(i = 1; i <= 10; i++) {
    d = f_quadrado(i);
    printf("%d ^ 2 = %f\n", i, d);
  }

  libera_func(f_quadrado);
  return 0;
}

int boo(int a, int b)
{
  return a-b;
}

typedef int (*func2_ptr) (int x, int y);

int test2(void)
{
  printf("** TEST 2 **\n");
  Parametro params[2];
  func2_ptr foo = NULL;
  int a, b;

  params[0].tipo = INT_PAR;
  params[0].amarrado = 0;
  params[0].posicao = 2;
  params[1].tipo = INT_PAR;
  params[1].amarrado = 0;
  params[1].posicao = 1;

  foo = gera_func(boo, 2, params);
  a = 5; b = 10;
  printf("boo(%d,%d) = %d\n", a, b, boo(a,b));
  printf("foo(%d,%d) = %d\n", a, b, foo(a,b));

  a = 2; b = 10;
  printf("boo(%d,%d) = %d\n", a, b, boo(a,b));
  printf("foo(%d,%d) = %d\n", a, b, foo(a,b));

  return 0;
}

typedef int (*func3_ptr) (void* candidata, size_t n);

char a[] = "quero saber se a outra string é um prefixo dessa aqu";

int test3(void)
{
  printf("** TEST 3 **\n");
  Parametro params[3];
  func3_ptr e_prefixo = NULL;
  char um[] = "quero saber se por acaso falei alguma bobagem";
  int tam;

  params[0].tipo = PTR_PAR;
  params[0].amarrado = 0;
  params[0].posicao = 1; // modificado [1]
  params[1].tipo = PTR_PAR;
  params[1].amarrado = 1;
  params[1].valor.v_ptr = a;
  params[2].tipo = INT_PAR;
  params[2].amarrado = 0;
  params[2].posicao = 2;

  e_prefixo = (func3_ptr) gera_func(memcmp, 3, params);

  tam = 3;
  printf("'%s' e' prefixo-%d de '%s'? %s\n", um, tam, a, e_prefixo(um, tam)?"NAO":"SIM");
  tam = 15;
  printf("%s e' prefixo-%d de '%s'? %s\n", um, tam, a, e_prefixo(um, tam)?"NAO":"SIM");
  tam = 25;
  printf("'%s' e' prefixo-%d de '%s'? %s\n", um, tam, a, e_prefixo(um, tam)?"NAO":"SIM");

  return 0;
}

typedef int (*func4_ptr) (int uc);

int sum1(int uc)
{
  return uc+1;
}

int test4(void)
{
  printf("** TEST 4 **\n");

  Parametro params[1];
  params[0].tipo = CHAR_PAR;
  params[0].amarrado = 0;
  params[0].posicao = 1;

  func4_ptr f_sum1 = gera_func(&sum1, 1, params);
  printf("Expecting 1: %d\n", f_sum1(0));
  printf("Expecting 2: %d\n", f_sum1(1));
  printf("Expecting 50: %d\n", f_sum1(49));
  printf("Expecting 1: %d\n", f_sum1(256));
  printf("Expecting 256: %d\n", f_sum1(255));
  libera_func(f_sum1);
  return 0;
}

typedef double (*func5_ptr) (double x, double y);

int test5(void)
{
  printf("** TEST 5 **\n");
  Parametro params[2];
  func5_ptr f_quadrado = NULL;
  double d;
  int i;

  params[0].tipo = DOUBLE_PAR;
  params[0].amarrado = 0;
  params[0].posicao = 1;
  params[1].tipo = DOUBLE_PAR;
  params[1].amarrado = 0;
  params[1].posicao = 2;

  f_quadrado = (func5_ptr) gera_func(pow, 2, params);

  for(i = 1; i <= 10; i++) {
    d = f_quadrado(2, i);
    printf("2 ^ %d = %f\n", i, d);
  }

  libera_func(f_quadrado);
  return 0;
}

int main()
{
  test0();
  test1();
  test2();
  test3();
  test4();
  test5();
  return 0;
}
