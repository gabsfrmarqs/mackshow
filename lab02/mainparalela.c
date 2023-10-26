#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int GetHalfPoint(int num) {
  int halfPoint, isEven = 0;

  if (num % 2 == 0)
    isEven = 1;

  if (isEven == 1)
    halfPoint = num / 2;

  else
    halfPoint = (num / 2) + 1;
  return halfPoint;
}

int main() {
  int i, num, j, k = 1, l = 1;
  //printf("Enter the number: ");
  //scanf("%d", &num);
  num = 12;
  j = num;

  int halfPoint = GetHalfPoint(num);

  pid_t child_pid;
  int pipefd[2];//setando o pipe
  
  if (pipe(pipefd) == -1) {
    perror("erro de pipe");
    exit(1);
  }

  child_pid = fork(); //criando processo filho

  if (child_pid < 0) {
    perror("erro de fork");
    exit(1);
  }

  if (child_pid == 0) { //se == 0 estamos n o processo filho
    close(pipefd[0]); //fechando leitura do pipe

    for (k = 1; l < halfPoint; l++)
      k = k * l;//loop da metade de baixo

    printf("The factorial of %d up to %d is %d\n", 1, halfPoint - 1, k);
    
    write(pipefd[1], &k, sizeof(k)); //escrevendo k no pipe
    close(pipefd[1]); //fechando escrita no pipe
    exit(0);
  } else { //aqui é no processo pai
    close(pipefd[1]); //fechando escrita do pipe

    for (i = 1; j >= halfPoint; j = j - 1)
      i = i * j;//loop da metada de cima

    printf("The factorial of %d up to %d is %d\n", halfPoint, num, i);
    
    int resultadok;
    read(pipefd[0], &resultadok, sizeof(resultadok)); //lendo k do pipe
    close(pipefd[0]); // fechando leitura do pipe

    printf("The total is = %d\n", i * resultadok);
    
    int status;
    wait(&status); // esperando o filho acabar
  }
  return 0;
}

