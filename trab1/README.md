Henrique Rodrigues Santiago - 1120671


Teste realizado com a struct abaixo.

struct _test {
  int i1;
  int i2;
  char s1[21];
  int i3;
};

int 4 bytes
int 4 bytes
char 21 bytes
padding 3 bytes
int 4 bytes

valores
i1 = 150
i2 = 300
s1 = "01234567890123456789"
i3 = 73

https://developers.google.com/protocol-buffers/docs/encoding
O resultado obtido com o número 150 foi o mesmo que o exemplo dado no link acima para o número 300.
Aa função "serializeInteger" recebe um inteiro em complemento de 2 e o converte para zigzag.
"zzValue = (comp2Value << 1) ^ (comp2Value >> 31);"
No caso de inteiros positivos, o valor do número é duplicado. No caso, 150 virou 300.
Por este motivo, o teste realizado com 150 deu o mesmo resultado do 300 do link acima.

Nota-se que se "s1" não estiver completamente preenchido o algorítmo não funcionará corretamente,
salvando dados aleatórios no arquivo de saída.

---- Atualizado 06/04/14

Comparei os exemplos disponibilizados no site com os gerados com o programa.
O exemplo 2 ficou diferente. O tamanho da string estava sendo transformado de complemento 2 
para zigzag pelo programa, enquanto no exemplo não.
Como não faz sentido tamanho de string negativo, mudei o código para neste caso não realizar a conversão.
Fiz mais dois testes, além do citado acima, que estão no teste.c.
