#include <stdio.h>
#include <stdlib.h>

#define m 6
#define n 6

double A[m][n] = 
{
  {1.0, 2.0, 3.0, 4.0, 5.0, 6.0},
  {7.0, 8.0, 9.0, 10.0, 11.0, 12.0},
  {13.0, 14.0, 15.0, 16.0, 17.0, 18.0},
  {19.0, 20.0, 21.0, 22.0, 23.0, 24.0},
  {25.0, 26.0, 27.0, 28.0, 29.0, 30.0},
  {31.0, 32.0, 33.0, 34.0, 35.0, 36.0}
};

double x[n] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
double y[m];

void MultMatrizVetor() 
{
  for (int i = 0; i < m; i++) 
  {
    y[i] = 0.0;
    for (int j = 0; j < n; j++) 
      y[i] += A[i][j] * x[j];
  }
}
int main() 
{
  MultMatrizVetor();

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

  return 0;
}



