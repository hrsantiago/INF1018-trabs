Relatório do Trabalho 2 de Software Básico desenvolvido no período 2014.1 (INF1018)

- Henrique Rodrigues Santiago - 1120671


O script brun.sh foi criado para compilar e rodar o programa em um único comando.
O script odump.sh foi criado para visualizar o objdump do code.s de maneira mais prática.


Foram realizados 6 testes para garantir a confiabilidade do programa.

O teste 0 foi criado para garantir que a função call_near funciona já que ela não recebe nenhum parâmetro.

Os testes 1,2 e 3 são os exemplos dados no enunciado do trabalho.
Eles testam valores amarrados, troca de ordem dos parâmetros e passagem de ponteiros.

O teste 4 foi criado para testar os parâmetros do tipo char.
Ele verifica se o parâmetro passado de fato é um char e não um int.
printf("Expecting 1: %d\n", f_sum1(256));
Nesse caso, o valor passado para a função será 0 que somado com 1, retorna 1.

O teste 5 foi criado para testar a função encapsulada do módulo gera_func "getStackPosition".
A partir da posição de um dos parâmetros ela calcula a posição dele na pilha.
Se o tipo double não fosse utilizado, todos os tipos ocupariam 4 bytes na pilha.
Dessa maneira, a posição na pilha poderia ser calculada sem a necessidade do for.
"posPilha = 8 + 4 * (param.posicao - 1)"
Como o double ocupa 8 bytes na pilha é necessário varrer todos os parâmetros procurando
por valores não amarrados cuja posição de parâmetro seja menor que a posição de parâmetro procurada.
