#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

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
