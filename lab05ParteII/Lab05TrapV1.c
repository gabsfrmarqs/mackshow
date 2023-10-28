#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
/*
-Dentro da região paralela, cada thread inicializa sua própria variável global_result com 0.0. Cada thread possui uma cópia separada desta variável.
-Em seguida, o programa entra em outra região paralela com #pragma omp parallel, criando mais threads. Dentro desta região paralela, a cláusula reduction(+:global_result) é usada para somar os resultados locais de cada thread à variável global_result.
-Cada thread executa a função Local_Trap(a, b, n), que calcula a integral local para o intervalo [a, b] usando o método dos trapézios. Essa integral local é adicionada à variável global_result dentro da região paralela.
-Após a região paralela, o programa espera que todas as threads terminem e, em seguida, imprime o resultado global da integral.
*/

void Trap(double a, double b, int n, double* global_result_p);

double f(double x)
{
  return exp(x);
}

double Local_Trap(double a, double b, int n)
{
  double h,approx,x_i;
  h = (b-a)/n;
  approx = (f(a) + f(b))/2.0;
  for (int i =1; i<= n-1;i++)
    {
      x_i = a + i*h;
      approx += f(x_i);
    }
  approx = h*approx;
  return approx;
}

int main(int argc, char* argv[]) 
{
  double global_result = 0.0;
  double a, b;
  int n;
  int thread_count;

  thread_count = strtol(argv[1], NULL,10);
  a=1; b=10; n=20;
  #pragma omp parallel num_threads(thread_count)
  {
    global_result = 0.0;
    # pragma omp parallel num_threads(thread_count)\
      reduction(+:global_result)
    global_result += Local_Trap(a,b,n);
  }

  printf("com %d trapezoides, a integral estimada, entre %f e  %f = %.14e\n",n,a,b,global_result);
 return 0;
}
