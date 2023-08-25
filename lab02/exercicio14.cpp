#include <iostream>

using namespace std;

int tamanhoString(char *p) {
  int count = 0;
  while (*p != '\0') {
    count++;
    p++;
  }
  return count;
}

void inserirCaractere(char str[], int posicao, char inserir, int tamanho) {
  for (int i = tamanho; i >= posicao; i--) {
    str[i + 1] = str[i];
  }
  str[posicao] = inserir;
}

int main() {
  char str[100] = "Old world underground, where are you now?";

  int posicao = 21; //Índice de inserção
  char inserir = '!';
  int tamanho = tamanhoString(str);

  cout << "String original: " << str << endl;
  inserirCaractere(str, posicao, inserir, tamanho);
  cout << "String após inserção em " << posicao << ": " << str << endl;
}

