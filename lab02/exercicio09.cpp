#include <iostream>

const int linhas = 3;
const int colunas = 3;

void substituirNegativosPorModulo(int matriz[linhas][colunas]) 
{
    for (int i = 0; i < linhas; ++i) 
    {
        for (int j = 0; j < colunas; ++j) 
        {
            if (matriz[i][j] < 0)
                matriz[i][j] = -matriz[i][j];
        }
    }
}

int main() {
    int matriz[linhas][colunas] = { {1, -2, 3}, {-4, 5, -6}, {7, -8, 9} };

    std::cout << "Matriz original:\n";
    for (int i = 0; i < linhas; ++i) 
    {
        for (int j = 0; j < colunas; ++j)
            std::cout << matriz[i][j] << " ";
        std::cout << "\n";
    }

    substituirNegativosPorModulo(matriz);

    std::cout << "Matriz apos substituio:\n";
    for (int i = 0; i < linhas; ++i) 
    {
        for (int j = 0; j < colunas; ++j) 
            std::cout << matriz[i][j] << " ";
        std::cout << "\n";
    }

}

