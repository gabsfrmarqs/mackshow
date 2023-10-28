#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
/*
-A estratégia utilizada neste código envolve a criação de uma área crítica para garantir que a variável global_result seja atualizada de forma segura por várias threads, mesmo que várias delas tentem acessar e modificar essa variável simultaneamente.
-Cada thread calcula seu resultado local, armazenando-o na posição apropriada no vetor local_results. Cada thread é responsável por sua própria parte do cálculo.
-Apenas uma thread por vez pode entrar na seção crítica e atualizar a variável global_result.
-Dentro da área crítica, a variável global_result é atualizada somando o valor na posição do vetor local_results correspondente à thread atual.
-Após todas as threads terem terminado de calcular seus resultados locais e atualizar global_result na área crítica, o programa prossegue e, no final, imprime o resultado global.
*/

void Trap(double a, double b, int n, double* global_result_p);

double f(double x)
{
  return exp(x);
}

double Local_Trap(double a, double b, int n)
{
  double h, approx, x_i;
  h = (b - a) / n;
  approx = (f(a) + f(b)) / 2.0;
  for (int i = 1; i <= n - 1; i++)
  {
    x_i = a + i * h;
    approx += f(x_i);
  }
  approx = h * approx;
  return approx;
}

int main(int argc, char* argv[])
{
  double global_result = 0.0;
  double a, b;
  int n;
  int thread_count;

  thread_count = strtol(argv[1], NULL, 10);
  a = 1; b = 10; n = 20;

  double* local_results = (double*)malloc(thread_count * sizeof(double));

  #pragma omp parallel num_threads(thread_count)
  {
    int my_rank = omp_get_thread_num();
    local_results[my_rank] = 0.0;

    #pragma omp for
    for (int i = 0; i < n; i++)
    {
      double local_a = a + i * (b - a) / n;
      double local_b = a + (i + 1) * (b - a) / n;
      local_results[my_rank] += Local_Trap(local_a, local_b, 1);
    }

    #pragma omp critical
    {
      global_result += local_results[my_rank];
    }
  }

  free(local_results);

  printf("Com %d trapezoides, a integral estimada entre %f e %f = %.14e\n", n, a, b, global_result);
  return 0;
}

