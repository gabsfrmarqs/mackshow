# Projeto

Gabriel de França Marques - 42107490 \
Renan Luiz Rodrigues Tagliaferro - 42105846

Este projeto visa desenvolver um algoritmo para estimar o valor de 'e' (número de Euler) por meio de uma série infinitesimal. O algoritmo realiza a soma de frações para aproximar 'e' da seguinte forma:

### Implementação inicial: 
Será desenvolvida uma solução para calcular 'e' considerando o maior valor possível para 'n' no denominador da fórmula. A solução usará pelo menos dois núcleos de processamento para computação paralela.

### Registro do valor de 'e': 
O valor obtido para 'e' e valide o número de casas decimais corretas para avaliar a precisão da estimativa.

### Cálculo do Speedup: 
Calcule e registre o speedup obtido ao migrar para a versão paralela do algoritmo. O speedup é a medida da melhoria de desempenho ao utilizar múltiplos núcleos de processamento.

# Número 'e'
O valor de Euler que será obtido para a conferência da precisão foi obtido no site do Astronomy Picture of the Day - NASA, onde é armazenado o número de Euler até com 1 milhão de dígitos de precisão. Localizado em: https://apod.nasa.gov/htmltest/gifcity/e.1mil. \
Segue o número obtido no site com 200 dígitos decimais: 
```
2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901
```

# Compilação do código
O código deverá ser combipilado com diretrizes especiais devido ao uso do OpenMP e do GMP (biblioteca que permite a alocação de variáveis com valores elevados). Primeiro o GMP deverá ser instalado:

Instalação em Fedora/RHEL:
```sudo dnf install gmp-devel```

Com a instalação completa, os códigos que fazem uso do GMP poderão ser compilados:
```gcc -fopenmp -lgmp input.c output.c```

# Explicação arquivos
``EulerMutex.c`` melhor versão Paralela
``EulerOMP.c`` antiga versão Paralela
``EulerSerial.c`` melhor versão Serial

# Como o problema foi resolvido?
Para cálcular o número de Euler com múltiplos dígitos de precisão, foram utilizadas múltiplas threads para agilizar o processo, além de implementar mutex para evitar condições de corrida no código. Além disso, devido ao ``print`` da Linguagem C apresentar alguns problemas de precisão, programamos para que a saída seja feita num arquivo chamado ``res.txt```. Quanto aos números de alta precisão, foi utilizada a biblioteca GMP (GNU Multiple Precision Arithmetic Library), permitindo que seja possível trabalhar com números longos.

### Resumidamente, como funciona o GMP?
O GMP aloca espaço para suas variáveis internamente. Floats no GMP utilizam um expoente e uma mantissa. Pedaços de um número multi-precisão que podem ser armazenados num tipo WORD são denominados _limbs_ (membros), com o uso de _limbs_, é possível realizar lidar com situações de carry em cálculos.

Fonte: ![Biblioteca GMP - Float Internals](https://gmplib.org/manual/Float-Internals#Float-Internals)

# Tempo e speedup da serial para paralela

Serial para n = 20000 (20 mil)
16,923343154s
![](imagens/serial20m.png)

Paralelo para n = 20000 (20 mil)
9,995086440s
![](imagens/paralelo20m.png)

Serial para n = 100000 (100 mil)
474,720885957
![](imagens/serial100m.png)

Paralelo para n = 100000 (100 mil)
261,597125601
![](imagens/paralelo100m.png)

Speedup calculado para n = 20000:
``1,6931662628``

Speedup calculado para n = 100000:
``1,8147022252``

# Estratégia de paralelismo
No primeiro código, foi implementada a paralelização usando a biblioteca OpenMP. A abordagem central envolve dividir a carga de trabalho entre diversas threads por meio de um loop paralelo. Cada thread calcula um resultado parcial de forma independente, e a thread principal agrega esses resultados parciais para obter o resultado final. A seção crítica é empregada para garantir que múltiplas threads possam atualizar a variável de resultado compartilhada sem conflitos.
Na segunda versão, uma estratégia diferente de paralelização foi adotada. Ao invés de utilizar OpenMP, foram utilizados pthreads (threads POSIX). Nessa abordagem, um conjunto de threads é criado, sendo cada uma responsável por uma faixa específica de cálculos. A tarefa é dividida entre as threads, e cada uma delas calcula um resultado parcial. Posteriormente, a thread principal espera pela conclusão de todas as threads e consolida os resultados parciais.

Algumas características distintivas na segunda versão incluem:

- Conjunto de Threads: A segunda versão cria explicitamente um conjunto de threads usando pthread_create e aguarda pela conclusão dessas threads com pthread_join.

- Função das Threads: Cada thread executa a função threadFunction, a qual calcula uma parte do resultado total. Essa função é responsável por uma faixa de cálculos especificada pelos campos start e end na estrutura ThreadData.

- Inicialização da Precisão e do Resultado: As variáveis de precisão e resultado são inicializadas com uma precisão mais alta (65536 bits) para garantir maior exatidão nos cálculos.

- Comparação com o Euler Real: O código inclui uma função (compareWithActualEuler) para comparar o resultado com um valor conhecido do número de Euler. Essa função lê dígitos de dois arquivos e os compara, fornecendo informações sobre possíveis discrepâncias.

Em resumo, ambas as versões empregam técnicas de paralelização para distribuir a carga de trabalho entre múltiplas threads, mas utilizam mecanismos de paralelização diferentes (OpenMP na primeira versão, pthreads na segunda versão). A segunda versão também apresenta recursos adicionais, como um conjunto de threads, gerenciamento explícito de threads e uma função para a comparação do resultado com um valor conhecido.

# Execução do código
### Serial
A execução do código serial gerou um número com 37 casas decimais de precisão:
![](imagens/serial.png)

Saída res.txt:
![](imagens/serial_cat_res.txt.png)

Tempo de execução com o comando ``perf stat -r 1 ./teste``: 31.989403809 segundos

### Paralela
A execução do código paralelo gerou um número com 17 casas de precisão:
![](imagens/parelelo.png)

Saída res.txt:
![](imagens/paralelo_cat_res.txt.png)

Tempo de execução com o comando ``perf stat -r 1 ./eparalelo 2``: 26.099513927 segundos

