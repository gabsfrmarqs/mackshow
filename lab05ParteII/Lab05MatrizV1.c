#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
/*
descrição da estratégia de região crítica neste código:

-Cada thread possui seu próprio vetor temporário temp_y, onde armazena os resultados parciais da multiplicação da matriz pelo vetor. As threads executam um loop paralelo para calcular os resultados parciais sem interferir umas nas outras.
-Após a conclusão do loop, todas as threads tentam entrar em uma seção crítica usando #pragma omp critical. Isso significa que apenas uma thread pode entrar na seção crítica de cada vez.
Dentro da seção crítica, cada thread atualiza o vetor y somando os valores de seu vetor temporário temp_y aos elementos correspondentes do vetor y.
-A seção crítica garante que a atualização de y seja realizada de forma exclusiva, impedindo que múltiplas threads atualizem o mesmo elemento de y simultaneamente, o que poderia levar a resultados incorretos.
  */

// linhas da matriz
#define m 6
// colunas da matriz
#define n 6

double A[m][n] = // matriz
{
  {1.0, 2.0, 3.0, 4.0, 5.0, 6.0},
  {7.0, 8.0, 9.0, 10.0, 11.0, 12.0},
  {13.0, 14.0, 15.0, 16.0, 17.0, 18.0},
  {19.0, 20.0, 21.0, 22.0, 23.0, 24.0},
  {25.0, 26.0, 27.0, 28.0, 29.0, 30.0},
  {31.0, 32.0, 33.0, 34.0, 35.0, 36.0}
};

double x[n] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0}; // vetor multiplicação
double y[m];

int main(int argc, char *argv[]) 
{
  int num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  #pragma omp parallel
  {
    int i, j;
    double temp_y[m] = {0.0}; // Vetor temporário para cada thread
    #pragma omp for
    for (i = 0; i < m; i++) 
    {
      for (j = 0; j < n; j++)
        temp_y[i] += A[i][j] * x[j];
    }
    // Combina os vetores temporários em y usando uma região crítica
    #pragma omp critical
    {
      for (i = 0; i < m; i++)
        y[i] += temp_y[i];
    }
  }

  printf("Resultado (Vetor y):\n");
  for (int i = 0; i < m; i++)
    printf("%lf\n", y[i]);

  return 0;
}

