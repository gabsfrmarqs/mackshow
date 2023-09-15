# Lab03

Atividade executada no dia 15/09.

### Crie um código-fonte que utilize fork() e shmget() entre 2 processos (pai e filho). Seu código deve garantir que:
- o processo pai e o processo filho compartilhem uma variável simples (por exemplo, inteiro - valor 1)
- o processo pai imprime o valor inicial dessa variável; em seguida, cria o processo filho e espera-o
- o processo filho acessa esta variável, realiza uma operação (por exemplo, adição - valor 2, totalizando 3), modificando o valor; em seguida, o processo filho termina
- o processo pai realiza uma outra operação (por exemplo, multiplicação - valor 4, totalizando 12), modificando novamente o valor, e imprime novamente a variável

Compilado via GCC na AWS
Executado pelo comando "./lab"
Os valores foram alterados na região de memória.

![imagem][lab03.png]

i
