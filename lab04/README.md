# LAB04

Considere o trecho de código fornecido para resolver o problema da multiplicação matriz-vetor utilizando pthreads. 
Construa a versão serial e paralela e registre os tempos de execução e speedup no repositório do projeto.

<-- ![codigo do enunciado](enunciado.png) -->
<-- Codigo de compilacao: ```gcc pthread.c -o helloworld -Wall -lpthread``` -->
<-- Execuçao: ```./helloworld <threads>``` -->

## Máquina original
### lscpu
![](imagens/lscpu-original.png)

### Execução serial
![](imagens/lab04-AWSOriginalSerial.png)

### Execução paralela
![](imagens/lab04-AWSOriginalParalela.png)

## Máquina 2vCPU
### lscpu
![](imagens/lscpu-2vCPU.png)

### Execução serial
![](imagens/lab04-AWS2vCPUSerial.png)

### Execução paralela
![](imagens/lab04-AWS2vCPUlParalela.png)
