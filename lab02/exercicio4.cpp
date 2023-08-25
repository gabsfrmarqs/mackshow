#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main() {
    string nome1 = "Rogerinho";
    string nome2 = "Pereira Sanches";

    if (nome1 < nome2) {
        cout << nome1 << endl << nome2 << endl;
    } else {
        cout << nome2 << endl << nome1 << endl;
    }

  cout << "\nCom string em C: " << endl;

  //Usando string C
  char nome1C[50] = "Zuleide", nome2C[50] = "Tony Peres";

    if (strcmp(nome1C, nome2C) > 0) {
        printf("%s\n%s\n", nome2C, nome1C);
    } else {
        printf("%s\n%s\n", nome1C, nome2C);
    }
    return 0;
}
