#include <stdio.h>
#include <gmp.h>
#include <pthread.h>

#define MAX_THREADS 4  


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct {
  int start;
  int end;
  mpf_t partialResult;
} ThreadData;

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

void* threadFunction(void* arg) {
  ThreadData* data = (ThreadData*)arg;
  mpf_init2(data->partialResult, 16384);

  for (int i = data->start; i <= data->end; i++) {
    mpz_t fact;
    mpf_t stepResult;
    mpz_init(fact);
    mpf_init2(stepResult,16384);

    fat(i, fact);
    mpf_set_z(stepResult, fact);


    pthread_mutex_lock(&mutex);
    mpf_ui_div(stepResult, 1, stepResult);
    mpf_add(data->partialResult, data->partialResult, stepResult);
    pthread_mutex_unlock(&mutex);

    mpf_clear(stepResult);
    mpz_clear(fact);
  }

  pthread_exit(NULL);
}

void EulerTest(int precision, mpf_t result) {
  mpf_t stepResult;
  mpf_init2(stepResult,16384);  
  mpz_t fact;
  mpz_init(fact);

  mpf_init2(result,16384);  

  pthread_t threads[MAX_THREADS];
  ThreadData threadData[MAX_THREADS];

  int chunkSize = precision / MAX_THREADS;
  int remainder = precision % MAX_THREADS;
  int currentStart = 0;


  for (int i = 0; i < MAX_THREADS; i++) {
    threadData[i].start = currentStart;
    threadData[i].end = currentStart + chunkSize - 1 + (i < remainder ? 1 : 0);
    currentStart = threadData[i].end + 1;

    pthread_create(&threads[i], NULL, threadFunction, &threadData[i]);
  }

  for (int i = 0; i < MAX_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }


  for (int i = 0; i < MAX_THREADS; i++) {
    pthread_mutex_lock(&mutex);
    mpf_add(result, result, threadData[i].partialResult);
    pthread_mutex_unlock(&mutex);

    mpf_clear(threadData[i].partialResult);
  }

  mpf_clear(stepResult);
  mpz_clear(fact);
}

void compareWithActualEuler(const char *actualEulerFile, const char *resultFile) {
  FILE *actualEuler = fopen(actualEulerFile, "r");
  FILE *result = fopen(resultFile, "r");

  if (actualEuler == NULL || result == NULL) {
    printf("Error opening files for comparison.\n");
    return;
  }

  int digitCount = 0;
  int correspondingDigits = 0;

  while (1) {
    int actualDigit = fgetc(actualEuler);
    int resultDigit = fgetc(result);

    if (actualDigit == EOF || resultDigit == EOF) {
      break; // Reached the end of one of the files
    }

    if ('0' <= actualDigit && actualDigit <= '9' &&
        '0' <= resultDigit && resultDigit <= '9') {
      digitCount++;

      if (actualDigit == resultDigit) {
        correspondingDigits++;
      } else {
        printf("Mismatch found at digit %d.\n", digitCount);
        break;
      }
    }
  }

  fclose(actualEuler);
  fclose(result);

  printf("Comparison complete.\n");
  printf("Total digits compared: %d\n", digitCount);
  printf("Corresponding digits: %d\n", correspondingDigits);
}

int main() {
  mpz_t n;
  mpz_init(n);
  printf("num : ");
  //scanf("%d", &n);
  gmp_scanf("%Zd", n);


  mpf_t result;
  EulerTest(mpz_get_ui(n), result);

  gmp_printf("final result %.10000Ff\n", result);

  FILE *file = fopen("res.txt", "w");
  if (file != NULL) {
    pthread_mutex_lock(&mutex);
    gmp_fprintf(file, "%.10000Ff", result);
    pthread_mutex_unlock(&mutex);
    fclose(file);
    printf("salvo em res.txt\n");
  } else {
    printf("erro ao salvar.\n");
  }

  compareWithActualEuler("num.txt", "res.txt");

  mpz_clear(n);
  mpf_clear(result);

  return 0;
}

