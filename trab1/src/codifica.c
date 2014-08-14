/* Henrique Rodrigues Santiago 1120671 3WB */

#include <string.h>
#include <stdio.h>
#include "codifica.h"

typedef enum { false, true } bool;

int serializeKey (int fieldNumber, int wireType, FILE *fp)
{
  printf("[serializeKey]: %d, %d\n", fieldNumber, wireType);

  unsigned char byte = (fieldNumber << 3) | wireType;
  if(fwrite(&byte, sizeof(char), 1, fp) != 1)
    return -1;
  return 0;
}

int serializeInteger (int comp2Value, int fieldNumber, FILE *fp, int *offset, bool useZigZag)
{
  printf("[serializeInteger]: %d\n", comp2Value);

  if(fieldNumber >= 0) {
    if(serializeKey(fieldNumber, 0, fp) == -1)
      return -1;
  }

  unsigned int value;
  if(useZigZag)
    value = (comp2Value << 1) ^ (comp2Value >> 31);
  else
    value = comp2Value;

  unsigned char bytes[5];
  int i = 0;
  do {
    bytes[i] = value & 0x7f;
    value >>= 7;

    if(value > 0)
      bytes[i] |= 0x80;

    ++i;
  } while(value > 0);

  if(fwrite(bytes, sizeof(char), i, fp) != i)
      return -1;

  *offset = sizeof(int);
  return 0;
}

int serializeString (char *value, int fieldNumber, FILE *fp, int *offset)
{
  printf("[serializeString]: %s\n", value);

  if(serializeKey(fieldNumber, 2, fp) == -1)
    return -1;

  int len = strlen(value);
  if(serializeInteger(len, -1, fp, offset, false) == -1)
    return -1;

  if(fwrite(value, sizeof(char), len, fp) != len)
    return -1;

  *offset = len + 1;
  return 0;
}

// int serialize (void* values, char *fields, FILE *fp)
int codifica (void* valores, char *campos, FILE *arquivo)
{
  int offset;
  int totalOffset = 0;
  int fieldNumber = 1;
  while(*campos != '\0') {
    if(*campos == 'i') {
      int mod = (totalOffset % sizeof(int));
      if(mod > 0) {
        int padding = sizeof(int) - mod;
        valores += padding;
        totalOffset += padding;
      }

      int i = (*(int*)valores);
      if(serializeInteger(i, fieldNumber, arquivo, &offset, true) == -1)
        return -1;
    }
    else if(*campos == 's') {
      char *c = valores;
      if(serializeString(c, fieldNumber, arquivo, &offset) == -1)
        return -1;
    }
    else {
      printf("Unknown field: %c\n", *campos);
      return -1;
    }

    valores += offset;
    totalOffset += offset;

    ++campos;
    ++fieldNumber;
  }
  return 0;
}
