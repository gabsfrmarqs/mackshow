#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Número de linhas da matriz
#define m 6
// Número de colunas da matriz
#define n 6
// Número de threads -> 1 por linha
#define thread_count 6

double A[m][n] = //matriz
{
  {1.0, 2.0, 3.0, 4.0, 5.0, 6.0},
  {7.0, 8.0, 9.0, 10.0, 11.0, 12.0},
  {13.0, 14.0, 15.0, 16.0, 17.0, 18.0},
  {19.0, 20.0, 21.0, 22.0, 23.0, 24.0},
  {25.0, 26.0, 27.0, 28.0, 29.0, 30.0},
  {31.0, 32.0, 33.0, 34.0, 35.0, 36.0}
};

double x[n] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};;//vetor multiplicação
double y[m];

void *Pth_mat_vect(void *rank) //esse é o cod. que o prof passou
{
  long my_rank = (long)rank;
  int i, j;
  int local_m = m / thread_count;
  int my_first_row = my_rank * local_m;
  int my_last_row = (my_rank + 1) * local_m - 1;
  
  for (i = my_first_row; i <= my_last_row; i++) 
  {
    y[i] = 0.0;
    for (j = 0; j < n; j++)
      y[i] += A[i][j] * x[j];
  }
  return NULL;
}

int main() 
{
  pthread_t *thread_ids;
  long thread;
  
  thread_ids = malloc(thread_count * sizeof(pthread_t));
  
  for (thread = 0; thread < thread_count; thread++)//cria e fazendo mult
    pthread_create(&thread_ids[thread], NULL, Pth_mat_vect, (void *)thread);
  
  for (thread = 0; thread < thread_count; thread++)//junta os resultados
    pthread_join(thread_ids[thread], NULL);
  
  free(thread_ids);
   
    printf("Matriz A:\n");
    for (int i = 0; i < m; i++) 
    {
      for (int j = 0; j < n; j++) 
        printf("%lf ", A[i][j]);
      printf("\n");
    }

  printf("Vetor x:\n");
  for (int i = 0; i < n; i++)
    printf("%lf\n", x[i]);

  printf("Resultado (Vetor y):\n");
  for (int i = 0; i < m; i++)
    printf("%lf\n", y[i]);
}
