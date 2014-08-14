/* Henrique Rodrigues Santiago 1120671 3WB */

#include <stdio.h>
#include <string.h>
#include "codifica.h"

typedef struct {
  int i1;
  int i2;
} S1;
S1 e1 = {1, -1};

typedef struct {
  int i1;
  int i2;
  char s1[3];
  int i3;
} S2;
S2 e2 = {150, -150, "oi", 65632};

typedef struct {
  int i1;
  int i2;
  char s1[21];
  int i3;
} S3;
S3 e3 = {300, 300, "01234567890123456789", 75};

typedef struct {
  char s1[5];
} S4;
S4 e4 = {"abcd"};

typedef struct {
  char s1[6];
  int i1;
} S5;
S5 e5 = {"abcde", 100};

int test(char *filename, void *structure, char *fields)
{
  FILE *fp = fopen(filename, "wb");
  if(!fp) {
    printf("Error opening file.\n");
    return 0;
  }

  printf("Serializing %s\n", filename);
  if(codifica(structure, fields, fp) == -1) {
    printf("Error serializing.\n");
    return 0;
  }

  fclose(fp);
  return 1;
}

int main()
{
  if(!test("output/e1", &e1, "ii"))
    return -1;

  if(!test("output/e2", &e2, "iisi"))
    return -1;

  if(!test("output/e3", &e3, "iisi"))
    return -1;

  if(!test("output/e4", &e4, "s"))
    return -1;

  if(!test("output/e5", &e5, "si"))
    return -1;

  return 0;
}
