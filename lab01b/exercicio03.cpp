#include <iostream>
//3. Faça o programa que apresenta a seguinte saída, perguntando ao usuário o número máximo(no exemplo, 9).Este número deve ser sempre ímpar.
//
//1 2 3 4 5 6 7 8 9
//  2 3 4 5 6 7 8
//    3 4 5 6 7
//	4 5 6
//	  5

void printLine(int numArray[9])
{
	for (int i = 0; i < 9;i++)
	{
		if (numArray[i] != -1)
			std::cout << numArray[i];
		else
			std::cout << " ";
	}
}
int main()
{
	int numeroMax = 9;
	int numArray[9];
	for (int i = 0; i < numeroMax;i++)
	{
		numArray[i] = i+1;
	}
	for (int i = 0; i < (numeroMax / 2)+1; i++)
	{
		printLine(numArray);
		numArray[i] = -1;
		numArray[(numeroMax-1) - i] = -1;
		std::cout << "\n";
	}
}


