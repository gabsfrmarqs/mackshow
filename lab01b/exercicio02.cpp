#include <iostream>

using namespace std;

int main() {
  int numNotas = 4;
  float notas[4] = {8, 8, 7, 8};
  float soma = notas[0] + notas[1] * 2 + notas[2] * 3 + notas[3];
  soma = soma / 7;
  cout << "Média: " << soma << endl;
  cout << "Conceito: ";
  if (soma < 4) {
    cout << 'E';
  } else if (soma >= 4 && soma < 6) {
    cout << 'D';
  } else if (soma >= 6 && soma < 7.5) {
    cout << 'C';
  } else if (soma >= 7.5 && soma < 9) {
    cout << 'B';
  } else if (soma >= 9) {
    cout << 'A';
 }
  cout << endl;
  return 0;
}
