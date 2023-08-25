#include <stdio.h>

#define LINHAS 3
#define COLUNAS 3

void somarLinhas(int matriz[LINHAS][COLUNAS], int linha1, int linha2) 
{
    for (int j = 0; j < COLUNAS; ++j)
        matriz[linha2][j] += matriz[linha1][j];
}

void multiplicarLinhas(int matriz[LINHAS][COLUNAS], int linha1, int linha2) 
{
    for (int j = 0; j < COLUNAS; ++j)
        matriz[linha2][j] *= matriz[linha1][j];
}

int main() 
{
    int matriz[LINHAS][COLUNAS] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    int linha1 = 0;
    int linha2 = 1;

    printf("Matriz original:\n");
    for (int i = 0; i < LINHAS; ++i)
    {
        for (int j = 0; j < COLUNAS; ++j) 
            printf("%d ", matriz[i][j]);

        printf("\n");
    }

    somarLinhas(matriz, linha1, linha2);

    printf("Matriz apos soma da linha %d na linha %d:\n", linha1+1, linha2+1);
    for (int i = 0; i < LINHAS; ++i) 
    {
        for (int j = 0; j < COLUNAS; ++j)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }

    multiplicarLinhas(matriz, linha1, linha2);

    printf("Matriz apos multiplicacao da linha %d na linha %d:\n", linha1+1, linha2+1);
    for (int i = 0; i < LINHAS; ++i) 
    {
        for (int j = 0; j < COLUNAS; ++j) 
            printf("%d ", matriz[i][j]);

        printf("\n");
    }

    return 0;
}

