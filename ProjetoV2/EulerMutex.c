#include <stdio.h>
#include <gmp.h>
#include <pthread.h>

#define MAX_THREADS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
    mpf_t partialResult;
} ThreadData;

// Função para calcular o fatorial
void fat(int n, mpz_t result) {
    mpz_fac_ui(result, n);
}

// Função executada por cada thread
void* threadFunction(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    mpf_init2(data->partialResult, 65536);  // Aumenta a precisão ainda mais

    for (int i = data->start; i <= data->end; i++) {
        // Declaração
        mpz_t fact;
        mpf_t stepResult;
        // Alocação de memória e inicia as variáveis como 0
        mpz_init(fact);
        mpf_init2(stepResult, 65536);  // Aumenta a precisão ainda mais

        fat(i, fact);

	// Converte o fatorial de fact (inteiro GMP) para ponto flutuante e armazena em stepResult
        mpf_set_z(stepResult, fact);

	// Calcula o inverso do valor armazenado no stepResult e armazena o resultado na própria variável
        mpf_ui_div(stepResult, 1, stepResult);

	// Soma o stepResult com o data->PartialResult e armazena em partialResult de novo
        mpf_add(data->partialResult, data->partialResult, stepResult);

	// Desaloca
        mpf_clear(stepResult);
        mpz_clear(fact);
    }

    // Encerra execução da thread
    pthread_exit(NULL);
}

// Função principal para calcular o resultado de Euler
void EulerTest(int precision, mpf_t result) {
    // Inicia a variável com a precisão de 65536 bits
    mpf_init2(result, 65536);  // Aumenta a precisão ainda mais

    // Declara array de threads e array de structs ThreadData
    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];

    // A precisão será dividida pelo número de threads e será armazenada no ChunkSize. 
    // Remainder calculará o resto da divisão. 
    int chunkSize = precision / MAX_THREADS;
    int remainder = precision % MAX_THREADS;
    int currentStart = 0;

    // As estruturas ThreadData serão preenchidas com os intervalos que deverão ser processados por cada thread
    for (int i = 0; i < MAX_THREADS; i++) {
        threadData[i].start = currentStart;
        threadData[i].end = currentStart + chunkSize - 1 + (i < remainder ? 1 : 0);
        currentStart = threadData[i].end + 1;

	// Cria a thread
        pthread_create(&threads[i], NULL, threadFunction, &threadData[i]);
    }

    // Aguarda a conclusão da thread para prosseguir
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Soma os resultados parciais e limpa a memória
    for (int i = 0; i < MAX_THREADS; i++) {
        mpf_add(result, result, threadData[i].partialResult);
        mpf_clear(threadData[i].partialResult);
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

    // Declara o n de precisão
    // mpz_t declara inteiro de precisão arbitrária
    mpz_t n;
    mpz_init(n);
    printf("Número: ");
    gmp_scanf("%Zd", n);

    // Declara a variável de resultado
    // mpf_t declara float de precisão arbitrária
    mpf_t result;
    EulerTest(mpz_get_ui(n), result);

    // Printa o valor na tela com o próprio gmp
    gmp_printf("Resultado final %.100000Ff\n", result);

    // Salva os dados no res.txt
    FILE *file = fopen("res.txt", "w");
    if (file != NULL) {
        gmp_fprintf(file, "%.100000Ff", result);
        fclose(file);
        printf("Salvo em res.txt\n");
    } else {
        printf("Erro ao salvar.\n");
    }
	
    // Chama o comparador
    compareWithActualEuler("num.txt", "res.txt");


    // Limpa a memória alocada
    mpz_clear(n);
    mpf_clear(result);

    return 0;
}
