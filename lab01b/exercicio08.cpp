#include <iostream>

using namespace std;

void transposicao(int linhas, int colunas, int **matriz, int **transposta) {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      transposta[j][i] = matriz[i][j];
    }
  }
}

int main() {
  const int colunas = 5, linhas = 4;

  //Aloca memória para a matriz original
  int **matriz = new int*[linhas];
  for(int i = 0; i < linhas; ++i) {
    matriz[i] = new int[colunas];
  }

  //Aloca memória para transposta
  int **transposta = new int*[colunas];
  for(int i = 0; i < colunas; ++i) {
    transposta[i] = new int[linhas];
  }

  //Inicia a matriz original com valores de 1 a colunas * linhas
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      matriz[i][j] = i * colunas + j + 1;
    }
  }

  transposicao(linhas, colunas, matriz, transposta);

  //Imprime a matriz original
  cout << "Matriz original:" << endl;
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }

  //Imprime a matrix transposta
  cout << "Transposta:" << endl;
  for (int i = 0; i < colunas; i++) {
    for (int j = 0; j < linhas; j++) {
      cout << transposta[i][j] << " ";
    }
    cout << endl;
  }

  //Desaloca
  for(int i = 0; i < linhas; ++i) {
    delete[] matriz[i];
  }
  delete[] matriz;

  for(int i = 0; i < colunas; ++i) {
    delete[] transposta[i];
  }
  delete[] transposta;

  return 0;
}

