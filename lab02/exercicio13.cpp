#include <iostream>

void removerCaractere(char str[], int posicao) 
{
    int i = posicao;
    while (str[i] != '\0') 
    {
        str[i] = str[i + 1];
        ++i;
    }
}

int main() {
    char str[100] = "eu sou uma string de caracteres";

    int posicao = 8; // Posição do caractere a ser removido (0-indexed)

    std::cout << "String original: " << str << "\n";
    removerCaractere(str, posicao);
    std::cout << "String apos remover o caractere na posicao " << posicao << ": " << str << "\n";
}
