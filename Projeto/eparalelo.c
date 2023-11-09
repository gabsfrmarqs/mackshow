#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <omp.h>

void fat(int n, mpz_t result)
 {
  if (n == 0) 
{
    mpz_set_ui(result, 1);
  } else
 {
    mpz_t temp;
    mpz_init(temp);
    fat(n - 1, temp);
    mpz_mul_ui(result, temp, n);
    mpz_clear(temp);
  }
}

void EulerTest(int precision, mpf_t result, int num_threads) {
  mpf_t stepResult;
  mpf_init2(result, 1024);  //bits precisão
  mpf_init(stepResult);
  mpz_t fact;
  mpz_init(fact);

  mpf_t *partial_results = (mpf_t *)malloc(num_threads * sizeof(mpf_t));

  for (int i = 0; i < num_threads; ++i) {
    mpf_init(partial_results[i]);
  }

  #pragma omp parallel for num_threads(num_threads)
  for (int i = 0; i <= precision; i++) {
    int tid = omp_get_thread_num();

    mpz_t local_fact;
    mpf_t local_stepResult;
    mpz_init(local_fact);
    mpf_init(local_stepResult);

    fat(i, local_fact);
    mpf_set_z(local_stepResult, local_fact);
    mpf_ui_div(local_stepResult, 1, local_stepResult);
    mpf_add(partial_results[tid], partial_results[tid], local_stepResult);

    mpz_clear(local_fact);
    mpf_clear(local_stepResult);
  }

  for (int i = 0; i < num_threads; ++i) {
    mpf_add(result, result, partial_results[i]);
    mpf_clear(partial_results[i]);
  }

  mpf_clear(stepResult);
  mpz_clear(fact);
  free(partial_results);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <num_threads>\n", argv[0]);
    return 1;
  }

  int n = 0;
  printf("num: ");
  scanf("%d", &n);

  int num_threads = atoi(argv[1]);

  mpf_t result;
  mpf_init(result);

  double start_time = omp_get_wtime();
  EulerTest(n, result, num_threads);
  double end_time = omp_get_wtime();

  gmp_printf("final result %.500Ff\n", result);
  FILE *file = fopen("res.txt", "w");
  if (file != NULL) {
    gmp_fprintf(file, "%.500Ff", result);
    fclose(file);
    printf("saved to res.txt\n");
  } else {
    printf("error saving to file.\n");
  }
  mpf_clear(result);

  return 0;
}

