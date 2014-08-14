/* Henrique Rodrigues Santiago 1120671 3WB */

#include <stdlib.h>
#include <stdio.h>
#include "gera_func.h"

#define MAX_FUNCTION_SIZE 128

// private variables
static unsigned char *m_func;
static unsigned int m_i;

static Parametro *m_params;
static int m_n;

// private functions
static int getStackPosition(int position)
{
  int i, size = 0;
  for(i = 0; i < m_n; ++i) {
    if(!m_params[i].amarrado && m_params[i].posicao < position)
      size += m_params[i].tipo == DOUBLE_PAR ? 2 : 1;
  }
  return 8 + 4 * size;
}

static void push_n_ebp(Parametro param, int n)
{
  int stackPosition = getStackPosition(param.posicao);
  while(n > 0) {
    // push pos(%ebp)
    m_func[m_i++] = 0xff;
    m_func[m_i++] = 0x75;
    m_func[m_i++] = stackPosition + 4 * (n-1);
    --n;
  }
}

static void call_near(void *from, void *to)
{
  unsigned int addr = (unsigned int)(to) - ((unsigned int)(from) + m_i + 5);
  m_func[m_i++] = 0xe8;
  m_func[m_i++] = (addr >> 0);
  m_func[m_i++] = (addr >> 8);
  m_func[m_i++] = (addr >> 16);
  m_func[m_i++] = (addr >> 24);
}

static void ret()
{
  m_func[m_i++] = 0xc3;
}

// public functions
void *gera_func(void *f, int n, Parametro params[])
{
  int j, size = 0;

  m_func = malloc(MAX_FUNCTION_SIZE);
  m_i = 0;
  m_params = params;
  m_n = n;

  // push ebp
  m_func[m_i++] = 0x55;

  // mov esp ebp
  m_func[m_i++] = 0x89;
  m_func[m_i++] = 0xe5;

  // push params
  for(j = n-1; j >= 0; --j) {
    if(params[j].tipo == INT_PAR) {
      if(params[j].amarrado) {
        // push $n
        m_func[m_i++] = 0x68;
        m_func[m_i++] = (params[j].valor.v_int >> 0);
        m_func[m_i++] = (params[j].valor.v_int >> 8);
        m_func[m_i++] = (params[j].valor.v_int >> 16);
        m_func[m_i++] = (params[j].valor.v_int >> 24);
      }
      else
        push_n_ebp(params[j], 1);

      size += 4;
    }
    else if(params[j].tipo == CHAR_PAR) {
      if(params[j].amarrado) {
        // push $n
        m_func[m_i++] = 0x6a;
        m_func[m_i++] = params[j].valor.v_char;
      }
      else
        push_n_ebp(params[j], 1);

      size += 4;
    }
    else if(params[j].tipo == DOUBLE_PAR) {
      if(params[j].amarrado) {
        // mov &valor, %eax
        m_func[m_i++] = 0xb8;
        m_func[m_i++] = ((unsigned int)&params[j].valor >> 0);
        m_func[m_i++] = ((unsigned int)&params[j].valor >> 8);
        m_func[m_i++] = ((unsigned int)&params[j].valor >> 16);
        m_func[m_i++] = ((unsigned int)&params[j].valor >> 24);

        // push 4(%eax)
        m_func[m_i++] = 0xff;
        m_func[m_i++] = 0x70;
        m_func[m_i++] = 4;

        // push 0(%eax)
        m_func[m_i++] = 0xff;
        m_func[m_i++] = 0x70;
        m_func[m_i++] = 0;
      }
      else
        push_n_ebp(params[j], 2);

      size += 8;
    }
    else if(params[j].tipo == PTR_PAR) {
      if(params[j].amarrado) {
        // push $n
        m_func[m_i++] = 0x68;
        m_func[m_i++] = ((unsigned int)params[j].valor.v_ptr >> 0);
        m_func[m_i++] = ((unsigned int)params[j].valor.v_ptr >> 8);
        m_func[m_i++] = ((unsigned int)params[j].valor.v_ptr >> 16);
        m_func[m_i++] = ((unsigned int)params[j].valor.v_ptr >> 24);
      }
      else
        push_n_ebp(params[j], 1);

      size += 4;
    }
  }

  call_near(m_func, f);

  // add size, esp
  if(size > 0) {
    m_func[m_i++] = 0x83;
    m_func[m_i++] = 0xc4;
    m_func[m_i++] = size;
  }

  // mov ebp esp
  m_func[m_i++] = 0x89;
  m_func[m_i++] = 0xec;

  // pop ebp
  m_func[m_i++] = 0x5d;

  ret();

  return (void*)m_func;
}

void libera_func(void* func)
{
  free(func);
}
