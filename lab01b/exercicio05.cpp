#include <iostream>

const int linhas = 3;
const int colunas = 3;

void multiplicarLinha(int matriz[linhas][colunas], int linha, int fator) 
{
    for (int i = 0; i < colunas; ++i) 
      matriz[linha][i] *= fator;
}

void multiplicarColuna(int matriz[linhas][colunas], int coluna, int fator) 
{
    for (int i = 0; i < linhas; ++i) 
      matriz[i][coluna] *= fator;
}

int main() 
{
    int matriz[linhas][colunas] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    int linhaParaMultiplicar = 1; 
    int colunaParaMultiplicar = 2; 
    int fatorLinha = 3;            
    int fatorColuna = 2;           

    std::cout << "Matriz inicial:\n";
    for (int i = 0; i < linhas; ++i) 
    {
        for (int j = 0; j < colunas; ++j) 
          std::cout << matriz[i][j] << " ";

        std::cout << "\n";
    }

    std::cout << "indice da linha multiplicada: " << linhaParaMultiplicar << " ->Fator: " << fatorLinha<<"\n";
    multiplicarLinha(matriz, linhaParaMultiplicar, fatorLinha);

    std::cout << "indice da coluna multiplicada: " << colunaParaMultiplicar << " ->Fator: " << fatorColuna << "\n";
    multiplicarColuna(matriz, colunaParaMultiplicar, fatorColuna);

    std::cout << "Linha multiplicada:\n";
    for (int j = 0; j < colunas; ++j)
      std::cout << matriz[linhaParaMultiplicar][j] << " ";
    std::cout << "\n";

    std::cout << "Coluna multiplicada:\n";
    for (int i = 0; i < linhas; ++i) 
      std::cout << matriz[i][colunaParaMultiplicar] << "\n";
}

