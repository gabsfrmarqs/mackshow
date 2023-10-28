#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
esta solução utiliza o reduction. com ele o OpenMP cria uma variável privada para cada thread e realiza a operação de redução nessa variável privada. Após a conclusão da região paralela, as variáveis privadas são combinadas automaticamente em uma única variável global.

Aqui, a linha #pragma omp parallel for reduction(+:y) foi usada após o loop externo para somar os valores parciais em y de todas as threads. Isso permite que cada thread realize sua própria soma parcial em uma variável privada e, no final, o OpenMP combina essas somas parciais para obter o resultado final em y. 

Apesar de não ter região critica explicita, o reduction funciona como se criássemos uma região crítica naquela parte, já que não deixa mais de 1 thread acessá-la ao mesmo tempo.
*/

// Número de linhas da matriz
#define m 6
// Número de colunas da matriz
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

double Local_Mat(int linha) 
{
  int j;
  double result = 0.0;
  for (j = 0; j < n; j++) 
    result += A[linha][j] * x[j];
  return result;
}

int main(int argc, char *argv[]) 
{
  int num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int i;

    #pragma omp for
    for (i = 0; i < m; i++) 
      y[i] = Local_Mat(i);

    #pragma omp for reduction(+:y)
    for (i = 0; i < m; i++)
      y[i] += 0;
  }

  printf("Resultado (Vetor y):\n");
  for (int i = 0; i < m; i++)
    printf("%lf\n", y[i]);

  return 0;
}

