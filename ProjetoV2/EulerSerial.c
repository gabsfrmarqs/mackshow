#include <stdio.h>
#include <gmp.h>

#define MAX_THREADS 1  // Alterado para 1, pois não há mais paralelismo

typedef struct {
    int start;
    int end;
    mpf_t partialResult;
} ThreadData;

// Função para calcular o fatorial
void fat(int n, mpz_t result) {
    mpz_fac_ui(result, n);
}

// Função principal para calcular o resultado de Euler sem paralelismo
void EulerTest(int precision, mpf_t result) {
    mpf_init2(result, 65536);  // Aumenta a precisão ainda mais

    ThreadData threadData;  // Não há mais múltiplas estruturas ThreadData

    int chunkSize = precision;
    int remainder = 0;
    int currentStart = 0;

    threadData.start = currentStart;
    threadData.end = currentStart + chunkSize - 1 + (remainder ? 1 : 0);

    for (int i = threadData.start; i <= threadData.end; i++) {
        mpz_t fact;
        mpf_t stepResult;
        mpz_init(fact);
        mpf_init2(stepResult, 65536);  // Aumenta a precisão ainda mais

        fat(i, fact);
        mpf_set_z(stepResult, fact);

        mpf_ui_div(stepResult, 1, stepResult);

        mpf_add(result, result, stepResult);

        mpf_clear(stepResult);
        mpz_clear(fact);
    }
}

// Função para comparar o resultado com o valor de Euler conhecido
void compareWithActualEuler(const char *actualEulerFile, const char *resultFile) {
    FILE *actualEuler = fopen(actualEulerFile, "r");
    FILE *result = fopen(resultFile, "r");

    if (actualEuler == NULL || result == NULL) {
        printf("Erro ao abrir os arquivos para comparação.\n");
        return;
    }

    int digitCount = 0;
    int correspondingDigits = 0;

    while (1) {
        int actualDigit = fgetc(actualEuler);
        int resultDigit = fgetc(result);

        if (actualDigit == EOF || resultDigit == EOF) {
            break; // Chegou ao final de um dos arquivos
        }

        if ('0' <= actualDigit && actualDigit <= '9' &&
            '0' <= resultDigit && resultDigit <= '9') {
            digitCount++;

            if (actualDigit == resultDigit) {
                correspondingDigits++;
            } else {
                printf("Desajuste encontrado no dígito %d.\n", digitCount);
                break;
            }
        }
    }

    fclose(actualEuler);
    fclose(result);

    printf("Comparação completa.\n");
    printf("Total de dígitos comparados: %d\n", digitCount);
    printf("Dígitos correspondentes: %d\n", correspondingDigits);
}

int main() {
    mpz_t n;
    mpz_init(n);
    printf("Número: ");
    gmp_scanf("%Zd", n);

    mpf_t result;
    EulerTest(mpz_get_ui(n), result);

    gmp_printf("Resultado final %.100000Ff\n", result);

    FILE *file = fopen("res.txt", "w");
    if (file != NULL) {
        gmp_fprintf(file, "%.100000Ff", result);
        fclose(file);
        printf("Salvo em res.txt\n");
    } else {
        printf("Erro ao salvar.\n");
    }

    compareWithActualEuler("num.txt", "res.txt");

    mpz_clear(n);
    mpf_clear(result);

    return 0;
}

