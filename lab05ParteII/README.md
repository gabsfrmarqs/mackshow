# Laboratório 05 - Parte 1

Esta pasta também contem o Hello World Paralelo mostrado em aula, que apesa de não fazer parte da entrega, demonstra que entendemos o conceito da matéria.

Os aquivos com nome lab05 são os pedidos na entrega, para compilá-los e executá-los use os comandos abaixo, lembrando que o -lm é necessário para a biblioteca math compilar corretamente.


compilar arquivo serial: 

```
gcc lab05serial.c -o lab05serial -lm
```

executar aquivo serial:

```
./lab05serial
```

compilar arquivo paralelo:

```
gcc lab05Paralelo.c -fopenmp -o lab05Paralelo -lm
```

executar arquivo paralelo: nome do executável, espaço, número de threads desejadas:

```
./lab05Paralelo 5
```

# Execuções na AWS
## Máquina 1vCPU
### lscpu
![](imagens/1vcpulscpu.png)

### Execução serial
![](imagens/1vcpuserial.png)

### Execução paralela
![](imagens/1vcpuparalelo.png)

## SpeedUp da Máquina 1vCPU
pela Lei  de Amdahl Sp = T(1)/T(p), mas como a máquina só tem 1 core, claramente o speedup será menor que 1, demonstrando que houve perda de performance:

sp = 0,000965726/0,003531666

sp = 0,273447715 --> uma perda enorme de eficiência. Abaixo executaremos na máquina multicore para demonstrar a melhora na eficiência:

## Máquina 2vCPU
### lscpu
![](imagens/2vcpulscpu.png)

### Execução serial
![](imagens/2vcpuserial.png)

### Execução paralela
![](imagens/2vcpuparalelo.png)

## SpeedUp da Máquina 2vCPU
pela Lei  de Amdahl Sp = T(1)/T(p), e lembrando que na execução foram utilizadas 2 Threads:

sp = 0,003925322/0.001986021

sp = 1,976475576 --> muito próximo de 2 (número de cores da máquina),  o que demonstra um bom ganho de desempenho em relação a versão serial quando executado nesta maquina multicore.
