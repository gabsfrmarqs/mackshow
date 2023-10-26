#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
  return exp(x);
}

double Trap(double a, double b, int n)
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

int main()
{
  double approx = Trap(1,15,25);
 
  printf("Resultado: %f\n", approx);
  return 0;
}

