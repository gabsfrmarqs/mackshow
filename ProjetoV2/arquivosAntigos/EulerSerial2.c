#include <stdio.h>
#include <gmp.h>

void fat(int n, mpz_t result) 
{
  if (n == 0) {
    mpz_set_ui(result, 1);
  } else {
    mpz_t temp;
    mpz_init(temp);
    fat(n - 1, temp);
    mpz_mul_ui(result, temp, n);
    mpz_clear(temp);
  }
}

void EulerTest(int precision, mpf_t result) 
{
  mpf_t stepResult;
  mpf_init2(stepResult, 8192);
  mpz_t fact;
  mpz_init(fact);

  mpf_init2(result, 8192);

  for (int i = 0; i <= precision; i++) {
    fat(i, fact);
    mpf_set_z(stepResult, fact);
    mpf_ui_div(stepResult, 1, stepResult);
    mpf_add(result, result, stepResult);
  }

  mpf_clear(stepResult);
  mpz_clear(fact);
}

int main() {
  int n = 0;
  printf("num : ");
  scanf("%d", &n);

  mpf_t result;
  EulerTest(n, result);

  gmp_printf("final result %.2000Ff\n", result);

  // Save the result to a text file
  FILE *file = fopen("res.txt", "w");
  if (file != NULL) {
    gmp_fprintf(file, "%.2000Ff", result);
    fclose(file);
    printf("salvo em res.txt\n");
  } else {
    printf("erro ao salvar.\n");
  }

  mpf_clear(result);

  return 0;
}

