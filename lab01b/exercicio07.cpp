#include <iostream>
#include <string>

struct Pessoa 
{
    std::string nome;
    int idade;
    float peso;
    float altura;
};

int main() 
{
    Pessoa pessoas[3];

    pessoas[0] = { "Maria", 25, 55.5f, 1.65f };
    pessoas[1] = { "Paulo", 30, 70.0f, 1.75f };
    pessoas[2] = { "Pedro", 28, 80.2f, 1.80f };

    std::cout << "Dados das pessoas:\n";
    for (int i = 0; i < 3; ++i) 
    {
        std::cout << "Nome: " << pessoas[i].nome << "\n";
        std::cout << "Idade: " << pessoas[i].idade << " anos\n";
        std::cout << "Peso: " << pessoas[i].peso << " kg\n";
        std::cout << "Altura: " << pessoas[i].altura << " m\n\n";
    }
}
