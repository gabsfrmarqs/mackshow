#include <iostream>

using namespace std;

int main() {
  const int indiceX = 4, indiceY = 3;
   int matriz[indiceX][indiceY] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1,2,3}};
   int transposta[indiceY][indiceX];

  //Realiza transposição para uma matriz secundária
   for(int i = 0; i < indiceX; i++) {
      for(int j = 0; j < indiceY; j++) {
         transposta[j][i] = matriz[i][j];
      }
   }

  //Imprime a matriz original
   cout << "Matriz original:" << endl;
   for(int i = 0; i < indiceX; i++) {
      for(int j = 0; j < indiceY; j++) {
         cout << matriz[i][j] << " ";
      }
      cout << endl;
   }

  //Imprime a matriz transposta
   cout << "Transposta:" << endl;
   for(int i = 0; i < indiceY; i++) {
      for(int j = 0; j < indiceX; j++) {
         cout << transposta[i][j] << " ";
      }
      cout << endl;
   }
   
   return 0;
}
