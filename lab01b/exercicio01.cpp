#include <iostream>
#include <climits>
//1. Crie um programa capaz de ler os dados de uma matriz quadrada de inteiros.
//Ao final da leitura o programa deverá imprimir o número da linha que contém o 
//menor dentre todos os números lidos.

int main()
{
	int matriz[4][4] =
	{
		{7,9,43,26},
		{10,88,63,3},
		{15,37,99,2},
		{32,85,77,66}
	};
	int menorNum = INT_MAX;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (matriz[i][j] < menorNum)
				menorNum = matriz[i][j];
		}
	}

	std::cout << "O menor Numero da matriz eh: " << menorNum<<"\n";
}


