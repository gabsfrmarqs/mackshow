#include <iostream>

using namespace std;

//função para obter o tamanho da string sem usar length()
int tamanhoString(char* p) {
    int count = 0;
    while (*p != '\0') {
        count++;
        p++;
    }
    return count;
}

int main() {
  char trecho[] = "Old World Underground, where are you now?";

  //Caractere de busca
  char busca = 'g';
  int tamanho = tamanhoString(trecho);

  bool encontrado = false;
  for(int i = 0; i < tamanho; i++){
    if (trecho[i] == busca){
      encontrado = true;
      cout << "Caractere encontrado no índice " << i << endl;
    }
  }

  if (encontrado == false){
    cout << "O caractere não foi encontrado." << endl;
  }
}
