#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() 
{
  // precisa ser ponteiro
  int *valor;

  //cria ID da memoria, o 0666 é para ter acesso a leitura e escrita em memoria
  int idMem = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

  //liga a mem compartilhada com o processo
  valor = (int *)shmat(idMem, NULL, 0);
  *valor = 1;

  pid_t pid = fork();
  if (pid == 0) 
  {  // Filho
    *valor += 2;
    printf("Primeira operação -> Valor após adição: %d\n", *valor);

    shmdt(valor);

    exit(0);
  } 
  else 
  { //PAI
    // precisa desse wait senão desincroniza
    wait(NULL);
    
    *valor *= 4;
    printf("Segunda operação -> Valor após multiplicação: %d\n", *valor);
    
    shmdt(valor);

    //IPC_RMIRemove a memória compartilhada
    shmctl(idMem, IPC_RMID, NULL);
  }
  return 0;
}

