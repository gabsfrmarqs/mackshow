#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <omp.h>

void fat(int n, mpz_t result) {
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

void EulerTest(int precision, mpf_t result, int num_threads) {
  mpf_t stepResult;
  mpf_init2(stepResult, 8192);
  mpz_t fact;
  mpz_init(fact);

  mpf_init2(result, 8192);

  mpf_t* local_results = (mpf_t*)malloc(num_threads * sizeof(mpf_t));
  for (int i = 0; i < num_threads; ++i) {
    mpf_init2(local_results[i], 8192);
  }

  #pragma omp parallel num_threads(num_threads)
  {
    int tid = omp_get_thread_num();
    #pragma omp for
    for (int i = 0; i <= precision; i++) {
      fat(i, fact);
      mpf_set_z(stepResult, fact);
      mpf_ui_div(stepResult, 1, stepResult);
      mpf_add(local_results[tid], local_results[tid], stepResult);
    }
  }

  for (int i = 0; i < num_threads; ++i) {
    mpf_add(result, result, local_results[i]);
    mpf_clear(local_results[i]);
  }

  mpf_clear(stepResult);
  mpz_clear(fact);
  free(local_results);
}

int main(int argc, char *argv[]) {

  int num_threads = atoi(argv[1]);

  int n;
  printf("Digite a precisão: ");
  scanf("%d", &n);

  mpf_t result;
  mpf_init(result);

  EulerTest(n, result, num_threads);

  gmp_printf("resultado final %.2000Ff\n", result);

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

