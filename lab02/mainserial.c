#include <stdio.h>

int GetHalfPoint(int num) {
  int halfPoint, isEven = 0;

  if (num % 2 == 0)
    isEven = 1;

  if (isEven == 1)
    halfPoint = num / 2;

  else
    halfPoint = (num / 2) + 1;
  return halfPoint;
}

int main() {
  int i, num, j, k = 1, l = 1;
  num = 10;
  j = num;

  int halfPoint = GetHalfPoint(num);

  for (k = 1; l < halfPoint; l++)
    k = k * l;//loop da metade de baixo

  printf("The factorial of %d up to %d is %d\n", 1, halfPoint - 1, k);
  
  for (i = 1; j >= halfPoint; j = j - 1)
    i = i * j;//loop da metada de cima

  printf("The factorial of %d up to %d is %d\n", halfPoint, num, i);
  
  printf("The total is = %d\n", i * k);   
  return 0;
}

